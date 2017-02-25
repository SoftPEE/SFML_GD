#pragma once

#include <Component.hpp>
#include <ResourceIdentifier.hpp>
#include <ResourceHolder.hpp>

#include <SFML\Graphics\Text.hpp>

#include <string>
#include <memory>

namespace GUI
{
  class Label : public Component
  {
  public:
    using Ptr = std::shared_ptr<Label>;
    
  public:
            Label::Label(const std::string& text, const FontHolder& font);
    virtual Label::~Label();

    virtual bool isSelectable() const;
            void setText(const std::string& text);
    virtual void handleEvent(const sf::Event& event);

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
    sf::Text  mText;

  };
}