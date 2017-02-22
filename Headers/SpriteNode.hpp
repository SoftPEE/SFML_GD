#pragma once

#include <SFML\Graphics\Sprite.hpp>

#include <SceneNode.hpp>

class SpriteNode : public SceneNode
{
public:
  explicit  SpriteNode::SpriteNode(const sf::Texture& texture);
            SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
  virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  sf::Sprite mSprite;
};