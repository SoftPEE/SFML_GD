#pragma once

#include <CommandQueue.hpp>

#include <SFML\Window\Event.hpp>

class Player
{
public:
  void handleEvent(const sf::Event& event, CommandQueue& commands);
  void handleRealTimeInput(CommandQueue& commands);
};