#include <Player.hpp>
#include <Aircraft.hpp>

#include <iostream>
#include <algorithm>

struct AircraftMover
{
  AircraftMover(float vx, float vy)
    : velocity(vx, vy)
  {
  }

  void operator() (Aircraft& aircraft, sf::Time dt) const
  {
    aircraft.accelerator(velocity * dt.asSeconds());
  }

  sf::Vector2f velocity;
};


Player::Player( )
  : mKeyBindings{ }
  , mActionBindings{ }
{
  mKeyBindings[sf::Keyboard::Left] = MoveLeft;
  mKeyBindings[sf::Keyboard::Right] = MoveRight;
  mKeyBindings[sf::Keyboard::Up] = MoveUp;
  mKeyBindings[sf::Keyboard::Down] = MoveDown;
  
  initializeActions();

  for (auto& action : mActionBindings)
  {
    action.second.category = Category::PlayerAircraft;
  }

}


void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
  {
    Command output;
    output.category = Category::PlayerAircraft;
    output.action = [](SceneNode& node, sf::Time dt)
    {
      std::cout << node.getPosition().x << ", " << node.getPosition().y << std::endl;
    };

    commands.push(output);
  }
}


void Player::handleRealTimeInput(CommandQueue& commands)
{
  for (auto& pair : mKeyBindings)
  {
    if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
      commands.push(mActionBindings[pair.second]);
  }
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
  for (auto itr = mKeyBindings.begin( ); itr != mKeyBindings.end( ); )
  {
    if (itr->second == action)
      mKeyBindings.erase(itr++);
    else
      itr++;
  }

  mKeyBindings[key] = action;
}


sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
  for (auto& key : mKeyBindings)
  {
    if (key.second == action)
      return key.first;
  }

  return sf::Keyboard::Unknown;
}


bool Player::isRealTimeAction(Action action)
{
  switch (action)
  {
  case MoveUp:
  case MoveDown:
  case MoveLeft:
  case MoveRight:
    return true;
    break;
  default:
    return false;
  }
}


void Player::initializeActions( )
{
  const float playerSpeed = 200.f;
  mActionBindings[MoveUp].action    = derivedAction<Aircraft>(AircraftMover(0.f,-playerSpeed));
  mActionBindings[MoveDown].action  = derivedAction<Aircraft>(AircraftMover(0.f,+playerSpeed));
  mActionBindings[MoveLeft].action  = derivedAction<Aircraft>(AircraftMover(-playerSpeed,0.f));
  mActionBindings[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed,0.f));
}