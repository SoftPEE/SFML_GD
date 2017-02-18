#pragma once
#include <SFML\Graphics.hpp>

class Game
{
private:
  sf::RenderWindow mWindow;
  sf::CircleShape  mPlayer;

  bool             mIsMovingUp;
  bool             mIsMovingDown;
  bool             mIsMovingLeft;
  bool             mIsMovingRight;

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

};

