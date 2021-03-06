#include <SceneNode.hpp>
#include <Category.hpp>

#include <algorithm>
#include <cassert>

SceneNode::SceneNode( )
  : mParent{nullptr }
  , mChildren{ }
{

}


void SceneNode::attachChild(SceneNode::Ptr child)
{
  child->mParent = this;
  mChildren.push_back(std::move(child));
}


SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
  auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (Ptr& p) -> bool {return p.get() == &node; });
  assert(found != mChildren.end());

  Ptr result = std::move(*found);
  result->mParent = nullptr;
  mChildren.erase(found);

  return result;
}


void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();

  drawCurrent(target, states);
  drawChildren(target, states);
  
}


void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  //Basisklasse malt nichts
}


void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
  for (auto& child : mChildren)
  {
    child->draw(target, states);
  }
}


void SceneNode::update(sf::Time dt)
{
  updateCurrent(dt);
  updateChildren(dt);
}


void SceneNode::updateCurrent(sf::Time dt)
{

}


void SceneNode::updateChildren(sf::Time dt)
{
  for (auto& child : mChildren)
  {
    child->update(dt);
  }
}


sf::Vector2f SceneNode::getWorldPosition( ) const
{
  return getWorldTransforms() * sf::Vector2f();
}


sf::Transform SceneNode::getWorldTransforms( ) const
{
  sf::Transform transform = sf::Transform::Identity;

  for (const SceneNode* node = this; node != nullptr; node = node->mParent)
  {
    transform = node->getTransform() * transform;
  }

  return transform;
}


size_t SceneNode::getCategory( ) const
{
  return Category::Scene;
}


void SceneNode::onCommand(const Command& command, sf::Time dt)
{
  if (command.category & getCategory())
    command.action(*this, dt);

  for(auto& child : mChildren)
    child->onCommand(command, dt);
}