#include "Sound.h"



Sound::Sound()
{
	sound = nullptr;
}

Sound::~Sound()
{
	clean();
}
/*
xóa các âm thanh hiện có bằng hàm clean(), sau đó nạp tệp âm thanh tại đường dẫn được truyền vào 
và lưu trữ nó trong biến con trỏ âm thanh của lớp.
*/
void Sound::loadWAV(std::string path)
{
	clean();
	sound = Mix_LoadWAV(path.c_str());
}

void Sound::clean()
{
	if (sound != nullptr)
	{
		Mix_FreeChunk(sound);
		sound = nullptr;
	}
}
//phát lại âm thanh được lưu trữ trong biến con trỏ âm thanh của lớp bằng cách sử dụng Mix_PlayChannel() từ thư viện SDL.
void Sound::play()
{
	Mix_PlayChannel(-1, sound, 0);
}