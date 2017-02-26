#include <PauseState.hpp>
#include <utilities.hpp>

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

PauseState::PauseState(StateStack& stack, Context context)
  : State{stack, context }
  , mPauseText{ }
  , mInstructionText{ }
{
  sf::Vector2f viewSize = context.window->getView().getSize();
  sf::Font& font = context.fonts->get(Fonts::default);

  mPauseText.setFont(font);
  mInstructionText.setFont(font);

  mPauseText.setString("Spiel pausiert");
  mPauseText.setCharacterSize(50);
  centerOrigin(mPauseText);
  mPauseText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

  mInstructionText.setString("Backspace um forzufahren, Esc zum Beenden");
  mInstructionText.setCharacterSize(20);
  centerOrigin(mInstructionText);
  mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);

}


void PauseState::draw( )
{
  sf::RenderWindow& window = *getContext().window;
  window.setView(window.getDefaultView());

  sf::RectangleShape background(sf::Vector2f(window.getSize()));
  background.setFillColor(sf::Color(0,0,0,150));
  window.draw(background);
  window.draw(mPauseText);
  window.draw(mInstructionText);
}


bool PauseState::update(sf::Time dt)
{
  return false;
}


bool PauseState::handleEvent(const sf::Event& event)
{
  if (event.type != sf::Event::KeyPressed)
    return false;

  if (event.key.code == sf::Keyboard::BackSpace)
    requestStackPop();

  else if (event.key.code == sf::Keyboard::Escape)
  {
    requestStateClear();
    requestStackPush(States::Menu);
  }

  return false;
}