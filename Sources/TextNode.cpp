#include <TextNode.hpp>
#include <Utilities.hpp>

TextNode::TextNode(const FontHolder& font, const std::string& text)
  : mText{text, font.get(Fonts::default), 20 }
{
  centerOrigin(mText);
}


void TextNode::setString(const std::string& text)
{
  mText.setString(text);
  centerOrigin(mText);
}


void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mText, states);
}