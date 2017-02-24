#pragma once

#include <ResourceHolder.hpp>

namespace sf
{
  class Texture;
  class Font;
}

namespace Textures
{
  enum ID
  {
    Eagle,
    Raptor,
    Dessert,
    TitleScreen
  };

}

namespace Fonts
{
  enum ID
  {
    default,
    TitleFont
  };
}

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder    = ResourceHolder<sf::Font, Fonts::ID>;