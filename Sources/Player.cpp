#include <Player.hpp>
#include <Aircraft.hpp>

#include <iostream>

struct AircraftMover
{
  AircraftMover(float vx, float vy)
    : velocity(vx, vy)
  {
  }

  void operator() (Aircraft& aircraft, sf::Time dt)
  {
    aircraft.accelerator(velocity);
  }

  sf::Vector2f velocity;
};

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

}