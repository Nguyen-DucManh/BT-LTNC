#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Wall.h"

class Wall;

// Lớp MapLoader để đọc dữ liệu bản đồ từ tệp tin bên ngoài

class MapLoader
{
public:
	MapLoader();// Hàm khởi tạo mặc định
	MapLoader(std::string path);// Hàm khởi tạo đọc bản đồ từ đường dẫn được chỉ định
	~MapLoader();// Hàm hủy
	void loadFromFile(std::string path);// Phương thức để tải bản đồ từ một tệp tin bên ngoài

	// Lấy địa chỉ của các đối tượng Tường và đưa vào vector mới
	void getWalls(std::vector<Wall*> &arg);

	// Lấy địa chỉ của các đối tượng Tank và đưa vào vector mới
	void getTanks(std::vector<Tank*> &arg);

	// Phương thức này có thể được sử dụng để giải phóng bộ nhớ được cấp phát động
	void freeDynamicAllocatedMemory();

private:
	std::ifstream file;// Tệp tin đang được đọc
	std::vector<Wall*> wall; // Danh sách các đối tượng Tường
	std::vector<Tank*> tank;// Danh sách các đối tượng Tank
};

