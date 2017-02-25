#include <Button.hpp>
#include <Utilities.hpp>

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Window\Event.hpp>

namespace GUI
{
  Button::Button(const FontHolder & font, const TextureHolder & texture)
    : mSprite{ }
    , mCallback{ }
    , mText{ "", font.get(Fonts::default), 16 }
    , mToggle{ false }
    , mNormalTexture{ texture.get(Textures::ButtonNormal) }
    , mSelectedTexture{ texture.get(Textures::ButtonSelected) }
    , mPressedTexture{ texture.get(Textures::ButtonPressed) }
  {
    mSprite.setTexture(mNormalTexture);
    mText.setPosition(sf::Vector2f(mNormalTexture.getSize() / 2u));
  }


  Button::~Button( )
  {

  }


  void Button::setCallback(Callback callback)
  {
    mCallback = std::move(callback);
  }


  void Button::setText(const std::string& text)
  {
    mText.setString(text);
    centerOrigin(mText);
  }


  void Button::setToggle(bool flag)
  {
    mToggle = flag;
  }


  bool Button::isSelectable( ) const
  {
    return true;
  }


  void Button::select( )
  {
    Component::select();
    mSprite.setTexture(mSelectedTexture);
  }


  void Button::deselect( )
  {
    Component::deselect();
    mSprite.setTexture(mNormalTexture);
  }


  void Button::activate( )
  {
    Component::activate();

    if (mToggle)
      mSprite.setTexture(mPressedTexture);
    if (mCallback)
      mCallback();
    if (!mToggle)
      deactivate();
  }


  void Button::deactivate( )
  {
    Component::deactivate();

    if (mToggle)
    {
      if (isSelected())
        mSprite.setTexture(mSelectedTexture);
      else
        mSprite.setTexture(mNormalTexture);
    }
  }


  void Button::handleEvent(const sf::Event& event)
  {

  }


  void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    states.transform *= getTransform();

    target.draw(mSprite, states);
    target.draw(mText, states);
  }
}

