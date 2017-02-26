#pragma once

#include <SceneNode.hpp>

#include <SFML\System\Vector2.hpp>

class Entity : public SceneNode
{
public:
  explicit Entity::Entity(int hitpoints);

  void            repair(int points);
  void            damage(int points);
  void            destroy();

  int             getHitpoints() const;
  bool            isDestroyed() const;

  void            setVelocity(sf::Vector2f velocity);
  void            setVelocity(float vx, float vy);
  void            accelerator(sf::Vector2f accelerate);
  void            accelerator(float dx, float dy);

  sf::Vector2f    getVelocity() const;

private:
  sf::Vector2f    mVelocity;
  int             mHitpoints;

protected:
  virtual void    updateCurrent(sf::Time dt);
};