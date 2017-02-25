#pragma once

#include <Component.hpp>

#include <vector>

namespace GUI
{
  class Container : public Component
  {
  public:
    using Ptr = std::shared_ptr<Container>;

  public:
            Container::Container();
    virtual Container::~Container();

    virtual bool isSelectable() const;
    virtual void handleEvent(const sf::Event& event);
            void select(size_t index);

            void pack(Component::Ptr component);

  private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
            void selectNext();
            void selectPrevious();
            bool hasSelection() const;

  private:
    std::vector<Component::Ptr> mChildren;
    int                         mSelectedChild;
  };
}