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
    Raptor
  };

}

namespace Fonts
{
  enum ID
  {
    default
  };
}

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder    = ResourceHolder<sf::Font, Fonts::ID>;