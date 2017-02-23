#include <Game.hpp>
#include <CommandQueue.hpp>
#include <Command.hpp>

#include <SFML\Window\Event.hpp>

#include <iostream>

//STATIC MEMBER 
float       Game::PLAYERSPEED       = 100.0;
sf::Time    Game::TIME_PER_FRAME    = sf::Time(sf::seconds(1.0/60.0));

Game::Game( )
  : mWindow{ sf::VideoMode(640,480), "SFML Application" }
  , mWorld{mWindow }
  , mIsMovingUp{false }
  , mIsMovingDown{false }
  , mIsMovingLeft{false }
  , mIsMovingRight{false }
  , mStatisticFont{ }
  , mStatisticText{ }
  , mStatisticTime{sf::Time::Zero }
  , mStatisticFramesPerSeconds{ 0 }
  , mPlayer{ }
{
  mStatisticFont.load(Fonts::default, "Media//Sansation.ttf");
  mStatisticText.setFont(mStatisticFont.get(Fonts::default));
  mStatisticText.setPosition(5.0f,5.0f);
  mStatisticText.setCharacterSize(10);
}


Game::~Game( )
{

}


void Game::run( )
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen())
  {
    processEvents();
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;

    while (timeSinceLastUpdate > TIME_PER_FRAME)
    {
      timeSinceLastUpdate -= TIME_PER_FRAME;
      processEvents();
      update(TIME_PER_FRAME);
    }
    updateStatistics(elapsedTime);
    render();
  }
}


void Game::processEvents( )
{
  CommandQueue& commands = mWorld.getCommandQueue();
  sf::Event event;

  while (mWindow.pollEvent(event))
  {
    
    mPlayer.handleEvent(event, commands);
    if (event.type == sf::Event::Closed)
      mWindow.close();
    
  }

  mPlayer.handleRealTimeInput(commands);
}


void Game::update(sf::Time dt)
{
 /* sf::Vector2f movement(0.f,0.f);
  if (mIsMovingUp)
    movement.y -= PLAYERSPEED;
  if (mIsMovingDown)
    movement.y += PLAYERSPEED;
  if (mIsMovingLeft)
    movement.x -= PLAYERSPEED;
  if (mIsMovingRight)
    movement.x += PLAYERSPEED;

  mPlayer.move(movement * dt.asSeconds());*/
  mWorld.update(dt);
}


void Game::render( )
{
  mWindow.clear();
  mWorld.draw();
  mWindow.setView(mWindow.getDefaultView());
  mWindow.draw(mStatisticText);
  mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
  if (key == sf::Keyboard::W)
    mIsMovingUp = isPressed;
  else if (key == sf::Keyboard::S)
    mIsMovingDown = isPressed;
  else if (key == sf::Keyboard::A)
    mIsMovingLeft = isPressed;
  else if (key == sf::Keyboard::D)
    mIsMovingRight = isPressed;
}

void Game::updateStatistics(sf::Time dt)
{
  mStatisticTime += dt;
  mStatisticFramesPerSeconds += 1;
  
  if (mStatisticTime >= sf::Time(sf::seconds(1.0)))
  {
    mStatisticText.setString("Frames / Seconds " + std::to_string(mStatisticFramesPerSeconds) + "\n"
    + "Time / Update " + std::to_string(mStatisticTime.asMicroseconds() / mStatisticFramesPerSeconds) + "ms");

    mStatisticTime -= sf::seconds(1.0);
    mStatisticFramesPerSeconds = 0;
  }
}
