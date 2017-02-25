#pragma once

#include <Category.hpp>

#include <SFML\System\Time.hpp>

#include <functional>
#include <cassert>

class SceneNode;

struct Command
{
  Command::Command();

  std::function<void(SceneNode&, sf::Time)>   action;
  size_t                                      category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
  return [=] (SceneNode& node, sf::Time dt)
  {
    //�berpr�fe ob das Gameobjekt wirklich vom Typ SceneNode abstammt
    assert(dynamic_cast<GameObject*>(&node) != nullptr);

    //Ausf�hrung der Funktion
    fn(static_cast<GameObject&>(node), dt);
  };
}