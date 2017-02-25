#include <SettingState.hpp>
#include <Utilities.hpp>

#include <SFML\Graphics\RenderWindow.hpp>

SettingState::SettingState(StateStack& stack, Context context)
  : State{stack, context }
  , mGUIContainer{ }
  , mBackgroundSprite{ }
{
  mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

  addButtonLabel(Player::MoveUp,    150.f, "Hoch",   context);
  addButtonLabel(Player::MoveDown,  200.f, "Runter", context);
  addButtonLabel(Player::MoveLeft,  250.f, "Links",  context);
  addButtonLabel(Player::MoveRight, 300.f, "Rechts", context);

  updateLabels();

  auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  backButton->setText("Zurück");
  backButton->setPosition(80.f, 375.f);
  backButton->setCallback(std::bind(&SettingState::State::requestStackPop, this));

  mGUIContainer.pack(backButton);
}


SettingState::~SettingState( )
{

}


void SettingState::draw( )
{
  sf::RenderWindow& window = *getContext().window;

  window.draw(mBackgroundSprite);
  window.draw(mGUIContainer);
}


bool SettingState::update(sf::Time dt)
{
  return false;
}


bool SettingState::handleEvent(const sf::Event& event)
{
  bool isKeyBinding = false;

  for (size_t i = 0; i < Player::ActionCount; ++i)
  {
    if (mBindingButtons[i]->isActive())
    {
      isKeyBinding = true;
      if (event.type == sf::Event::KeyPressed)
      {
        getContext().player->assignKey(static_cast<Player::Action>(i), event.key.code);
        mBindingButtons[i]->deactivate();
      }
      break;
    }
  }

  if (isKeyBinding)
    updateLabels();
  else
    mGUIContainer.handleEvent(event);

  return false;
}


void SettingState::updateLabels( )
{
  Player& player = *getContext().player;

  for (size_t i = 0; i < Player::ActionCount; ++i)
  {
    sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
    mbindingLabels[i]->setText(KeytoString(key));
  }
}


void SettingState::addButtonLabel(Player::Action action, float y, const std::string& text, Context context)
{
  mBindingButtons[action] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
  mBindingButtons[action]->setPosition(80.f, y);
  mBindingButtons[action]->setText(text);
  mBindingButtons[action]->setToggle(true);

  mbindingLabels[action] = std::make_shared<GUI::Label>(text, *context.fonts);
  mbindingLabels[action]->setPosition(350.f, y + 15.f);

  mGUIContainer.pack(mBindingButtons[action]);
  mGUIContainer.pack(mbindingLabels[action]);
}