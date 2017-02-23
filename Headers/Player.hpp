#pragma once

#include <CommandQueue.hpp>
#include <Command.hpp>

#include <SFML\Window\Event.hpp>

#include <map>

class Player
{
public:
  enum Action
  {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown
  };

public:
  Player::Player();

  void                  assignKey(Action action, sf::Keyboard::Key key);
  sf::Keyboard::Key     getAssignedKey(Action action) const;

  void                  handleEvent(const sf::Event& event, CommandQueue& commands);
  void                  handleRealTimeInput(CommandQueue& commands);

private:
  void                  initializeActions();
  static bool           isRealTimeAction(Action action);

private:
  std::map<sf::Keyboard::Key, Action>   mKeyBindings;
  std::map<Action, Command>             mActionBindings;

};