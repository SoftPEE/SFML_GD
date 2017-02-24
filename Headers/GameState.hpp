#pragma once

#include <World.hpp>
#include <Player.hpp>
#include <State.hpp>

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Text.hpp>

class GameState : public State
{
public:
  GameState(StateStack& stack, Context context );
  ~GameState( );

private:
  virtual bool handleEvent(const sf::Event& event );
  virtual bool update(sf::Time dt);
  void         draw( );

private:
  World             mWorld;
  Player&           mPlayer;
};

