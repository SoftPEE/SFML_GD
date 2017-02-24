#pragma once

#include <State.hpp>

#include <SFML\Graphics\Text.hpp>

class PauseState : public State
{
public:
  PauseState::PauseState(StateStack& stack, Context context);

  virtual void  draw();
  virtual bool  update(sf::Time dt);
  virtual bool  handleEvent(const sf::Event& event);

private:
  sf::Text      mPauseText;
  sf::Text      mInstructionText;
};