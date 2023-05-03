#pragma once
#include "State.h"
#include "Game.h"
//Hiển thị menu và xử lý tương tác
enum class Menu//liệt kê định nghĩa các tùy chọn cho Menu
{
	RESUME,
	RESTART,
	ABOUT,
	EXIT,
	MENUTITLE
};

class Game;

class MenuState : public State
{
public:
	MenuState(TTF_Font *font72, TTF_Font *font48);
	~MenuState();
	//Xử lý sự kiện, tính toán và vẽ
	virtual void handleEvents(SDL_Event &e);
	virtual void logic();
	virtual void render();

private:
	std::vector<Texture*> texture;//lưu trữ thông tin hình ảnh, văn bản
	SDL_Rect currentChoiceRect;
	//kích thước và vị trí các thành phần trong menu
	SDL_Rect background;
	int currentChoice;// được khởi tạo với giá trị 0, đại diện cho tùy chọn đầu tiên trong menu.
	bool returnPressed;//được khởi tạo với giá trị false, đại diện cho trạng thái ban đầu khi chưa có phím "Enter" được nhấn.
	const int menuElements = 4;//một hằng số để lưu trữ số lượng tùy chọn trong menu.
	// lưu trữ vị trí bắt đầu của menu trên màn hình.
	int menuBeginX = 400;
	int menuBeginY = 350;
};

