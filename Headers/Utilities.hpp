#pragma once

#include <string>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\System\Vector2.hpp>

namespace sf
{
  class Text;
  class Sprite;
  class Keyboard;
}

void centerOrigin(sf::Text& text);
void centerOrigin(sf::Sprite& sprite);
std::string KeytoString(sf::Keyboard::Key key);

float toRadian(float degree);
float toDegree(float radian);
float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);