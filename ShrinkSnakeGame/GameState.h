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
		: nowState(state::Gaming) // Ĭ�ϳ�ʼ��Ϊ Gaming ״̬
	{
	}

    GameState(const GameState& other)
        : nowState(other.nowState) // �������캯��
    {
    }

    GameState& operator=(const GameState& other)
    {
        if (this != &other) // �������Ҹ�ֵ
        {
            nowState = other.nowState; // ��ֵ������
        }
        return *this;
    }

	state getState();
    void setState(state nextState);
};

