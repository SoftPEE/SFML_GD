#pragma once

#include <SFML\Graphics\Sprite.hpp>

#include <Entity.hpp>
#include <ResourceIdentifier.hpp>

class Aircraft : public Entity
{
public:
  enum Type
  {
    Eagle,
    Raptor
  };

private:
  Type        mType;
  sf::Sprite  mSprite;

public:
  Aircraft(Type type, const TextureHolder& texture);

private:
  virtual void drawCurrent(sf::RenderTarget& states, sf::RenderStates target) const;

};