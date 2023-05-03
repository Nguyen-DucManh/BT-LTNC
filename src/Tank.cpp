#include "Tank.h"

/*
velocity là tốc độ di chuyển mặc định của Tank và được khởi tạo với giá trị là 2,
maxHp là số lượng máu tối đa của Tank và được khởi tạo với giá trị là 4.
*/
const int Tank::velocity = 2;
const int Tank::maxHp = 4;
// hiển thị hình ảnh của Tank.
Texture Tank::texture;
//
Tank::Tank(int x, int y, direction d, int up, int down, int left, int right)
{

	//lưu trữ tọa độ xuất phát của Tank
	respawnX = x;
	respawnY = y;
	reset();// khởi tạo lại giá trị ban đầu các biến thành viên của Tank
	//kích thước
	width = 60;
	height = 60;
	// vận tốc
	vx = 0;
	vy = 0;
	//một hình chữ nhật (rect) đại diện cho khu vực xung quanh Tank để xác định va chạm
	collider.w = width;
	collider.h = height;
	// hướng di chuyển
	dir = d;

	//phím điều khiển
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
	//xóa bỏ trạng thái của các phím điều khiển và chuẩn bị cho việc bắt đầu một vòng lặp mới.
	clearButtonFlags();
	//thời gian nhấn
	upTicks = 0;
	downTicks = 0;
	leftTicks = 0;
	rightTicks = 0;
}


Tank::~Tank()
{
}
//xử lý các sự kiện như nút bấm được nhấn hoặc nút bấm được thả.
void Tank::handleEvent(SDL_Event &e)
{
	/*
	 trước tiên kiểm tra xem nút bấm nào đã được nhấn bằng cách
	 kiểm tra sự kiện SDL_KEYDOWN. Nếu một trong các nút bấm được nhấn, 
	 giá trị của các biến upButtonPressed, downButtonPressed, leftButtonPressed 
	 hoặc rightButtonPressed sẽ được đặt thành true, tương ứng với việc lưu thời 
	 điểm bắt đầu được tính bằng cách sử dụng hàm SDL_GetTicks().
	*/
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == up)
		{
			upButtonPressed = true;
			upTicks = SDL_GetTicks();
		}
		else if (e.key.keysym.sym == down)
		{
			downButtonPressed = true;
			downTicks = SDL_GetTicks();
		}
		else if (e.key.keysym.sym == left)
		{
			leftButtonPressed = true;
			leftTicks = SDL_GetTicks();
		}
		else if (e.key.keysym.sym == right)
		{
			rightButtonPressed = true;
			rightTicks = SDL_GetTicks();
		}
	}
	//Các biến up, down, left, right được truyền vào phương thức để định nghĩa các nút bấm tương ứng.
	//Nếu sự kiện SDL_KEYUP được kích hoạt, có nghĩa là một trong các nút bấm đã được thả.
// Trong trường hợp này, giá trị của biến tương ứng sẽ được đặt thành false.
	if (e.type == SDL_KEYUP)
	{
		if (e.key.keysym.sym == up) upButtonPressed = false;
		else if (e.key.keysym.sym == down) downButtonPressed = false;
		else if (e.key.keysym.sym == left) leftButtonPressed = false;
		else if (e.key.keysym.sym == right) rightButtonPressed = false;
	}
}

