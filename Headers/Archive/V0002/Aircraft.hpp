#pragma once

#include <Entity.hpp>
#include <ResourceIdentifier.hpp>

#include <SFML\Graphics\Sprite.hpp>

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

  virtual size_t  getCategory() const;

private:
  virtual void drawCurrent(sf::RenderTarget& states, sf::RenderStates target) const;

};