#include <World.hpp>

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
  mSceneGraph.update(dt);

  sf::Vector2f playerPosition = mPlayer->getPosition( );
  sf::Vector2f playerVelocity = mPlayer->getVelocity( );

  if ((playerPosition.x >= mWorldBounds.left + mWorldBounds.width - 150.0f) ||
      (playerPosition.x <= mWorldBounds.left + 150.0f))
  {
    playerVelocity.x = -playerVelocity.x;
    mPlayer->setVelocity(playerVelocity);
  }
}


void World::draw( )
{
  mWindow.setView(mWorldView);
  mWindow.draw(mSceneGraph);
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