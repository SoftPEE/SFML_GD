#include <Aircraft.hpp>
#include <ResourceHolder.hpp>

#include<SFML\Graphics\RenderTarget.hpp>
#include<SFML\Graphics\RenderStates.hpp>

Textures::ID toTextureID(Aircraft::Type type)
{
  switch (type)
  {
  case Aircraft::Eagle:
    return Textures::Eagle;
    break;
  case Aircraft::Raptor:
    return Textures::Raptor;
    break;
  }
}

Aircraft::Aircraft(Aircraft::Type type, const TextureHolder& texture)
  : mType {type }
  , mSprite{texture.get(toTextureID(type))}
{

}


void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}