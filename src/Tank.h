#pragma once
#include "Game.h"

enum direction;//định nghĩa kiểu liệt kê (enum) đại diện cho hướng di chuyển của xe tăng.
class Texture;

class Tank : public Object
{
public:
	Tank(int x, int y, direction d, int up, int down, int left, int right);//đưa ra các thông số cần thiết để khởi tạo một đối tượng xe tăng.
	~Tank();//hàm hủy của lớp Tank.

	static void initTexture(std::string path);//khởi tạo một Texture từ đường dẫn được chỉ định.
	static int getMaxHp();//trả về giá trị tối đa của máu mà một đối tượng Tank có thể có.

	virtual void render();//vẽ đối tượng Tank lên màn hình.
	virtual void reset();//đặt lại trạng thái của đối tượng Tank.
	void handleEvent(SDL_Event &e);//xử lý các sự kiện liên quan đến đối tượng Tank.
	void move();//di chuyển đối tượng Tank.
	void undo();//hoàn tác một hành động đã thực hiện trước
	void respawn(int x, int y); //đặt lại vị trí của đối tượng Tank tại một vị trí mới được chỉ định.
	void respawn(); //đặt lại vị trí của đối tượng Tank tại vị trí respawnX và respawnY.
	void setVelocity();//thiết lập vận tốc của đối tượng Tank dựa trên các phím mũi tên được nhấn.
	void clearButtonFlags(); //xóa các cờ lưu trữ thông tin về các phím mũi tên được nhấn.

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	//Tọa độ x, y, chiều rộng, chiều cao
	int getHp();//trả về lượng máu hiện tại
	unsigned int getScore();// điểm hiện tại
	direction getDirection();//hướng di chuyển
	SDL_Rect getCollider();// trả về khu vực va chạm(hình chữ nhật)

	void decreaseHp();// giảm lượng máu
	void increaseScore();//tăng điểm

	friend class Bullet;//bro :>

private:
	int respawnX;
	int respawnY;

	//Tọa độ
	int vx;
	int vy;
	//Tốc độ
	int hp;
	unsigned int score;
	direction dir; //hướng

	//Hộp va chạm
	SDL_Rect collider;

	//phím điều khiển
	int up;
	int down;
	int left;
	int right;

	//cờ đánh dấu nhấn phím 
	bool upButtonPressed;
	bool downButtonPressed;
	bool leftButtonPressed;
	bool rightButtonPressed;

	//thời gian nhấn phím tương ứng
	Uint32 upTicks;
	Uint32 downTicks;
	Uint32 leftTicks;
	Uint32 rightTicks;
	//sử dụng kiểu dữ liệu Uint32 giúp cho chương trình có thể lưu trữ được các giá trị thời gian lớn hơn
	//và đồng thời không cần phải xử lý các giá trị âm.

	//Ngoài ra, việc sử dụng kiểu dữ liệu Uint32 cũng đảm bảo tính đồng nhất giữa các biến lưu trữ thời gian
	//và các hàm của thư viện SDL, giúp cho việc xử lý các
		//sự kiện liên quan đến thời gian trở nên dễ dàng hơn.
	static const int velocity;//tốc độ
	static const int maxHp;// máu tối đa

	static Texture texture;//hình ảnh
};