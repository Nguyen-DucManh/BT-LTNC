#pragma once
#include "Game.h"

enum class TextureUI
{
	//Các thành phần giao diện người dùng được định nghĩa bằng enum TextureUI, bao gồm các hình ảnh như:
	PLAYER1,
	PLAYER2,
	PLAYER1MOVE,
	PLAYER2MOVE,
	PLAYER1FIRE,
	PLAYER2FIRE,
	HP1,
	HP2,
	SCORETANK1,
	SCORETANK2
};

class HpBar;
//tạo thanh máu của Tank
class UI : public Object
{
public:
	UI(TTF_Font *bigFont, TTF_Font *normalFont);
	~UI();

	virtual void render(); //được sử dụng để vẽ các thành phần giao diện người dùng trên màn hình.
	virtual void reset();//được sử dụng để thiết lập lại các thành phần giao diện người dùng khi chơi lại trò chơi.
	void setBar(int player1, int player2);//được sử dụng để cập nhật thanh máu của các tướng (tank) trong trò chơi.
	void setScore(int player1, int player2);// được sử dụng để cập nhật điểm số của hai người chơi trong trò chơi.

private:
	SDL_Rect background; // kích thước màn hình
	std::vector<Texture*> texture;// hình ảnh thành phần giao diện người dùng
	HpBar *bar1;
	HpBar *bar2;
	//thanh máu
	std::string score1;
	std::string score2;
	// điểm
	TTF_Font *bigFont;
	TTF_Font *normalFont;
//font
};

