#include <Aircraft.hpp>
#include <ResourceHolder.hpp>
#include <Category.hpp>
#include <DataTables.hpp>
#include <TextNode.hpp>

#include<SFML\Graphics\RenderTarget.hpp>
#include<SFML\Graphics\RenderStates.hpp>

namespace
{
  const std::vector<AircraftData> Table = initializeAircraftData();
}

//Textures::ID toTextureID(Aircraft::Type type)
//{
//  switch (type)
//  {
//  case Aircraft::Eagle:
//    return Textures::Eagle;
//    break;
//  case Aircraft::Raptor:
//    return Textures::Raptor;
//    break;
//  default:
//    return;
//  }
//}


Aircraft::Aircraft(Aircraft::Type type, const TextureHolder& texture, const FontHolder& font)
  : Entity{Table[type].hitpoints }
  , mType {type }
  , mSprite{texture.get(Table[type].texture)}
{
  auto bounds = mSprite.getLocalBounds();
  mSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

  std::unique_ptr<TextNode> healtDisplay{new TextNode(font, "")};
  mHealthDisplay = healtDisplay.get();
  attachChild(std::move(healtDisplay));
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


void Aircraft::updateCurrent(sf::Time dt)
{
  Entity::updateCurrent(dt);
  mHealthDisplay->setString(std::to_string(getHitpoints()));
  mHealthDisplay->setPosition(0.f, 50.f);
  mHealthDisplay->setRotation(!getRotation());
}