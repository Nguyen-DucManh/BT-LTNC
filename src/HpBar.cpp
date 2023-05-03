#include "HpBar.h"

SDL_Renderer* HpBar::renderer{};

HpBar::HpBar(int maxHp, int width, int height, int x, int y)
/*
phương thức khởi tạo lớp HpBar với giá trị tối đa maxHp, chiều rộng width,
chiều cao height, tọa độ x và y của thanh máu trên màn hình. Hàm này cũng 
tính toán và thiết lập kích thước và vị trí cho mỗi "đoạn" của thanh máu.
*/
{
	this->maxHp = maxHp;
	this->hp = maxHp;

	bar = new SDL_Rect[maxHp];

	for (int i = 0; i < maxHp; i++)
	{
		bar[i].w = width / maxHp;
		bar[i].h = height;
		bar[i].x = x + i * bar[i].w;
		bar[i].y = y;
	}
}

HpBar::~HpBar()//phương thức hủy lớp HpBar, giải phóng bộ nhớ cho mảng bar.
{
	delete[] bar;
}

void HpBar::setRenderer(SDL_Renderer *r)//phương thức thiết lập renderer SDL_Renderer cho lớp HpBar.
{
	renderer = r;
}

void HpBar::setHp(int hp)//phương thức thiết lập giá trị hiện tại của thanh máu.
{
	this->hp = hp;
}
/*
phương thức vẽ thanh máu trên màn hình với giá trị hiện tại của hp. Nó sử dụng SDL_SetRenderDrawColor
để thiết lập màu cho thanh máu, và sau đó sử dụng SDL_RenderFillRect để vẽ các đoạn thanh máu tương ứng với giá trị hp và maxHp.
*/
void HpBar::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; i < hp; i++) SDL_RenderFillRect(renderer, &bar[i]);
	SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
	for (int i = hp; i < maxHp; i++) SDL_RenderFillRect(renderer, &bar[i]);
}