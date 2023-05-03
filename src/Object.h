#pragma once
#include <SDL.h>
#include <vector>

class Object
{
public:
	Object();
	virtual ~Object();

	static void setRenderer(SDL_Renderer *r);// thiết lập vẽ
	static void renderAll();// vẽ tất cả đối tượng
	static void resetAll();// reset đối tượng và giải phóng bộ nhớ
	virtual void render() = 0;
	virtual void reset() = 0;

protected:
	//kích thước đối tượng
	int x, y, width, height;
	static SDL_Renderer *renderer;
	static std::vector<Object*> object;
};

