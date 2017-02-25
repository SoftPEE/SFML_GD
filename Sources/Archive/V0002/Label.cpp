#include <Label.hpp>
#include <Utilities.hpp>

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

namespace GUI
{
  Label::Label(const std::string& text, const FontHolder& font)
    : mText{text, font.get(Fonts::default), 16 }
  {
    centerOrigin(mText);
  }


  Label::~Label( )
  {

  }


  bool Label::isSelectable( ) const
  {
    return false;
  }


  void Label::setText(const std::string& text)
  {
    mText.setString(text);
    centerOrigin(mText);
  }


  void Label::handleEvent(const sf::Event& event)
  {

  }


  void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    states.transform *= getTransform();

    target.draw(mText, states);
  }
}