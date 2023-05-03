#pragma once
#include "Game.h"

class HpBar
{
public:
	HpBar(int maxHp, int width, int height, int x, int y);//các yếu tố của thanh máu
	~HpBar();// hàm hủy

	static void setRenderer(SDL_Renderer *r);// vẽ

	void render();// phương thức vẽ
	void setHp(int hp);// thiết lập máu

private:
	int x, y;
	int width, height;
	int hp;
	int maxHp;
	SDL_Rect *bar;// đại diện cho thanh máu

	static SDL_Renderer *renderer;// vẽ thanh máu
};