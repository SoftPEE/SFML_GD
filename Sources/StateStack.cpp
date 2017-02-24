#include <StateStack.hpp>

StateStack::StateStack(State::Context context)
  : mContext{context }
  , mStack{ }
  , mPendingList{ }
  , mFactories{ }
{

}


void StateStack::update(sf::Time dt)
{
  for (auto itr = mStack.rbegin(); itr != mStack.rend(); itr++)
    if (!(*itr)->update(dt))
      return;

  applyPenndingChanges();
}


void StateStack::draw( )
{
  for(auto& state : mStack)
    state->draw();
}


void StateStack::handleEvent(const sf::Event& event)
{
  for (auto itr = mStack.rbegin(); itr != mStack.rend(); itr++)
    if(!(*itr)->handleEvent(event))
      return;
  
  applyPenndingChanges();
}


void StateStack::pushState(States::ID stateID)
{
  mPendingList.push_back(PendingChange(Push, stateID));
}


void StateStack::popState( )
{
  mPendingList.push_back(PendingChange(Pop));
}


void StateStack::clearStates( )
{
  mPendingList.push_back(PendingChange(Clear));
}


bool StateStack::isEmpty( ) const
{
  return mStack.empty();
}


State::Ptr StateStack::createState(States::ID stateID)
{
  auto found = mFactories.find(stateID);

  //Vergessen State zu registrieren
  //Application.cpp >>registerState()<<
  assert(found != mFactories.end());

  return found->second();
}


void StateStack::applyPenndingChanges( )
{
  for (auto& change : mPendingList)
  {
    switch (change.action)
    {
    case Push:
      mStack.push_back(createState(change.stateID));
      break;
    case Pop:
      mStack.pop_back();
      break;
    case Clear:
      mStack.clear();
      break;
    }
  }
  mPendingList.clear();
}