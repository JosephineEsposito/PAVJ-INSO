#pragma once

class Action
{
public:
  unsigned m_key;
  Action* next;

  Action();
  Action(unsigned& _key);
};

