#include <Aircraft.hpp>
#include <ResourceHolder.hpp>
#include <Category.hpp>

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
  auto bounds = mSprite.getLocalBounds();
  mSprite.setOrigin(bounds.width / 2.0, bounds.height / 2.0);
}


size_t Aircraft::getCategory( ) const
{
  switch (mType)
  {
  case Eagle:
    return Category::PlayerAircraft;
    break;
  default:
    return Category::EnemyAircraft;
  }
}


void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}