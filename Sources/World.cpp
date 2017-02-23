#include <World.hpp>

#include <SFML\Graphics\RenderWindow.hpp>

World::World(sf::RenderWindow& window)
  : mWindow{ window }
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
  std::unique_ptr<Aircraft> playerAircraft{ new Aircraft{Aircraft::Eagle, mTextures} };
  mPlayer = playerAircraft.get();
  mPlayer->setPosition(mSpawnposition);
  mPlayer->setVelocity(40.0f, mScrollSpeed);
  mSceneLayer[Air]->attachChild(std::move(playerAircraft));


  //Eskorte erstellen
  std::unique_ptr<Aircraft> escortLeft{new Aircraft{Aircraft::Raptor, mTextures } };
  escortLeft->setPosition(-50,50);

  std::unique_ptr<Aircraft> escortRight{new Aircraft{Aircraft::Raptor, mTextures } };
  escortRight->setPosition(50,50);

  mPlayer->attachChild(std::move(escortLeft));
  mPlayer->attachChild(std::move(escortRight));
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