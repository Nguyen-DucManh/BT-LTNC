#include "GameState.h"



GameState::GameState(Game *game)
{
	this->game = game;
}


GameState::~GameState()
{
}

void GameState::handleEvents(SDL_Event &e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			this->setNextState(EXIT);
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			this->setNextState(MENU);

		game->bullet[0]->handleEvent(e);
		game->tank[0]->handleEvent(e);
		game->bullet[1]->handleEvent(e);
		game->tank[1]->handleEvent(e);
	}
}

void GameState::logic()
{
	// Cập nhật vận tốc của hai xe tăng
	game->tank[0]->setVelocity();
	game->tank[1]->setVelocity();
	// Vòng lặp cho mỗi xe tăng
	for (int i = 0; i < static_cast<int>(game->tank.size()); i++)
	{
		// Bắn đạn và di chuyển đạn
		game->bullet[i]->fire(game->tank[i], 500);
		game->bullet[i]->move(); 
		// Di chuyển xe tăng
		game->tank[i]->move();

		// Kiểm tra va chạm giữa hai xe tăng
		if (game->checkCollision(game->tank[i]->getCollider(), game->tank[(i + 1) % 2]->getCollider())) game->tank[i]->undo();

		// Nếu xảy ra va chạm, đưa vị trí của xe tăng trở lại vị trí trước đó
		if (game->bullet[i]->doesExist() && game->checkCollision(game->bullet[i]->getCollider(), game->tank[(i + 1) % 2]->getCollider()))
		{
			game->tank[(i + 1) % 2]->decreaseHp(); // Nếu xảy ra va chạm, giảm điểm số của xe tăng bị bắn
			game->bullet[i]->reset();// Đặt lại đạn
			game->collisionSound->play(); // Phát âm thanh va chạm
			// Nếu điểm số của xe tăng bị bắn giảm xuống 0
			if (game->tank[(i + 1) % 2]->getHp() == 0)
			{
				// Hồi sinh xe tăng và tăng điểm số của xe tăng bắn đạn
				game->tank[(i + 1) % 2]->respawn();
				game->tank[i]->increaseScore();
			}
		}

		// Kiểm tra va chạm giữa từng mảnh tường trong trò chơi với xe tăng và đạn
		for (int j = 0; j < static_cast<int>(game->wall.size()); j++)
		{
			// Kiểm tra va chạm giữa xe tăng và mảnh tường
			if (game->wall[j]->doesExist() && game->checkCollision(game->tank[i]->getCollider(), game->wall[j]->getCollider())) game->tank[i]->undo();
			// Nếu xảy ra va chạm và mảnh tường có thể phá hủy
			if (game->wall[j]->doesExist() && game->bullet[i]->doesExist() && game->checkCollision(game->bullet[i]->getCollider(), game->wall[j]->getCollider()))
			{
				/*
				kiểm tra xem có va chạm giữa đạn và tường không. Nếu có, nó kiểm tra xem tường có phải là tường có thể phá hủy hay không bằng cách
				sử dụng phương thức isDestructible() trên đối tượng tường. Nếu tường có thể phá hủy, nó gọi hàm destroy() trên đối tượng tường để 
				phá hủy nó.
				Sau đó, nó gọi hàm reset() trên đối tượng đạn để đặt lại vị trí của nó và phát âm thanh va chạm bằng cách gọi hàm play() trên đối
				tượng âm thanh. Nếu tường không thể phá hủy, việc phát âm thanh va chạm chỉ được thực hiện, không làm gì thêm.
				*/
				if (game->wall[j]->isDestructible())
					game->wall[j]->destroy();

				game->bullet[i]->reset();
				game->collisionSound->play();
			}
		}
	}

	//Set current score
	game->ui->setScore(game->tank[0]->getScore(), game->tank[1]->getScore());
	game->ui->setBar(game->tank[0]->getHp(), game->tank[1]->getHp());
}
//Thiết lập màu nền cho cửa sổ (renderer) bằng hàm SDL_SetRenderDrawColor
void GameState::render()
{
	//Clear window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);//Xóa toàn bộ nội dung của cửa sổ bằng hàm SDL_RenderClear.
	//Gọi phương thức renderAll của lớp Object để vẽ tất cả các đối tượng lên màn hình.
	Object::renderAll();
	//Hiển thị toàn bộ nội dung đã vẽ lên màn hình bằng hàm
	SDL_RenderPresent(renderer);
}