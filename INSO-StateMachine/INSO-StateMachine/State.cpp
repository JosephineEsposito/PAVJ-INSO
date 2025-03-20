#include <Windows.h>

#include "Transition.h"
#include "StateName.h"


State::State() :
  m_pCurrentState(nullptr),
  m_pNextState(nullptr),
  m_iCondition(0)
{
}



#pragma region | Getters

EState* State::GetCurrentState() const
{
  return m_pCurrentState;
}
EState* State::GetNextState() const
{
  return m_pNextState;
}
int State::GetCondition() const
{
  return m_iCondition;
}

#pragma endregion

#pragma region | Setters

void State::SetCurrentState(EState* _state)
{
  m_pCurrentState = _state;
}
void State::SetNextState(EState* _state)
{
  m_pNextState = _state;
}
void State::SetCondition(int& _condition)
{
  m_iCondition = _condition;
}

#pragma endregion



bool State::Transition(int& _action)
{
  if (m_iCondition != _action)
  {
    return;
  }


}