#include "../libs/Action.h"
#include "../libs/tigr.h"

Action::Action()
{
  m_key = TKey::TK_DOT;
  next = nullptr;
}

Action::Action(unsigned& _key)
{
  m_key = _key;
  next = nullptr;
}
