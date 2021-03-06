#include <GameState.hpp>
#include <CommandQueue.hpp>
#include <Command.hpp>

#include <SFML\Window\Event.hpp>

GameState::GameState(StateStack& stack, Context context )
  : State{stack, context }
  , mWorld{*context.window, *context.fonts }
  , mPlayer{*context.player }
{
  
}


GameState::~GameState( )
{

}


bool GameState::update(sf::Time dt)
{
 
  mWorld.update(dt);

  CommandQueue& commands = mWorld.getCommandQueue();
  mPlayer.handleRealTimeInput(commands);

  return true;
}


bool GameState::handleEvent(const sf::Event& event)
{
  CommandQueue& commands = mWorld.getCommandQueue();
  mPlayer.handleEvent(event, commands);

  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    requestStackPush(States::Pause);
  return true;
}


void GameState::draw( )
{
  mWorld.draw();
}



