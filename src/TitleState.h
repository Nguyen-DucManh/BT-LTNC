#pragma once
#include "State.h"
#include "Texture.h"

class Texture;

class TitleState : public State
{
public:

	TitleState(TTF_Font *font);
	~TitleState();
	// xử lý sự kiện, tính toán và vẽ hình ảnh
	virtual void handleEvents(SDL_Event &e);
	virtual void logic();
	virtual void render();
private:
	//vẽ hình ảnh nền và thông tin trên màn hình trạng thái chính
	Texture *background;
	Texture *info;
};

