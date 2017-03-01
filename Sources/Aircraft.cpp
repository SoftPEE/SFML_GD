#include <Aircraft.hpp>
#include <ResourceHolder.hpp>
#include <Category.hpp>
#include <DataTables.hpp>
#include <TextNode.hpp>
#include <Utilities.hpp>

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
  , mDirectionIndex{ 0 }
  , mTraveledDistance{ 0 }
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
  mHealthDisplay->setRotation(getRotation());
}


void Aircraft::updateMovementPattern(sf::Time dt)
{
  const std::vector<Direction>& directions = Table[mType].directions;

  if (!directions.empty( ))
  {
    float distanceToTravel = directions[mDirectionIndex].distance;
    if (mTraveledDistance > distanceToTravel)
    {
      mDirectionIndex = (mDirectionIndex + 1) % directions.size();
      mTraveledDistance = 0.f;
    }

    float radians = toRadian(directions[mDirectionIndex].angle + 90.f);
    float vx = getMaxSpeed() * cos(radians);
    float vy = getMaxSpeed() * sin(radians);

    setVelocity(vx, vy);
    mTraveledDistance += getMaxSpeed() * dt.asSeconds();

  }
}


float Aircraft::getMaxSpeed( ) const
{
  return Table[mType].speed;
}