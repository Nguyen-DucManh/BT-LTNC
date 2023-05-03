#pragma once
#include "Game.h"

class Sound
{
public:
	//khơi tạo và hủy hàm
	Sound();
	~Sound();
	/*
	Trong các ứng dụng game hoặc âm nhạc, các file âm thanh có thể có kích thước khá lớn và chúng được tải lên bộ nhớ để phát lại.
	Nếu không giải phóng bộ nhớ được dùng để lưu trữ các file âm thanh khi chúng không còn cần thiết, 
	thì nó sẽ dẫn đến tình trạng leak bộ nhớ và gây ra sự chậm trễ và hiệu suất không mong muốn của ứng dụng. 
	Do đó, việc giải phóng bộ nhớ là rất quan trọng để tối ưu hóa hiệu suất của ứng dụng
	*/ 

	void clean();//giải phóng bộ nhớ đối với âm thanh.
	void loadWAV(std::string path);//phương thức để tải tệp âm thanh có đường dẫn được chỉ định.
	void play();// phát

private:
	Mix_Chunk *sound;//con trỏ đến một đối tượng Mix_Chunk trong thư viện SDL Mixer, đại diện cho âm thanh được tải.
};