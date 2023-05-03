#include "Game.h"
// khởi tạo game
Game::Game()
{
	window = nullptr;
	renderer = nullptr;
	initialize();
}
//hàm hủy
Game::~Game()
{
	freeDynamicAllocatedMemory();

	TTF_CloseFont(font72);
	TTF_CloseFont(font48);
	TTF_CloseFont(font24);
	TTF_CloseFont(font18);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::freeDynamicAllocatedMemory()
{
	delete state;
	delete collisionSound;
	delete ui;

	for (int i = 0; i < static_cast<int>(wall.size()); i++)
	{
		delete wall[i];
	}

	for (int i = 0; i < static_cast<int>(tank.size()); i++)
	{
		delete tank[i];
	}

	for (int i = 0; i < static_cast<int>(bullet.size()); i++)
	{
		delete bullet[i];
	}
}

void Game::initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) State::setCurrentState(EXIT);

	//Set linear filtering
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	window = SDL_CreateWindow(("TANKS " + VERSION_NUMBER).c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) State::setCurrentState(EXIT);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) State::setCurrentState(EXIT);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) State::setCurrentState(EXIT);

	//Initialize TrueTypeFont
	if (TTF_Init() == -1) State::setCurrentState(EXIT);

	font72 = TTF_OpenFont("fonts/TruenoRg.otf", 72);
	if (font72 == nullptr) State::setCurrentState(EXIT);
	font48 = TTF_OpenFont("fonts/TruenoRg.otf", 48);
	if (font48 == nullptr) State::setCurrentState(EXIT);
	font24 = TTF_OpenFont("fonts/TruenoRg.otf", 24);
	if (font24 == nullptr) State::setCurrentState(EXIT);
	font18 = TTF_OpenFont("fonts/TruenoRg.otf", 18);
	if (font18 == nullptr) State::setCurrentState(EXIT);

	//Initialize audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) State::setCurrentState(EXIT);

	collisionSound = new Sound();
	collisionSound->loadWAV("sounds/collision.wav");

	//Set renderer for classes
	State::setRenderer(renderer);
	Object::setRenderer(renderer);
	Texture::setRenderer(renderer);
	HpBar::setRenderer(renderer);

	state = new TitleState(font48);

	//Init static textures
	Bullet::init("images/bullet.png", "sounds/fire.wav", collisionSound);
	Tank::initTexture("images/tank.png");
	Wall::initTextures("images/wall.png", "images/solidWall.png");

	loadUI();
	loadMap();

	bullet.push_back(new Bullet(SDLK_RETURN));
	bullet.push_back(new Bullet(SDLK_SPACE));
}

void Game::loadMap()
{
	MapLoader ml("map.txt");
	ml.getWalls(wall);
	ml.getTanks(tank);
}

void Game::loadUI()
{
	ui = new UI(font48, font24);
}
/*
vòng lặp chính của trò chơi. Nó chạy trong khi trạng thái hiện tại không phải là EXIT. 
Trong vòng lặp, nó gọi hàm handleEvents() của trạng thái hiện tại để xử lý bất kỳ sự kiện nào
(như đầu vào của người dùng), sau đó gọi hàm logic() để cập nhật logic của trò chơi và sau đó gọi hàm render()
để vẽ trạng thái hiện tại của trò chơi.
*/
void Game::run()
{
	//Main loop
	while (State::getCurrentState() != EXIT)
	{
		state->handleEvents(e);
		state->logic();
		changeState();
		state->render();
	}
}
/*
kiểm tra xem hai hình chữ nhật SDL_Rectangles a và b có va chạm hay không. Nó thực hiện kiểm tra xem hai hình chữ 
nhật có chồng lên nhau hay không. Nếu không có chồng lên nhau, hàm sẽ trả về false, ngược lại sẽ trả về true. Hàm
này có thể được sử dụng trong hệ thống phát hiện va chạm của trò chơi để kiểm tra va chạm giữa các đối tượng trò chơi,
như các chiếc xe tăng và tường.
*/
bool Game::checkCollision(SDL_Rect a, SDL_Rect b)
{
	if (a.y >= b.y + b.h) return false;
	if (a.y + a.h <= b.y) return false;
	if (a.x >= b.x + b.w) return false;
	if (a.x + a.w <= b.x) return false;

	return true;
}
//chuyển đổi giữa các trạng thái (state) của trò chơi.
void Game::changeState()
{
	/*
	 biến static State::getNextState() để kiểm tra trạng
	 thái kế tiếp của trò chơi. Nếu giá trị của biến khác NONE, 
	 hàm sẽ tiếp tục kiểm tra giá trị của biến đó để xác định trạng thái mới của trò chơi.
	 Nếu trạng thái kế tiếp là EXIT, trò chơi sẽ kết thúc, ngược lại thì hàm sẽ xóa trạng
	 thái hiện tại bằng lệnh delete state và tạo một trạng thái mới tương ứng với giá trị của biến State::getNextState().
	*/
	if (State::getNextState() != NONE)
	{
		if (State::getNextState() != EXIT)
			delete state;
		/*
		sử dụng một switch case để kiểm tra giá trị của State::getNextState() và tạo ra trạng thái mới tương ứng với
		mỗi giá trị của biến đó. Trong trường hợp của mỗi trạng thái, hàm sẽ khởi tạo đối tượng của trạng thái tương ứng.
		*/
		switch (State::getNextState())
		{
			case TITLE:
			{
				state = new TitleState(font48);
				break;
			}
			case GAME:
			{
				state = new GameState(this);

				// Vòng lặp này cần thiết để ngừng di chuyển xe tăng hoặc bắn đạn sau khi thay đổi trạng thái
				// Nếu không có nó, xe tăng có thể di chuyển hoặc bắn đạn mà không cần nhấn nút (sau khi trở về từ trạng thái menu)
				// Điều này được gây ra bởi các cờ không thể thay đổi sau khi thay đổi trạng thái
				// Đó là lý do tại sao chúng phải được thiết lập bằng tay
				for (int i = 0; i < static_cast<int>(tank.size()); i++)
				{
					tank[i]->clearButtonFlags();
					bullet[i]->clearButtonFlag();
				}
				break;
			}
			case MENU:
			{
				state = new MenuState(font72, font48);
				break;
			}
			case ABOUT:
			{
				state = new AboutState(VERSION_NUMBER, font72, font48, font24, font18);
				break;
			}
		}
		//Sau đó, hàm sẽ cập nhật trạng thái hiện tại của trò chơi bằng cách gọi hàm State::setCurrentState(State::getNextState())
		//và đặt giá trị của biến State::setNextState(NONE) để đánh dấu trạng thái kế tiếp của trò chơi là NONE.
		State::setCurrentState(State::getNextState());
		State::setNextState(NONE);
	}
}