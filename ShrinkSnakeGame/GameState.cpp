#include "GameState.h"

state GameState::getState()
{
    return nowState;
}

void GameState::setState(state nextState)
{
    nowState = nextState;
}
