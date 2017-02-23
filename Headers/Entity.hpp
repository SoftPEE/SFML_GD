#pragma once

#include <SFML\System\Vector2.hpp>

#include <SceneNode.hpp>

class Entity : public SceneNode
{
private:
  sf::Vector2f    mVelocity;

  virtual void    updateCurrent(sf::Time dt);

public:
  void            setVelocity(sf::Vector2f velocity);
  void            setVelocity(float vx, float vy);
  void            accelerator(sf::Vector2f accelerate);
  void            accelerator(float dx, float dy);

  sf::Vector2f    getVelocity() const;
};