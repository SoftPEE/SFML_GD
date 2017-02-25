#pragma once

#include <string>
#include <SFML\Window\Keyboard.hpp>

namespace sf
{
  class Text;
  class Sprite;
  class Keyboard;
}

void centerOrigin(sf::Text& text);
void centerOrigin(sf::Sprite& sprite);
std::string KeytoString(sf::Keyboard::Key key);