#pragma once

#include <memory>
#include <vector>

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include <SFML\System\NonCopyable.hpp>

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
  using Ptr = std::unique_ptr<SceneNode>;

private:
  std::vector<Ptr>    mChildren;
  SceneNode*          mParent;

public:
  SceneNode::SceneNode();

  void    attachChild(Ptr child);
  Ptr     detachChild(const SceneNode& node);

private:
  virtual void  draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void  drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
          void  drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

};