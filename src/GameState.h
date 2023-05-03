#pragma once // được sử dụng để đảm bảo rằng tệp mã được bao gồm chỉ được biên dịch một lần.
#include "State.h"
#include "Game.h"

class Game;

class GameState : public State
{
public:
	GameState(Game *game); //là hàm tạo của lớp GameState, nhận một tham số là con trỏ đến đối tượng lớp Game.
	~GameState();//là hàm hủy của lớp GameState.
	virtual void handleEvents(SDL_Event &e);
	//là một phương thức ảo (virtual) được định nghĩa trong lớp cha State.
	//Phương thức này được gọi để xử lý các sự kiện từ SDL_Event(phím được nhấn, chuột được di chuyển, ...)
	virtual void logic();// là một phương thức ảo (virtual) được định nghĩa trong lớp cha State.
	//Phương thức này được gọi để tính toán các thay đổi trong trạng thái của trò chơi.
	virtual void render();//là một phương thức ảo (virtual) được định nghĩa trong lớp cha State. 
	//Phương thức này được gọi để vẽ các đối tượng và trạng thái của trò chơi trên màn hình.
private:
	Game *game;//là một thuộc tính của lớp GameState để lưu trữ đối tượng lớp Game.
};

