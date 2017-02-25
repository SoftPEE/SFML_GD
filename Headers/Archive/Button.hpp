#pragma once

#include <Component.hpp>
#include <ResourceIdentifier.hpp>
#include <ResourceHolder.hpp>

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Text.hpp>

#include <memory>
#include <string>
#include <functional>

namespace GUI
{
  class Button : public Component
  {
  public:
    using Ptr = std::shared_ptr<Button>;
    using Callback = std::function<void()>;

  public:
            Button::Button(const FontHolder& font, const TextureHolder& texture);
    virtual Button::~Button();

            void setCallback(Callback callback);
            void setText(const std::string& text);
            void setToggle(bool flag);

    virtual bool isSelectable() const;
    virtual void select();
    virtual void deselect();
    virtual void activate();
    virtual void deactivate();

    virtual void handleEvent(const sf::Event& event);

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
    sf::Sprite            mSprite;
    sf::Text              mText;
    bool                  mToggle;

    const sf::Texture&    mNormalTexture;
    const sf::Texture&    mSelectedTexture;
    const sf::Texture&    mPressedTexture;

    Callback              mCallback;
  };
}