#include <Entity.hpp>

void Entity::setVelocity(sf::Vector2f velocity)
{
  mVelocity = velocity;
}

void Entity::updateCurrent(sf::Time dt)
{
  move(mVelocity * dt.asSeconds());
}

void Entity::setVelocity(float vx, float vy)
{
  mVelocity.x = vx;
  mVelocity.y = vy;
}


void Entity::accelerator(sf::Vector2f accelerate)
{
  mVelocity += accelerate;
}



void Entity::accelerator(float dx, float dy)
{
  mVelocity += sf::Vector2f(dx,dy);
}


sf::Vector2f Entity::getVelocity( ) const
{
  return mVelocity;
}