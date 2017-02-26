#include <Entity.hpp>

Entity::Entity(int hitpoints)
  : mHitpoints {hitpoints }
{

}


void Entity::repair(int points)
{
  mHitpoints += points;
}


void Entity::damage(int points)
{
  mHitpoints -= points;
}


void Entity::destroy( )
{
  mHitpoints = 0;
}


int Entity::getHitpoints( ) const
{
  return mHitpoints;
}


bool Entity::isDestroyed( ) const
{
  return mHitpoints > 0;
}


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