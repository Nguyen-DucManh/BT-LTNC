#include "Bullet.h"

const int Bullet::velocity = 10;//định nghĩa một hằng số tốc độ cho đối tượng đạn.
/*
đại diện cho tài nguyên hình ảnh và âm thanh được sử dụng bởi các đối tượng đạn trong trò chơi.
*/
Texture Bullet::texture{};
Sound Bullet::fireSound{};
Sound* Bullet::collisionSound = nullptr;


Bullet::Bullet(int fireButton)// khởi tạo một đối tượng đạn với nút bắn được chỉ định.
{
	this->fireButton = fireButton;// lưu trữ giá trị của nút bắn được chỉ định.
	reset();// khởi tạo lại
	//lưu trữ chiều rộng và chiều cao của đối tượng đạn.
	width = 6;
	height = 12;
	//xác định xem nút bắn có đang được nhấn hay không.
	fireButtonPressed = false;
	// lưu trữ số tick (thời gian tính bằng mili giây) kể từ lần bắn đạn cuối cùng và kể từ khi nút bắn được nhấn lần cuối
	shotTicks = 0;
	buttonTicks = 0;
}
// giải phóng bộ nhớ cho đối tượng đạn khi nó được hủy.
Bullet::~Bullet()
{
}
/*
xử lý sự kiện được truyền vào qua tham số e. Nếu sự kiện là phím được nhấn (SDL_KEYDOWN) và phím đó là nút bắn được chỉ định
(fireButton) thì biến fireButtonPressed được đặt là true. Nếu sự kiện là phím được thả ra (SDL_KEYUP) và phím đó là nút bắn
được chỉ định (fireButton) thì biến fireButtonPressed được đặt là false.
*/
void Bullet::handleEvent(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == fireButton) fireButtonPressed = true;
	else if (e.type == SDL_KEYUP && e.key.keysym.sym == fireButton) fireButtonPressed = false;
}
//thiết lập lại trạng thái ban đầu của đối tượng đạn.
void Bullet::reset()
{
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	collider = { 0,0,0,0 };

	dir = UP;

	exist = false;
}

