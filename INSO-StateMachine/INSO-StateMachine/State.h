#pragma once

#include <Windows.h>
#include "StateName.h"

class State
{
private:
  EState* m_pState;
  State* m_pNextState;

  int m_iCondition;

public:
  // Default constructor
  State();

  // Get current state
  EState* GetCurrentState() const;
  // Get next state
  EState* GetNextState() const;
  // Get condition for transition
  int GetCondition() const;

  // Set current state
  void SetCurrentState(EState* _state);
  // Set next state
  void SetNextState(EState* _state);
  // Set condition for transition
  void SetCondition(int& _condition);

  // Performs the transition between the current state and the next state
  bool Transition(int& _action);
};

