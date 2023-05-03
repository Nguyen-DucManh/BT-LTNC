#include "MapLoader.h"

/*
Tải vị trí và thông tin các đối tượng trên bản đồ từ tệp tin văn bản.
Các đối tượng bao gồm các thành phần như tường (Wall) và xe tăng (Tank).
*/

MapLoader::MapLoader()
{
}

MapLoader::MapLoader(std::string path)
{
	loadFromFile(path);
}

MapLoader::~MapLoader()
{
}
//
void MapLoader::loadFromFile(std::string path)
{
	file.open(path);

	if (file)
	{
		char c;//Biến lưu trữ ký tự đang được xem xét trong vòng lặp.
		int line = 0; // số dòng
		int row = 0;//số cột bản đồ
		int tankCounter = 0; // số xe tăng

		while (file.get(c))//Vòng lặp để duyệt qua từng ký tự trong tệp tin.
		{
			if (row < MAP_WIDTH/WALL_WIDTH && line < MAP_HEIGHT/WALL_HEIGHT && c != '\n')
				/*
				Kiểm tra xem ký tự đang xét có phải là một phần của các thành phần trên
				bản đồ hay không. Nếu đúng thì thực hiện các câu lệnh trong switch-case dưới đây.
				*/
			{
				switch (c)
				{
					case 'X':
					{
						wall.push_back(new Wall(64 * row, 64 * line)); //tường có thể phá
						break;
					}
					case '#':
					{
						wall.push_back(new Wall(64 * row, 64 * line, false));// không phá
						break;
					}
					//Nếu ký tự đang xét là một trong các ký tự biểu thị hướng của xe tăng,
					// thì tạo một đối tượng xe tăng (Tank) mới và đưa vào danh sách tank.
					//Các đối tượng xe tăng này có các thuộc tính như vị trí ban đầu, hướng đi và các phím điều khiển.
					case '^':
					case 'v':
					case '<':
					case '>':
					{
						if (tankCounter == 0)
						{
							// nếu số xe tăng là 0, tạo xe tăng mới với vị trí và hướng di chuyển tương ứng
							switch (c)
							{
								case '^':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, UP, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT));
									break;
								}
								case 'v':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, DOWN, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT));
									break;
								}
								case '<':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, LEFT, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT));
									break;
								}
								case '>':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, RIGHT, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT));
									break;
								}
							}

						}
						//tương tự với số xe tăng là 1
						else if (tankCounter == 1)
						{
							switch (c)
							{
								case '^':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, UP, SDLK_w, SDLK_s, SDLK_a, SDLK_d));
									break;
								}
								case 'v':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, DOWN, SDLK_w, SDLK_s, SDLK_a, SDLK_d));
									break;
								}
								case '<':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, LEFT, SDLK_w, SDLK_s, SDLK_a, SDLK_d));
									break;
								}
								case '>':
								{
									tank.push_back(new Tank(64 * row + 2, 64 * line + 2, RIGHT, SDLK_w, SDLK_s, SDLK_a, SDLK_d));
									break;
								}
							}
						}
						tankCounter++;
						break;
					}
				}
			}
// xử lý các ký tự xuống dòng trong tệp đang được đọc. Khi đọc đến ký tự xuống dòng ('\n'),
//  nó sẽ tăng biến đếm dòng (line) lên 1 
//và đặt lại biến đếm cột (row) thành -1 để bắt đầu đếm từ đầu dòng tiếp theo. Sau đó, biến 
			//đếm cột được tăng lên 1 để đếm ký tự tiếp theo trên dòng đó.
			else if (c == '\n')
			{
				line++;
				row = -1;
			}
			row++;
		}

		//TO-DO: Exception when tankCounter < 2
	}
	else
	{
		std::cout << "File could not be opened" << std::endl;
	}

	file.close();
}
/*
 giải phóng bộ nhớ đã được phân bổ động cho các đối tượng trong vector wall và tank. 
 Trong đó, vòng lặp for được sử dụng để duyệt qua các phần tử trong vector wall và tank, 
 sau đó sử dụng toán tử delete để giải phóng bộ nhớ của từng đối tượng.
*/
void MapLoader::freeDynamicAllocatedMemory()
{
	for (int i = 0; i < static_cast<int>(wall.size()); i++)
	{
		delete wall[i];
	}

	for (int i = 0; i < static_cast<int>(tank.size()); i++)
	{
		delete tank[i];
	}
}
/*
truy xuất các đối tượng trong vector wall và tank. Trong đó, các đối tượng được truyền vào 
thông qua tham số tham chiếu arg, và hàm sử dụng vòng lặp for để duyệt qua các phần tử trong 
vector wall và tank, sau đó thêm các đối tượng vào vector arg.
Các đối tượng được truyền vào vector arg vẫn được giữ nguyên và không bị giải phóng bộ nhớ.
*/
void MapLoader::getWalls(std::vector<Wall*> &arg)
{
	for (auto x : wall)
	{
		arg.push_back(x);
	}
}

void MapLoader::getTanks(std::vector<Tank*> &arg)
{
	for (auto x : tank)
	{
		arg.push_back(x);
	}
}