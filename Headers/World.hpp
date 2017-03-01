#pragma once

#include <ResourceIdentifier.hpp>
#include <ResourceHolder.hpp>
#include <SceneNode.hpp>
#include <SpriteNode.hpp>
#include <Aircraft.hpp>
#include <CommandQueue.hpp>

#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\Graphics\View.hpp>

#include <array>

class World
{
public:
  explicit World::World(sf::RenderWindow& window, FontHolder& font);
  void            update(sf::Time dt);
  void            draw();
  CommandQueue&   getCommandQueue();

public:
  struct SpawnPoint
  {
    SpawnPoint(Aircraft::Type type, float x , float y);

    Aircraft::Type type;
    float x;
    float y;
  };

private:
  void loadTextures();
  void buildScene();

  void adaptPlayerVelocity();
  void adaptPlayerPosition();

  void spawnEnemies();
  void addEnemy(Aircraft::Type type, float x, float y);
  void addEnemies();

  sf::FloatRect getViewBounds() const;
  sf::FloatRect getBattlefieldBounds() const;

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
  FontHolder&                         mFontHolder;
  SceneNode                           mSceneGraph;
  std::array<SceneNode*, LayerCount>  mSceneLayer;
  CommandQueue                        mCommandQueue;

  std::vector<SpawnPoint>             mEnemySpawnPoints;
  sf::FloatRect                       mWorldBounds;
  sf::Vector2f                        mSpawnposition;
  float                               mScrollSpeed;
  Aircraft*                           mPlayer;
};