void Tank::setVelocity()
{
	// Nếu có bất kỳ nút lái xe nào được nhấn
	if (upButtonPressed || downButtonPressed || leftButtonPressed || rightButtonPressed)
	{
		// Kiểm tra xem nút lái xe nào được nhấn nhiều nhất và thiết lập tốc độ và hướng di chuyển cho tank tương ứng
		/*
		Nếu có bất kỳ nút nào được nhấn, phương thức tiếp tục kiểm tra xem nút nào được nhấn nhiều hơn bằng cách so 
		sánh số lần nhấn của các nút đó (lưu trong các biến upTicks, downTicks, leftTicks, và rightTicks). Nếu nút up 
		được nhấn nhiều nhất, tốc độ của tank sẽ được đặt là 0 đơn vị trên trục x (vx = 0) và velocity đơn vị trên trục
		y (vy = -velocity), và hướng di chuyển của tank sẽ được thiết lập là UP (lưu trong biến dir). Tương tự, nếu nút 
		down, left, hoặc right được nhấn nhiều hơn, phương thức sẽ đặt tốc độ và hướng di chuyển của tank theo cách tương ứng.
		Nếu không có nút nào được nhấn, tốc độ và hướng di chuyển của tank sẽ được đặt lại về 0 để dừng di chuyển.
		*/
		if (upTicks > downTicks && upTicks > leftTicks && upTicks > rightTicks && upButtonPressed)
		{
			vx = 0;
			vy = -velocity;
			dir = UP;
		}
		else if (downTicks > upTicks && downTicks > leftTicks && downTicks > rightTicks && downButtonPressed)
		{
			vx = 0;
			vy = velocity;
			dir = DOWN;
		}
		else if (leftTicks > upTicks && leftTicks > downTicks && leftTicks > rightTicks && leftButtonPressed)
		{
			vx = -velocity;
			vy = 0;
			dir = LEFT;
		}
		else if (rightTicks > upTicks && rightTicks > downTicks && rightTicks > leftTicks && rightButtonPressed)
		{
			vx = velocity;
			vy = 0;
			dir = RIGHT;
		}
		else
		{
			vx = 0;
			vy = 0;
		}
	}
	else 
	{
		vx = 0;
		vy = 0;
	}
}
/*
di chuyển Tank dựa trên vận tốc hiện tại của nó. Các biến x và y lưu trữ tọa độ hiện tại của Tank. 
Khi di chuyển, giá trị của x sẽ được tăng lên với vận tốc vx, tương tự với giá trị của y sẽ được tăng lên với vận tốc vy. 
Sau đó, giá trị của biến collider sẽ được cập nhật tương ứng với giá trị của x và y để định vị vị trí của Tank trên màn hình.
trong trường hợp Tank di chuyển ra khỏi màn hình, vị trí của Tank sẽ không được thay đổi và phương thức sẽ lùi lại trạng thái
trước đó. Điều này được thực hiện bằng cách giảm giá trị của x và y đi với vận tốc vx và vy tương ứng,
và cập nhật lại giá trị của biến collider để đảm bảo vị trí của Tank đúng với vị trí trước đó trên màn hình.
*/
void Tank::move()
{
	x += vx;
	collider.x = x;

	if ((x < 0) || (x + width > 768))
	{
		x -= vx;
		collider.x = x;
	}

	y += vy;
	collider.y = y;

	if ((y < 0) || (y + height > 768))
	{
		y -= vy;
		collider.y = y;
	}
}
/*
hoàn tác (undo) việc di chuyển Tank về trạng thái trước đó. Các giá trị của biến x, y và collider
sẽ được thay đổi lại về trạng thái trước đó của Tank. Phương thức này thường được sử dụng khi xảy
ra va chạm hoặc khi cần phục hồi lại trạng thái của Tank để xử lý các trường hợp đặc biệt
.*/
void Tank::undo()
{
	x -= vx;
	collider.x = x;

	y -= vy;
	collider.y = y;
}

void Tank::respawn(int x, int y)
{
	this->x = x;
	this->y = y;
	hp = maxHp;
}

void Tank::respawn()
{
	x = respawnX;
	y = respawnY;
	hp = maxHp;
}

void Tank::reset()
{
	respawn();
	score = 0;
}

int Tank::getX()
{
	return x;
}

int Tank::getY()
{
	return y;
}

int Tank::getWidth()
{
	return width;
}

int Tank::getHeight()
{
	return height;
}

int Tank::getHp()
{
	return hp;
}

int Tank::getMaxHp()
{
	return maxHp;
}

unsigned int Tank::getScore()
{
	return score;
}

direction Tank::getDirection()
{
	return dir;
}

SDL_Rect Tank::getCollider()
{
	return collider;
}

void Tank::decreaseHp()
{
	hp--;
}

void Tank::increaseScore()
{
	score++;
}

void Tank::initTexture(std::string path)
{
	texture.loadPNG(path);
}

void Tank::render()
{
	texture.render(x, y, static_cast<double>(dir));
}

void Tank::clearButtonFlags()
{
	upButtonPressed = false;
	downButtonPressed = false;
	leftButtonPressed = false;
	rightButtonPressed = false;
}