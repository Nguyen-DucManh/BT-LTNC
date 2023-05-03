#pragma once
#include "Game.h"
// Xử lý hiển thị hình ảnh và văn bản ra màn hình
class Texture
{
public:
	Texture(int x = 0, int y = 0);
	~Texture();

	static void setRenderer(SDL_Renderer *r);

	void render();
	void render(int x, int y, double angle = 0.0);// hiển thị text tại vị trí (x, y), góc quay angle
	void clean();// giải phóng
	void loadPNG(std::string path); //Tải hình ảnh và tạo texture
	void loadText(std::string text, TTF_Font *font, SDL_Color textColor = { 255,255,255,255 });//tải vằn bản và tạo texture từ văn bản đó với font, màu sắc chỉ định
	void setPosition(int x, int y);
	// thiết lập vị trí của texture

	int getWidth();
	int getHeight();

private:
	int x, y;
	int width, height;

	static SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *surface;
	SDL_Rect renderRect;
};