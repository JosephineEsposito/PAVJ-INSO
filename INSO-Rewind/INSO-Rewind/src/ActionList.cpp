#include "../libs/ActionList.h"

int ActionList::size = 0;
int ActionList::maxsize = 10;

ActionList::ActionList()
{
  ActionList::size = 0;
  ActionList::maxsize = 10;

  m_RootAction = nullptr;
  m_CurrentAction = nullptr;
}
ActionList::ActionList(Action* _root)
{
  ActionList::size = 0;
  ActionList::maxsize = 10;

  m_RootAction = _root;
  m_CurrentAction = m_RootAction;
}
ActionList::ActionList(Action* _root, int& _size)
{
  ActionList::size = 0;
  ActionList::maxsize = _size;

  m_RootAction = _root;
  m_CurrentAction = m_RootAction;
}


ActionList::~ActionList()
{
  ActionList::size = 0;
  ActionList::maxsize = 10;

  delete m_CurrentAction;
  delete m_RootAction;
}

void ActionList::push(Action* _action)
{
  if (_action)
  {
    m_CurrentAction->next = m_CurrentAction;
    m_CurrentAction = _action;
    ActionList::size++;
  }

  if (ActionList::size > ActionList::maxsize)
  {
    renew();
  }
}

void ActionList::renew()
{
  m_RootAction = m_RootAction->next;
}

void ActionList::clear()
{
  while (m_RootAction)
  {
    Action* node = m_RootAction;
    m_RootAction = m_RootAction->next;
    delete node;
    ActionList::size--;
  }
  m_CurrentAction = nullptr;
}