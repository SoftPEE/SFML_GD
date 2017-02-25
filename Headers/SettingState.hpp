#pragma once

#include <State.hpp>
#include <Container.hpp>
#include <Player.hpp>
#include <Button.hpp>
#include <Label.hpp>

#include <SFML\Graphics\Sprite.hpp>

#include <array>

class SettingState : public State
{
public:
          SettingState::SettingState(StateStack& stack, Context context);
  virtual SettingState::~SettingState();

  virtual void      draw();
  virtual bool      update(sf::Time dt);
  virtual bool      handleEvent(const sf::Event& event);

private:
          void      updateLabels();
          void      addButtonLabel(Player::Action action, float y, const std::string& text, Context context);

private:
  GUI::Container                                    mGUIContainer;
  sf::Sprite                                        mBackgroundSprite;
  std::array<GUI::Button::Ptr, Player::ActionCount> mBindingButtons;
  std::array<GUI::Label::Ptr, Player::ActionCount>  mbindingLabels;
};