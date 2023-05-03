#pragma once
#include "Game.h"

enum direction;
/*
là một kiểu liệt kê (enum) định nghĩa các hướng di chuyển của đối tượng Bullet,
bao gồm UP, DOWN, LEFT và RIGHT. Kiểu liệt kê này được sử dụng trong các phương thức của
đối tượng Bullet để xác định hướng di chuyển của viên đạn. Cụ thể, phương thức getDirection() 
của đối tượng Bullet trả về một giá trị kiểu direction, biểu thị hướng di chuyển hiện tại của viên đạn. 
Việc sử dụng kiểu liệt kê giúp mã nguồn dễ đọc hơn và giảm thiểu các lỗi cú pháp trong việc định nghĩa 
các hướng di chuyển của đối tượng Bullet.
*/
class Sound;
class Tank;
class Texture;

class Bullet : public Object
{
public:
	Bullet(int fireButton);//là hàm khởi tạo của đối tượng Bullet, nhận vào tham số là nút bắn đạn trên bàn phím.
	~Bullet(); //là hàm hủy của đối tượng Bullet.

	static void init(std::string texturePath, std::string fireSoundPath, Sound *collisionSound); //hàm khởi tạo đối tượng Bullet, 
	//tải các tài nguyên cần thiết và cấu hình âm thanh.

	//Render bullet if exist
	virtual void render(); //là phương thức hiển thị viên đạn trên màn hình nếu đang tồn tại.
	virtual void reset(); //là phương thức thiết lập lại trạng thái của viên đạn sau khi nó đã bị
	//phá hủy hoặc va chạm với một đối tượng khác.
	void handleEvent(SDL_Event &e); //là phương thức xử lý sự kiện của đối tượng Bullet,
	//kiểm tra xem nút bắn đạn có được nhấn hay không
	void fire(Tank *tank, int delay); //là phương thức bắn đạn từ một đối tượng Tank(Xe tăng) đã được chuyền vào, 
	//với một độ trễ được cấu hình trước.
	void move(); //là phương thức di chuyển viên đạn dựa trên hướng di chuyển và tốc độ của nó
	void clearButtonFlag();//dùng để xóa cờ hiệu được đặt khi nút bắn được nhấn. 
	//Điều này giúp đảm bảo rằng viên đạn sẽ không bị bắn nhiều lần từ cùng một lần nhấn nút.

	bool doesExist();
	//dùng để xóa cờ hiệu được đặt khi nút bắn được nhấn. 
	//Điều này giúp đảm bảo rằng viên đạn sẽ không bị bắn nhiều lần từ cùng một lần nhấn nút.
	direction getDirection(); //trả về hướng di chuyển hiện tại của viên đạn,
	//được định nghĩa dưới dạng kiểu liệt kê direction.
	SDL_Rect getCollider();
	//trả về khu vực va chạm của viên đạn, được định nghĩa dưới dạng SDL_Rect. 
	//Khu vực này là một hình chữ nhật xác định vị trí và kích thước của viên đạn trên màn hình, 
	//để xác định khi nào viên đạn va chạm với các đối tượng khác.
private:
	//là tốc độ của viên đạn theo trục x và y.
	int vx;
	int vy;
	//biểu thị trạng thái của viên đạn, true nếu đang tồn tại và false nếu đã bị phá hủy.
	bool exist;
	/*
	Các biến buttonTicks và shotTicks trong đoạn code trên được sử dụng để xác định thời điểm
	nút bắn được nhấn và thời điểm viên đạn được bắn ra. Các biến này được định nghĩa dưới dạng kiểu Uint32,
	đại diện cho số nguyên không âm 32-bit không dấu, và được sử dụng để lưu trữ giá trị số nguyên biểu diễn 
	thời gian tính bằng mili giây.

- Biến buttonTicks được sử dụng để lưu trữ thời điểm cuối cùng nút bắn được nhấn. 
  Biến này được cập nhật trong phương thức handleEvent() khi phát hiện nút bắn được nhấn.

- Biến shotTicks được sử dụng để lưu trữ thời điểm cuối cùng viên đạn được bắn ra. 
	Biến này được cập nhật khi viên đạn được bắn ra bởi phương thức fire().

Cả hai biến này được sử dụng để tính toán khoảng thời gian giữa thời điểm nút bắn 
được nhấn và thời điểm viên đạn được bắn ra, để đảm bảo rằng có một khoảng thời gian nhất định
giữa các lần bắn viên đạn và tránh tình trạng bắn liên tục.
	*/
	Uint32 buttonTicks;
	Uint32 shotTicks;
	//là hướng di chuyển của viên đạn.
	direction dir;

	SDL_Rect collider;// là hình chữ nhật va chạm của viên đạn.

	int fireButton; //biểu thị nút bắn đạn trên bàn phím, được chuyền vào qua hàm khởi tạo.
	bool fireButtonPressed; //biểu thị trạng thái của nút bắn đạn, true nếu được nhấn và false nếu không.

	static const int velocity; //là tốc độ di chuyển của viên đạn
	static Texture texture; //là đối tượng Texture(Ảnh) của viên đạn, được chia sẻ giữa tất cả các đối tượng Bullet.
	static Sound fireSound;//là âm thanh phát ra khi bắn đạn, cũng được chia sẻ giữa tất cả các đối tượng Bullet.
	static Sound *collisionSound;//là âm thanh phát ra khi viên đạn va chạm với một đối tượng khác, 
	//được chuyền vào qua hàm khởi tạo.
};