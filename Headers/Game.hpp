#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Graphics\Text.hpp>

#include <World.hpp>
#include <Player.hpp>

class Game
{
private:
  sf::RenderWindow  mWindow;
  World             mWorld;
  Player            mPlayer;

  FontHolder        mStatisticFont;
  sf::Text          mStatisticText;
  sf::Time          mStatisticTime;
  unsigned int      mStatisticFramesPerSeconds;

  bool              mIsMovingUp;
  bool              mIsMovingDown;
  bool              mIsMovingLeft;
  bool              mIsMovingRight;

public:
  static float        PLAYERSPEED;
  static sf::Time     TIME_PER_FRAME;

public:
  Game( );
  ~Game( );

  void run( );



private:
  void processEvents( );
  void update(sf::Time dt);
  void render( );

  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
  void updateStatistics(sf::Time dt);

};

