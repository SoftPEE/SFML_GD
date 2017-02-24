#include <Utilities.hpp>

#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\Sprite.hpp>

void setOrigin(sf::Text& text)
{
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}


void setOrigin(sf::Sprite& sprite)
{
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}