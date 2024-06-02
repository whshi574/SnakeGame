#pragma once
enum state 
{
	Gaming,
	GamePause,
	GameOver
};

class GameState
{
private:
	state nowState;
public:
	GameState()
		: nowState(state::Gaming) // 默认初始化为 Gaming 状态
	{
	}

    GameState(const GameState& other)
        : nowState(other.nowState) // 拷贝构造函数
    {
    }

    GameState& operator=(const GameState& other)
    {
        if (this != &other) // 避免自我赋值
        {
            nowState = other.nowState; // 赋值操作符
        }
        return *this;
    }

	state getState();
    void setState(state nextState);
};

