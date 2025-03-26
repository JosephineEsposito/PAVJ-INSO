#pragma once

#include "Action.h"

class ActionList
{
public:
  Action* m_RootAction;

  Action* m_CurrentAction;



  static int size;
  static int maxsize;


  ActionList();
  ActionList(Action* _root);
  ActionList(Action* _root, int& _size);

  ~ActionList();


  void push(Action* _action);
  void renew();
  void clear();
};

