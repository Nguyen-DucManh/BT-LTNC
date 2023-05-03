#pragma once 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include "Object.h"
#include "Texture.h"
#include "Tank.h"
#include "Wall.h"
#include "Bullet.h"
#include "HpBar.h"
#include "Sound.h"
#include "MapLoader.h"
#include "UI.h"
#include "State.h"
#include "TitleState.h"
#include "GameState.h"
#include "MenuState.h"
#include "AboutState.h"

constexpr int MAP_WIDTH = 768;
constexpr int MAP_HEIGHT = 768;
constexpr int WALL_WIDTH = 64;
constexpr int WALL_HEIGHT = 64;
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;

const std::string VERSION_NUMBER = "v1.2.0";

class HpBar;
class Wall;
class Texture;
class Object;
class UI;
//Đoạn code này định nghĩa một enum direction, 
//gồm 4 giá trị UP, RIGHT, DOWN, và LEFT tương ứng với hướng di chuyển của đối tượng trong trò chơi.
enum direction
{
	UP = 0,
	RIGHT = 90,
	DOWN = 180,
	LEFT = 270
};

class Game
{
public:
	Game();
	~Game();
	void run();

	friend class GameState;
	friend class MenuState;

private:
	void initialize();//khởi tạo các giá trị ban đầu cho trò chơi.
	void loadMap();//hàm dùng để tải bản đồ cho trò chơi.
	void loadUI();//hàm dùng để tải giao diện người dùng cho trò chơi.
	void freeDynamicAllocatedMemory();//hàm dùng để giải phóng bộ nhớ đã được cấp phát động.
	bool checkCollision(SDL_Rect a, SDL_Rect b);//hàm dùng để kiểm tra va chạm giữa hai hình chữ nhật a và b.
	void changeState(); //hàm dùng để thay đổi trạng thái của trò chơi

	SDL_Window *window; //cửa sổ của trò chơi
	SDL_Renderer *renderer; //bộ vẽ của trò chơi
	SDL_Event e;//sự kiện của trò chơi
	TTF_Font *font72;
	TTF_Font *font48;
	TTF_Font *font24;
	TTF_Font *font18;
	//font
	State *state;// con trỏ đến trạng thái của trò chơi.

	std::vector<Wall*> wall;
	std::vector<Tank*> tank;
	std::vector<Bullet*> bullet;
	Sound *collisionSound; //con trỏ đến âm thanh khi có va chạm trong trò chơi.
	UI *ui;//con trỏ đến giao diện người dùng của trò chơi.
};