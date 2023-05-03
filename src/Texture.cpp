#include "Texture.h"
//định nghĩa một lớp Texture để xử lý hình ảnh bằng cách sử dụng thư viện SDL.
SDL_Renderer* Texture::renderer = nullptr;
//ạo ra một đối tượng Texture với kích thước ban đầu x và y, với các giá trị 
//khác ban đầu được thiết lập là nullptr, 0 hoặc { 0,0,0,0 } tuỳ thuộc vào kiểu dữ liệu.
Texture::Texture(int x, int y)
{
	texture = nullptr;
	surface = nullptr;
	this->x = x;
	this->y = y;
	width = 0;
	height = 0;
	renderRect = { 0,0,0,0 };
}

Texture::~Texture()
{
	clean();
}
//giải phóng 
void Texture::clean()
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		surface = nullptr;
		width = 0;
		height = 0;
		renderRect = { 0,0,0,0 };
	}
}
//tải và xử lý tệp tin hình ảnh PNG hoặc văn bản (text) để tạo thành texture trong SDL
void Texture::loadPNG(std::string path)
{
	clean();
	//một màu trong hình ảnh (ở đây là màu trắng) được đặt làm màu khóa (color key) bằng cách sử dụng hàm SDL_SetColorKey() với
	//đối số thứ hai là SDL_TRUE và đối số thứ ba là mã màu được trích xuất từ surface (được lấy từ hình ảnh vừa tải) sử dụng hàm SDL_MapRGB()
	surface = IMG_Load(path.c_str());
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	width = surface->w;
	height = surface->h;
	renderRect.w = width;
	renderRect.h = height;

	SDL_FreeSurface(surface);
	surface = nullptr;
}
/*
Tiếp theo, texture được tạo bằng cách sử dụng hàm SDL_CreateTextureFromSurface() với đối số đầu tiên là renderer, một đối tượng SDL_Renderer
đã được khởi tạo từ trước. Sau khi tạo texture, chiều rộng và chiều cao của nó sẽ được lấy từ surface->w và surface->h. renderRect sẽ được
cập nhật tương ứng với kích thước của texture. Cuối cùng, surface sẽ được giải phóng bằng hàm SDL_FreeSurface(),
và trỏ đến nó sẽ được thiết lập thành nullptr.
*/
//tải hình ảnh từ đường dẫn được truyền vào dưới dạng chuỗi path. Trước khi bắt đầu tải, 
//hàm clean() sẽ được gọi để giải phóng tài nguyên của texture trước đó (nếu có).
//Hình ảnh sẽ được tải bằng hàm IMG_Load(path.c_str()) từ thư viện SDL_image.
void Texture::loadText(std::string text, TTF_Font *font, SDL_Color textColor)
{
	clean();

	surface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	width = surface->w;
	height = surface->h;
	renderRect.w = width;
	renderRect.h = height;

	SDL_FreeSurface(surface);
	surface = nullptr;
}
//thiết lập vị trí của texture trong màn hình bằng cách cập nhật giá trị của biến x và y.
void Texture::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}
// vẽ texture lên màn hình tại vị trí được xác định bởi tham số x và y. Tham số angle cho phép xoay texture theo góc được chỉ định.
void Texture::render(int x, int y, double angle)
{
	renderRect.x = x;
	renderRect.y = y;

	SDL_RenderCopyEx(renderer, texture, nullptr, &renderRect, angle, nullptr, SDL_FLIP_NONE);
}
//một phiên bản nạp chồng (overload) của hàm render(), nó được sử dụng để vẽ texture lên màn hình tại vị trí được thiết lập trước đó bằng hàm setPosition().
void Texture::render()
{
	renderRect.x = x;
	renderRect.y = y;

	SDL_RenderCopyEx(renderer, texture, nullptr, &renderRect, 0, nullptr, SDL_FLIP_NONE);
}
/*
Hàm void Texture::render() được nạp chồng (overload) để cho phép vẽ texture lên màn hình tại vị trí được thiết lập
trước đó bằng hàm setPosition(), mà không cần truyền vào tham số vị trí x và y.
Việc này giúp cho việc vẽ các texture trở nên đơn giản hơn và tiện lợi hơn, đặc biệt là trong trường hợp các texture
có thể di chuyển động trên màn hình. Nếu không có hàm này, thì trong mỗi lần muốn vẽ texture tại vị trí hiện tại của nó,
chúng ta phải truyền vào tham số vị trí x và y, làm cho việc sử dụng code trở nên phức tạp và dài hơn.
Vì vậy, việc nạp chồng hàm render() giúp cho việc sử dụng code trở nên đơn giản và tiện lợi hơn, đồng thời cũng giúp tăng 
tính tái sử dụng và linh hoạt của code.
*/
void Texture::setRenderer(SDL_Renderer *r)
{
	renderer = r;
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}