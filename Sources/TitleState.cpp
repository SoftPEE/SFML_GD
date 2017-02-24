#include <TitleState.hpp>
#include <Utilities.hpp>

#include <SFML\Graphics\RenderWindow.hpp>

TitleState::TitleState(StateStack& stack, Context context)
  : State{stack, context }
  , mBackgroundSprite{ }
  , mText{ }
  , mShowText{true }
  , mTextEffectTime{ }
{
  mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));
  mText.setFont(context.fonts->get(Fonts::default));
  mText.setCharacterSize(20);
  mText.setString("Weiter mit beliebiger Taste");
  setOrigin(mText);
  mText.setPosition(context.window->getView().getSize() / 2.f);
}


void TitleState::draw( )
{
  sf::RenderWindow& window = *getContext().window;

  window.draw(mBackgroundSprite);

  if (mShowText)
    window.draw(mText);
}


bool TitleState::update(sf::Time dt)
{
  mTextEffectTime += dt;

  if (mTextEffectTime >= sf::seconds(0.5f))
  {
    mShowText = !mShowText;
    mTextEffectTime = sf::Time::Zero;
  }

  return true;
}


bool TitleState::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    requestStackPop();
    requestStackPush(States::Game);
  }

  return true;
}