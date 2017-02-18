#include <Game.hpp>

//STATIC MEMBER 
float       Game::PLAYERSPEED       = 100.0;
sf::Time    Game::TIME_PER_FRAME    = sf::Time(sf::seconds(1.0/60.0));

Game::Game( )
  : mWindow{ sf::VideoMode(640,480), "SFML Application" }
  , mPlayer{ }
  , mIsMovingUp{false }
  , mIsMovingDown{false }
  , mIsMovingLeft{false }
  , mIsMovingRight{false }
{
  mPlayer.setRadius(40.f);
  mPlayer.setPosition(100.f, 100.f);
  mPlayer.setFillColor(sf::Color::Cyan);
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
    timeSinceLastUpdate += clock.restart();

    while (timeSinceLastUpdate > TIME_PER_FRAME)
    {
      timeSinceLastUpdate -= TIME_PER_FRAME;
      processEvents();
      update(TIME_PER_FRAME);
    }
    render();
  }
}


void Game::processEvents( )
{
  sf::Event event;

  while (mWindow.pollEvent(event))
  {
    switch (event.type)
    {
      case sf::Event::KeyPressed: 
        handlePlayerInput(event.key.code, true); 
        break;
      case sf::Event::KeyReleased: 
        handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        mWindow.close();
    }
  }
}


void Game::update(sf::Time dt)
{
  sf::Vector2f movement(0.f,0.f);
  if (mIsMovingUp)
    movement.y -= PLAYERSPEED;
  if (mIsMovingDown)
    movement.y += PLAYERSPEED;
  if (mIsMovingLeft)
    movement.x -= PLAYERSPEED;
  if (mIsMovingRight)
    movement.x += PLAYERSPEED;

  mPlayer.move(movement * dt.asSeconds());
}


void Game::render( )
{
  mWindow.clear();
  mWindow.draw(mPlayer);
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
