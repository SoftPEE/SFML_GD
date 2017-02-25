#include <MenuState.hpp>
#include <Utilities.hpp>
#include <Button.hpp>

#include <SFML\Graphics\RenderWindow.hpp>

MenuState::MenuState(StateStack& stack, Context context)
  : State{stack, context }
  , mBackgroundSprite{ }
  , mGUIContainer{ }
{
  sf::Texture& texture  = context.textures->get(Textures::TitleScreen);
  sf::Font& font        = context.fonts->get(Fonts::default);

  mBackgroundSprite.setTexture(texture);
  
  auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  auto settingButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);

  playButton->setPosition(100,250);
  playButton->setText("Play");
  playButton->setCallback([this]( )
  {
    requestStackPop();
    requestStackPush(States::Game);
  });

  exitButton->setPosition(100,350);
  exitButton->setText("Exit");
  exitButton->setCallback(std::bind(&MenuState::State::requestStackPop, this));

  settingButton->setPosition(100,300);
  settingButton->setText("Einstellungen");
  settingButton->setCallback(std::bind(&MenuState::State::requestStackPush, this, States::Setting));

  mGUIContainer.pack(playButton);
  mGUIContainer.pack(settingButton);
  mGUIContainer.pack(exitButton);
}


bool MenuState::update(sf::Time dt)
{
  return true;
}


bool MenuState::handleEvent(const sf::Event& event)
{
  mGUIContainer.handleEvent(event);

  return true;
}


void MenuState::draw( )
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(mBackgroundSprite);
  window.draw(mGUIContainer);
}
