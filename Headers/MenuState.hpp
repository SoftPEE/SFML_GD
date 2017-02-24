#pragma once

#include <vector>

#include <State.hpp>

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Text.hpp>

class MenuState : public State
{
public:
  MenuState::MenuState(StateStack& stack, Context context);

  virtual bool  update(sf::Time dt);
  virtual bool  handleEvent(const sf::Event& event);
  virtual void  draw();

  void          updateOptionText();

private:
  enum OptionNames
  {
    Play,
    Exit
  };

private:
  sf::Sprite             mBackgroundSprite;
  std::vector<sf::Text>  mOptions;
  std::size_t            mOptionIndex;

};