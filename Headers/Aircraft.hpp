#pragma once

#include <Entity.hpp>
#include <ResourceIdentifier.hpp>
#include <TextNode.hpp>

#include <SFML\Graphics\Sprite.hpp>

class Aircraft : public Entity
{
public:
  enum Type
  {
    Eagle,
    Raptor,
    TypeCounts
  };
public:
  Aircraft(Type type, const TextureHolder& texture, const FontHolder& font);

  virtual size_t  getCategory() const;

private:
  Type        mType;
  sf::Sprite  mSprite;
  TextNode*   mHealthDisplay;

private:
  virtual void drawCurrent(sf::RenderTarget& states, sf::RenderStates target) const;
  virtual void updateCurrent(sf::Time dt);

};