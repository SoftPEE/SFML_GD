#pragma once

#include <StateStack.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifier.hpp>
#include <Player.hpp>

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Text.hpp>

class Application
{
public:
  Application::Application();
  void        run();

private:
  void        update(sf::Time dt);
  void        processInput();
  void        render();

  void        registerStates();
  void        updateStatistics(sf::Time dt);

private:
  static const sf::Time TIME_PER_FRAME;

  sf::RenderWindow  mWindow;
  StateStack        mStateStack;
  TextureHolder     mTextures;
  FontHolder        mFonts;
  Player            mPlayer;

  sf::Text          mStatisticText;
  sf::Time          mStatisticTime;
  unsigned int      mStatisticFramesPerSeconds;

};