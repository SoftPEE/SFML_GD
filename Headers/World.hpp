#pragma once

#include <array>

#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Time.hpp>

#include <ResourceIdentifier.hpp>
#include <ResourceHolder.hpp>
#include <SceneNode.hpp>
#include <SpriteNode.hpp>
#include <Aircraft.hpp>

class World
{
public:
  explicit World::World(sf::RenderWindow& window);
  void  update(sf::Time dt);
  void  draw();

private:
  void loadTextures();
  void buildScene();

private:
  enum Layer
  {
    Background,
    Air,
    LayerCount
  };

private:
  sf::RenderWindow&                   mWindow;
  sf::View                            mWorldView;
  TextureHolder                       mTextures;
  SceneNode                           mSceneGraph;
  std::array<SceneNode*, LayerCount>  mSceneLayer;

  sf::FloatRect                       mWorldBounds;
  sf::Vector2f                        mSpawnposition;
  float                               mScrollSpeed;
  Aircraft*                           mPlayer;
};