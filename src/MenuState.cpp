#include "MenuState.h"



MenuState::MenuState(TTF_Font *font72, TTF_Font *font48)
{
	currentChoice = static_cast<int>(Menu::RESUME);
	returnPressed = false;
	background = { menuBeginX - 50,menuBeginY - 160,320,400 };
	currentChoiceRect = { menuBeginX,menuBeginY+7,230,50 };

	texture.push_back(new Texture(menuBeginX, menuBeginY));
	texture.push_back(new Texture(menuBeginX, menuBeginY + 50));
	texture.push_back(new Texture(menuBeginX, menuBeginY + 100));
	texture.push_back(new Texture(menuBeginX, menuBeginY + 150));
	texture.push_back(new Texture(menuBeginX, 200));

	texture[static_cast<int>(Menu::RESUME)]->loadText("RESUME", font48);
	texture[static_cast<int>(Menu::RESTART)]->loadText("RESTART", font48);
	texture[static_cast<int>(Menu::ABOUT)]->loadText("ABOUT", font48);
	texture[static_cast<int>(Menu::EXIT)]->loadText("EXIT", font48);
	texture[static_cast<int>(Menu::MENUTITLE)]->loadText("MENU", font72);
}


MenuState::~MenuState()
{
	for (int i = 0; i < static_cast<int>(texture.size()); i++)
	{
		delete texture[i];
	}
}
/*
Hàm handleEvent() được sử dụng để xử lý các sự kiện như phím được nhấn hoặc chuột được nhấn.
Trong trường hợp này, nó chỉ xử lý các sự kiện liên quan đến phím được nhấn.
Nếu phím mũi tên lên được nhấn, thì lựa chọn hiện tại sẽ giảm đi 1 đơn vị. Nếu phím mũi tên xuống được nhấn,
thì lựa chọn hiện tại sẽ tăng lên 1 đơn vị. Nếu phím Enter 
được nhấn, biến returnPressed được đặt thành true để xác định rằng người dùng đã chọn một mục trong menu.
Cuối cùng, phương thức kết thúc và chờ để xử lý các sự kiện tiếp theo từ hàng đợi SDL_Event.
*/
void MenuState::handleEvents(SDL_Event &e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			this->setNextState(EXIT);
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				{
					this->setNextState(GAME);
					break;
				}
				case SDLK_UP:
				{
					currentChoice--;
					break;
				}
				case SDLK_DOWN:
				{
					currentChoice++;
					break;
				}
				case SDLK_RETURN:
				{
					returnPressed = true;
					break;
				}
			}
		}
	}
}

void MenuState::logic()
//Hàm logic() này được gọi liên tục để cập nhật trạng thái của trò chơi.
{
	//Đoạn code này kiểm tra nếu lựa chọn hiện tại đang nằm ngoài phạm vi của menu, 
	//thì nó sẽ được điều chỉnh để nằm trong phạm vi hợp lệ. Điều này giúp đảm bảo rằng 
	//lựa chọn sẽ luôn nằm trong phạm vi của menu và tránh các lỗi xảy ra khi truy cập vào phần tử nằm ngoài phạm vi.
	if (currentChoice < 0)
		currentChoice = menuElements - 1;
	else if (currentChoice >= menuElements)
		currentChoice = 0;
	/*
	Nếu phím trở về được nhấn, switch case sẽ được sử dụng để xác định lựa chọn hiện tại trong menu. Các lựa chọn trong menu bao gồm:

RESUME: tiếp tục chơi trò chơi.
RESTART: khởi động lại trò chơi và thiết lập lại tất cả đối tượng.
ABOUT: xem thông tin về trò chơi.
EXIT: thoát khỏi trò chơi.
Tùy thuộc vào lựa chọn được chọn, hàm setNextState() được gọi để thiết lập trạng thái kế tiếp của trò chơi. Nếu lựa chọn là RESTART,
thì Object::resetAll() cũng được gọi để thiết lập lại tất cả đối tượng.
	*/
	if (returnPressed)
	{
		switch (currentChoice)
		{
			case (int)Menu::RESUME:
			{
				this->setNextState(GAME);
				break;
			}
			case (int)Menu::RESTART:
			{
				this->setNextState(GAME);
				Object::resetAll();
				break;
			}
			case (int)Menu::ABOUT:
			{
				this->setNextState(ABOUT);
				break;
			}
			case (int)Menu::EXIT:
			{
				this->setNextState(EXIT);
				break;
			}
		}
	}

	/*cập nhật vị trí hiện tại của hình chữ nhật đại diện cho lựa chọn trong menu. Vị trí này được tính toán bằng cách thêm
	giá trị của menuBeginY và 7 (để dịch chuyển hình chữ nhật lên trên một chút), và nhân với 50 (khoảng cách giữa hai lựa chọn trong menu)
	. Giá trị của currentChoice được sử dụng để xác định lựa chọn hiện tại của người dùng trong menu.
Khi người dùng di chuyển lên hoặc xuống trong menu, vị trí của hình chữ nhật đại diện cho lựa chọn cũng được 
cập nhật để di chuyển đến vị trí mới của lựa chọn hiện tại. Việc cập nhật này sẽ được thực hiện bởi hàm logic() 
mỗi khi người dùng di chuyển hoặc chọn một lựa chọn mới trong menu
.*/
	currentChoiceRect.y = menuBeginY + 7 + currentChoice * 50;\
}
/*
Hàm render() này được sử dụng để vẽ các phần tử trong menu lên màn hình.
Nó duyệt qua từng phần tử trong menu và vẽ chúng lên màn hình bằng cách sử dụng các hình ảnh đã được tải vào bộ nhớ trước đó.
Nếu phần tử hiện tại đang được vẽ, thì hình chữ nhật hiện tại được vẽ lên màn hình bằng cách sử dụng hàm SDL_RenderCopy().
Nếu không, hình ảnh của phần tử được lưu trữ trong một mảng các hình ảnh và được vẽ bằng cách sử dụng phần tử tương ứng trong mảng.
*/
void MenuState::render()
{
	//Clear window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	Object::renderAll();

	SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
	SDL_RenderFillRect(renderer, &background);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &background);

	for (auto x : texture)
	{
		x->render();
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, menuBeginX, 280, menuBeginX + 220, 280);
	SDL_RenderDrawLine(renderer, menuBeginX, 283, menuBeginX + 220, 283);
	SDL_RenderDrawLine(renderer, menuBeginX, 286, menuBeginX + 220, 286);
	SDL_RenderDrawRect(renderer, &currentChoiceRect);

	SDL_RenderPresent(renderer);
}