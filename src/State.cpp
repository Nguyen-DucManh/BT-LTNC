#include "State.h"
//quản lý trạng thái của trò chơi, tức là trò chơi hiện đang ở màn hình tiêu đề, chế độ chơi trò chơi hoặc một trạng thái khác nào đó.
SDL_Renderer* State::renderer{};
StateEnum State::currentState = TITLE;
StateEnum State::nextState = NONE;

void State::setRenderer(SDL_Renderer *r)
{
	renderer = r;
}

void State::setCurrentState(StateEnum arg)//đại diện cho trạng thái hiện tại của trò chơi.
{
	currentState = arg;
}

void State::setNextState(StateEnum arg)//đại diện cho trạng thái kế tiếp của trò chơi.
{
	nextState = arg;
}

StateEnum State::getCurrentState()
{
	return currentState;
}

StateEnum State::getNextState()
{
	return nextState;
}