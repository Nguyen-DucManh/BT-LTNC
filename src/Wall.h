#pragma once// đảm bảo rằng mã nguồn sẽ chỉ được đưa vào trình biên dịch một lần duy nhất
#include "Game.h"

class Wall : public Object
{
public:
	Wall(int x, int y, bool destructible = true);//phương thức khởi tạo đối tượng Wall với 
	//vị trí (x, y) trong game và trạng thái có thể phá hủy hay không (destructible).
	~Wall();//hủy đối tượng Wall.

	static void initTextures(std::string wallTexturePath, std::string solidWallTexturePath);
	//phương thức tĩnh để khởi tạo hai đối tượng Texture wallTexture và solidWallTexture bằng cách 
	//load ảnh từ hai đường dẫn đến file ảnh tường phá hủy và tường không phá hủy.
	virtual void render();//phương thức ảo để vẽ đối tượng Wall lên màn hình.
	virtual void reset();//phương thức ảo để đặt lại trạng thái của đối tượng Wall khi cần.
	void destroy();// phương thức để phá hủy đối tượng Wall (nếu đối tượng có thể phá hủy).

	int getX();//phương thức để lấy giá trị tọa độ x của đối tượng Wall.
	int getY(); //phương thức để lấy giá trị tọa độ y của đối tượng Wall.
	bool doesExist();//phương thức để kiểm tra xem đối tượng Wall có còn tồn tại hay không.
	bool isDestructible();//phương thức để kiểm tra xem đối tượng Wall có thể phá hủy hay không.
	SDL_Rect getCollider();
	//phương thức để lấy đối tượng SDL_Rect collider của đối tượng Wall.
private:
	bool exist; //cho biết đối tượng tường có còn tồn tại hay không.
	bool destructible;//cho biết đối tượng tường có thể phá hủy hay không.
	SDL_Rect collider;//xác định vị trí và kích thước của collider (đối tượng chắn) của đối tượng Wall trong game.

	static Texture wallTexture;
	static Texture solidWallTexture;
	/*
	các biến tĩnh "wallTexture" và "solidWallTexture" được sử dụng để lưu trữ các hình ảnh tường và được khởi tạo bằng
	cách gọi phương thức tĩnh "initTextures" của lớp Wall, trong đó đường dẫn đến các tệp hình ảnh được cung cấp để
	load các tệp hình ảnh này vào các đối tượng "Texture".
	*/
};