#pragma once

#include <memory>

#include <StateIdentifiers.hpp>
#include <ResourceIdentifier.hpp>
#include <ResourceHolder.hpp>

#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>

namespace sf
{
  class RenderWindow;
}

class StateStack;
class Player;

class State
{
public:
  using Ptr = std::unique_ptr<State>;
  struct Context
  {
    Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);
    sf::RenderWindow* window;
    TextureHolder*    textures;
    FontHolder*       fonts;
    Player*           player;
  };

public:
  State::State(StateStack& stack, Context context);
  virtual State::~State();

  virtual void draw() = 0;
  virtual bool update(sf::Time dt) = 0;
  virtual bool handleEvent(const sf::Event& event) = 0;

protected:
  void    requestStackPush(States::ID stateID);
  void    requestStackPop();
  void    requestStateClear();

  Context getContext() const;

private:
  StateStack* mStack;
  Context     mContext;
};