void Bullet::fire(Tank *tank, int delay)
{
	// kiểm tra xem nút bắn đã ấn chưa
	if (fireButtonPressed)
	{
		// lấy thời điểm hiện tại	
		buttonTicks = SDL_GetTicks();
//Kiểm tra xem đạn đã bị hủy chưa (exist == false) và 
		//thời gian kể từ lần bắn trước đó đã vượt qua độ trễ cho phép (buttonTicks - delay > shotTicks).
		
		if (!exist && buttonTicks - delay > shotTicks)
		{
			//Cập nhật thời điểm bắn mới nhất (shotTicks) thành thời điểm hiện tại (buttonTicks).
			shotTicks = buttonTicks;
			//Thiết lập hướng đi của đạn dựa trên hướng đi của tank được truyền vào
			dir = tank->dir;
			
			//Tính toán vị trí của đạn dựa trên vị trí của tank và hướng đi của nó
			switch (dir)
			{
				case UP:
				{
					x = tank->x + tank->width / 2 - width / 2;
					y = tank->y - height;
					break;
				}
				case DOWN:
				{
					x = tank->x + tank->width / 2 - width / 2;
					y = tank->y + tank->height;
					break;
				}
				case LEFT:
				{
					x = tank->x - height;
					y = tank->y + tank->height / 2 - width / 2;
					break;
				}
				case RIGHT:
				{
					x = tank->x + tank->width;
					y = tank->y + tank->height / 2 - width / 2;
				}
			}
			/*
			Các lệnh này được sử dụng để thiết lập tọa độ ban đầu của đối tượng đạn. Đầu tiên,
			chúng ta xác định hướng bắn (UP, DOWN, LEFT, RIGHT) bằng cách truy cập giá trị của biến dir.
			Sau đó, chúng ta sử dụng một câu lệnh switch-case để thiết lập tọa độ ban đầu của đối tượng đạn dựa trên
			hướng bắn được xác định. Cụ thể, nếu hướng bắn là UP, tọa độ x sẽ là vị trí x của xe tăng cộng với một nửa
			chiều rộng của nó trừ đi một nửa chiều rộng của đạn, và tọa độ y sẽ là vị trí y của xe tăng trừ đi chiều cao
			\của đạn. Tương tự, nếu hướng bắn là DOWN, chúng ta cộng chiều cao của xe tăng vào tọa độ y của đạn. Nếu
			hướng bắn là LEFT, chúng ta trừ chiều rộng của đạn vào tọa độ x của xe tăng và cộng một nửa chiều cao của
			nó vào tọa độ y của đạn. Nếu hướng bắn là RIGHT, chúng ta cộng chiều rộng của xe tăng vào tọa độ x của đạn
			và cộng một nửa chiều cao của nó vào tọa độ y của đạn.
			*/
			//Thiết lập biến exist thành true để đánh dấu rằng đạn đang tồn tại trên màn hình.
			exist = true;
			// phát âm thanh bắn
			fireSound.play();
			//Thiết lập đối tượng va chạm (collider) của đạn bằng cách thiết lập tọa độ x và y của nó. 
			collider.x = x;
			collider.y = y;

			//cập nhật kích thước và vị trí của hộp va chạm (collider box) dựa trên hướng bắn của đạn.
			/*
			Nếu hướng bắn của đạn là UP hoặc DOWN, đó là khi đạn di chuyển theo chiều dọc, thì chiều rộng
			và chiều cao của hộp va chạm sẽ được thiết lập là width và height tương ứng. Ngược lại, nếu hướng
			bắn của đạn là LEFT hoặc RIGHT, tức là đạn di chuyển theo chiều ngang, thì chiều rộng và chiều cao
			của hộp va chạm sẽ được đổi chỗ (swap) để phù hợp với hướng di chuyển. Theo đó, chiều rộng sẽ là height
			và chiều cao sẽ là width.
			Lý do để thay đổi kích thước của hộp va chạm này là để phù hợp với hình dạng của đạn khi nó di chuyển.
			Nếu không có điều kiện này, đối tượng va chạm có thể không được xác định đúng và có thể gây ra các lỗi 
			trong việc xử lý va chạm với các đối tượng khác.
			*/
			if (dir == UP || dir == DOWN)
			{
				collider.w = width;
				collider.h = height;
			}
			else if (dir == LEFT || dir == RIGHT)
			{
				collider.w = height;
				collider.h = width;
			}

			//Thiết lập tốc độ của đạn dựa trên hướng đi của nó. Điều này được thực hiện bằng cách sử dụng
			//một câu lệnh switch để thiết lập vx và vy (vận tốc theo chiều x và y) của đạn.
			switch (dir)
			{
				case UP:
				{
					vy -= velocity;
					break;
				}
				case DOWN:
				{
					vy += velocity;
					break;
				}
				case LEFT:
				{
					vx -= velocity;
					break;
				}
				case RIGHT:
				{
					vx += velocity;
					break;
				}
			}
		}
	}
}
/*
Hàm này cập nhật vị trí của đối tượng đạn bằng cách thay đổi giá trị của biến x và y dựa trên vận tốc (vx và vy)
của đối tượng. Nó cũng cập nhật hình dạng của vùng va chạm (collider) của đối tượng dựa trên vị trí mới của đối tượng.
Nếu đối tượng vượt quá ranh giới của màn hình chơi (x hoặc y nhỏ hơn 0 hoặc lớn hơn 768), thì hàm sẽ gọi hàm reset() 
để đưa đối tượng trở về vị trí ban đầu và phát âm thanh va chạm (collisionSound).
*/
void Bullet::move()
{
	x += vx;
	collider.x = x;

	if ((x < 0) || (x + width > 768))
	{
		reset();
		collisionSound->play();
	}

	y += vy;
	collider.y = y;

	if ((y < 0) || (y + height > 768))
	{
		reset();
		collisionSound->play();
	}
}
// Hàm này trả về giá trị true nếu đối tượng đạn vẫn tồn tại trên màn hình chơi, ngược lại trả về false.
//Điều này được xác định bởi biến exist.
bool Bullet::doesExist()
{
	return exist;
}
// Hàm này trả về hướng di chuyển của đối tượng đạn (được lưu trữ trong biến dir).
direction Bullet::getDirection()
{
	return dir;
}
//Hàm này trả về hình dạng vùng va chạm (collider) của đối tượng đạn dưới dạng một cấu trúc dữ liệu SDL_Rect.
SDL_Rect Bullet::getCollider()
{
	return collider;
}
/*
khởi tạo đạn với các thông tin cần thiết như đường dẫn đến hình ảnh của đạn, đường dẫn đến file âm thanh khi bắn đạn
và con trỏ tới âm thanh khi đạn va chạm với vật thể khác. Trong phương thức này, hình ảnh của đạn được tải lên từ
đường dẫn được truyền vào và lưu vào biến texture, âm thanh bắn đạn được tải lên từ đường dẫn được truyền vào và 
lưu vào biến fireSound, và con trỏ tới âm thanh khi đạn va chạm được lưu vào biến collisionSound.
*/
void Bullet::init(std::string texturePath, std::string fireSoundPath, Sound* collisionSoundPtr)
{
	texture.loadPNG(texturePath);
	fireSound.loadWAV(fireSoundPath);
	collisionSound = collisionSoundPtr;
}
//hiển thị đạn trên màn hình game nếu đạn đang tồn tại (exist = true). Nó sử dụng hàm render của đối tượng 
// texture để vẽ đạn lên màn hình với tọa độ x và y của đạn,
//và hướng di chuyển của đạn (dir) được truyền vào dưới dạng một giá trị kiểu số nguyên.
void Bullet::render()
{
	if(exist) texture.render(x, y, static_cast<double>(dir));
}
/*
 đặt lại trạng thái của cờ fireButtonPressed sang giá trị false. Cờ này được sử dụng để kiểm tra xem nút bắn đạn có được 
 nhấn hay không. Bằng cách đặt lại giá trị của cờ này sang false, chúng ta đảm bảo rằng khi người chơi không nhấn
 nút bắn đạn, đạn sẽ không được bắn ra.*/
void Bullet::clearButtonFlag()
{
	fireButtonPressed = false;
}