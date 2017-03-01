#include <World.hpp>

#include <SFML\Graphics\RenderWindow.hpp>

#include <iostream>

World::SpawnPoint::SpawnPoint(Aircraft::Type type, float x, float y)
  : type{ type }
  , x{ x }
  , y{ y }
{

}


World::World(sf::RenderWindow& window, FontHolder& font)
  : mWindow{ window }
  , mFontHolder{ font }
  , mWorldView{ window.getDefaultView( ) }
  , mTextures{ }
  , mSceneGraph{ }
  , mSceneLayer{ }
  , mWorldBounds{ 0.0f, 0.0f, mWorldView.getSize( ).x, 2000.0f }
  , mSpawnposition{ mWorldView.getSize( ).x / 2.0f, mWorldBounds.height - mWorldView.getSize( ).y / 2.0f }
  , mScrollSpeed{ -50.0f }
  , mPlayer{ nullptr }
{
  loadTextures( );
  buildScene( );

  mWorldView.setCenter(mSpawnposition);
}


void World::update(sf::Time dt)
{
  mWorldView.move(0, mScrollSpeed * dt.asSeconds( )); 
  mPlayer->setVelocity(0.0f, 0.0f);

  while(!mCommandQueue.isEmpty())
    mSceneGraph.onCommand(mCommandQueue.pop(), dt);
  adaptPlayerVelocity();
  

  mSceneGraph.update(dt);
  adaptPlayerPosition();
  spawnEnemies();

}


void World::draw( )
{
  mWindow.setView(mWorldView);
  mWindow.draw(mSceneGraph);
}


CommandQueue& World::getCommandQueue( )
{
  return mCommandQueue;
}


void World::loadTextures( )
{
  mTextures.load(Textures::Eagle,   "Media//Textures//Eagle.png");
  mTextures.load(Textures::Raptor,  "Media//Textures//Raptor.png");
  mTextures.load(Textures::Avenger, "Media//Textures//Avenger.png");
  mTextures.load(Textures::Dessert, "Media//Textures//Desert.png");
}


void World::buildScene( )
{
  //Layer-Grundgerüst erstellen
  for (size_t i = 0; i < LayerCount; i++)
  {
    SceneNode::Ptr layer{new SceneNode() };
    mSceneLayer[i] = layer.get();

    mSceneGraph.attachChild(std::move(layer));
  }

  //Background erstellen
  sf::Texture& texture = mTextures.get(Textures::Dessert);
  sf::IntRect textureRect{mWorldBounds };
  texture.setRepeated(true);

  std::unique_ptr<SpriteNode> backgroundSprite{ new SpriteNode{texture, textureRect } };
  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);

  mSceneLayer[Background]->attachChild(std::move(backgroundSprite));

  //Spieler erstellen
  std::unique_ptr<Aircraft> playerAircraft{ new Aircraft{Aircraft::Eagle, mTextures, mFontHolder} };
  mPlayer = playerAircraft.get();
  mPlayer->setPosition(mSpawnposition);
  mPlayer->setVelocity(40.0f, mScrollSpeed);
  mSceneLayer[Air]->attachChild(std::move(playerAircraft));

  //Gegner hinzufügen
  addEnemies( );
}


void World::adaptPlayerVelocity( )
{
  sf::Vector2f playerVelocity = mPlayer->getVelocity();

  if (playerVelocity.x != 0.0f && playerVelocity.y != 0.0f)
    mPlayer->setVelocity(playerVelocity / std::sqrt(2.0f));
  mPlayer->accelerator(0.0f, mScrollSpeed);
}


void World::adaptPlayerPosition( )
{
  sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.0f, mWorldView.getSize());
  const float   borderDistance = 40.0f;

  sf::Vector2f position = mPlayer->getPosition();

  position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
  position.x = std::max(position.x, viewBounds.left + borderDistance);
  position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
  position.y = std::max(position.y, viewBounds.top + borderDistance);

  mPlayer->setPosition(position);
}


void World::addEnemy(Aircraft::Type type, float x, float y)
{
  mEnemySpawnPoints.push_back(SpawnPoint(type, mSpawnposition.x + x, mSpawnposition.y - y));
}


void World::addEnemies( )
{
  addEnemy(Aircraft::Raptor,    0.f,  500.f);
  addEnemy(Aircraft::Raptor,    0.f, 1000.f);
  addEnemy(Aircraft::Raptor, +100.f, 1100.f);
  addEnemy(Aircraft::Raptor, -100.f, 1100.f);
  addEnemy(Aircraft::Avenger, -70.f, 1400.f);
  addEnemy(Aircraft::Avenger, -70.f, 1600.f);
  addEnemy(Aircraft::Avenger,  70.f, 1400.f);
  addEnemy(Aircraft::Avenger,  70.f, 1600.f);

  std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [] (SpawnPoint lhs, SpawnPoint rhs) 
  {
    return lhs.y < rhs.y; 
  });
}


void World::spawnEnemies( )
{
  if (!mEnemySpawnPoints.empty( ) && mEnemySpawnPoints.back().y > getBattlefieldBounds().top)
  {
    SpawnPoint spawn = mEnemySpawnPoints.back();

    std::unique_ptr<Aircraft> enemy{new Aircraft(spawn.type, mTextures, mFontHolder) };
    enemy->setPosition(spawn.x, spawn.y);
    enemy->rotate(180.f);
    mSceneLayer[Air]->attachChild(std::move(enemy));

    mEnemySpawnPoints.pop_back();
  }
}


sf::FloatRect World::getViewBounds( ) const
{
  return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}


sf::FloatRect World::getBattlefieldBounds( ) const
{
  sf::FloatRect viewBounds = getViewBounds();

  viewBounds.top -= 100.f;
  viewBounds.height += 100.f;
  
  return viewBounds;
}