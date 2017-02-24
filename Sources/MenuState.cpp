#include <MenuState.hpp>
#include <Utilities.hpp>

#include <SFML\Graphics\RenderWindow.hpp>

MenuState::MenuState(StateStack& stack, Context context)
  : State{stack, context }
  , mBackgroundSprite{ }
  , mOptions{ }
  , mOptionIndex{ 0 }
{
  sf::Texture& texture  = context.textures->get(Textures::TitleScreen);
  sf::Font& font        = context.fonts->get(Fonts::default);

  mBackgroundSprite.setTexture(texture);

  sf::Text playOption;
  playOption.setFont(font);
  playOption.setString("Play");
  setOrigin(playOption);
  playOption.setPosition(context.window->getView().getSize() / 2.f);

  sf::Text exitOption;
  exitOption.setFont(font);
  exitOption.setString("Exit");
  setOrigin(exitOption);
  exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.0f, 30.0f));

  mOptions.push_back(playOption);
  mOptions.push_back(exitOption);

  updateOptionText();
}


bool MenuState::update(sf::Time dt)
{
  return true;
}


bool MenuState::handleEvent(const sf::Event& event)
{
  if (event.type != sf::Event::KeyPressed)
    return false;

  if (event.key.code == sf::Keyboard::Return)
  {
    if (mOptionIndex == Play)
    {
      requestStackPop();
      requestStackPush(States::Game);
    }
    else if (mOptionIndex == Exit)
      requestStackPop();
  }
  else if (event.key.code == sf::Keyboard::Up)
  {
    if (mOptionIndex > 0)
      mOptionIndex--;
    else
      mOptionIndex =  mOptions.size() -1;

    updateOptionText();
  }
  else if (event.key.code == sf::Keyboard::Down)
  {
    if (mOptionIndex < (mOptions.size() -1))
      mOptionIndex++;
    else
      mOptionIndex = 0;

    updateOptionText();
  }

  return true;
}


void MenuState::draw( )
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(mBackgroundSprite);
  
  for(auto& option : mOptions)
    window.draw(option);
}


void MenuState::updateOptionText( )
{
  if (mOptions.empty())
    return;

  for (auto& text : mOptions)
    text.setFillColor(sf::Color::White);

  mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}