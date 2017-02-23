#pragma once

#include <Command.hpp>

#include <memory>
#include <vector>

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include <SFML\System\NonCopyable.hpp>
#include <SFML\System\Time.hpp>

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
  using Ptr = std::unique_ptr<SceneNode>;

private:
  std::vector<Ptr>    mChildren;
  SceneNode*          mParent;

public:
  SceneNode::SceneNode();

  void            update(sf::Time dt);

  void            attachChild(Ptr child);
  Ptr             detachChild(const SceneNode& node);
  sf::Vector2f    getWorldPosition() const;
  virtual size_t  getCategory() const;
  void    onCommand(const Command& command, sf::Time dt);

private:
  sf::Transform   getWorldTransforms() const;
  virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
          void    drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
               
  virtual void    updateCurrent(sf::Time dt);
          void    updateChildren(sf::Time dt);

          

};