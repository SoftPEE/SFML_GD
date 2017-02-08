#pragma once
#include <SFML\Graphics.hpp>

class Game
{
public:
  Game( );
  ~Game( );

  void run( );

public:
  static float        PlayerSpeed;
  static sf::Time     TimePerFrame;

private:
  void processEvents( );
  void update(sf::Time dt);
  void render( );

  void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
  sf::RenderWindow mWindow;
  sf::CircleShape  mPlayer;

  bool             mIsMovingUp;
  bool             mIsMovingDown;
  bool             mIsMovingLeft;
  bool             mIsMovingRight;
};

