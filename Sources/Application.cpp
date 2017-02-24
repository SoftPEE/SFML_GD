#include <Application.hpp>
#include <State.hpp>

#include <TitleState.hpp>
#include <GameState.hpp>

//STATIC
const sf::Time Application::TIME_PER_FRAME = sf::Time(sf::seconds(1.0/60.0));

Application::Application( )
  : mWindow{ sf::VideoMode(640, 480), "SFML_Application" }
  , mTextures{ }
  , mFonts{ }
  , mPlayer{ }
  , mStateStack{State::Context(mWindow, mTextures, mFonts, mPlayer) }
  , mStatisticText{ }
  , mStatisticTime{ sf::Time::Zero }
  , mStatisticFramesPerSeconds{0 }
{
  mFonts.load(Fonts::default, "Media//Sansation.ttf");
  mTextures.load(Textures::TitleScreen, "Media//Textures//TitleScreen.png");

  mStatisticText.setFont(mFonts.get(Fonts::default));
  mStatisticText.setPosition(5.f,5.f);
  mStatisticText.setCharacterSize(10.f);

  registerStates();
  mStateStack.pushState(States::Title);
}


void Application::run( )
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (mWindow.isOpen())
  {
    processInput();
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;

    while (timeSinceLastUpdate > TIME_PER_FRAME)
    {
      timeSinceLastUpdate -= TIME_PER_FRAME;

      processInput();
      update(TIME_PER_FRAME);

      if (mStateStack.isEmpty())
        mWindow.close();
    }
    updateStatistics(elapsedTime);
    render();
  }
}


void Application::update(sf::Time dt)
{
  mStateStack.update(dt);
}


void Application::processInput( )
{
  sf::Event event;

  while (mWindow.pollEvent(event))
  {
    mStateStack.handleEvent(event);

    if (event.type == sf::Event::Closed)
      mWindow.close();
  }
  
}


void Application::render( )
{
  mWindow.clear();
  mStateStack.draw();
  mWindow.setView(mWindow.getDefaultView());
  mWindow.draw(mStatisticText);

  mWindow.display();
}


void Application::registerStates( )
{
  mStateStack.registerState<TitleState>(States::Title);
  //mStateStack.registerState<MenuState>(States::Menu);
  mStateStack.registerState<GameState>(States::Game);
  //mStateStack.registerState<PauseState>(States::Pause);
}


void Application::updateStatistics(sf::Time dt)
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