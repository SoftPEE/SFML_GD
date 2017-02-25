#include <Container.hpp>

#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>

namespace GUI
{
  Container::Container( )
    : mChildren{ }
    , mSelectedChild{ -1 }
  {

  }


  Container::~Container( )
  {

  }


  bool Container::isSelectable( ) const
  {
    return false;
  }


  void Container::handleEvent(const sf::Event& event)
  {
    if (hasSelection() && mChildren[mSelectedChild]->isActive())
      mChildren[mSelectedChild]->handleEvent(event);
    else if (event.type == sf::Event::KeyPressed)
    {
      if ((event.key.code == sf::Keyboard::W) || (event.key.code == sf::Keyboard::Up))
        selectPrevious();
      else if ((event.key.code == sf::Keyboard::S) || (event.key.code == sf::Keyboard::Down))
        selectNext();
      else if ((event.key.code == sf::Keyboard::Return) || (event.key.code == sf::Keyboard::Space))
        if (hasSelection())
          mChildren[mSelectedChild]->activate();
    }
  }


  void Container::select(size_t index )
  {
    if (mChildren[index]->isSelectable( ))
    {
      if (hasSelection())
        mChildren[mSelectedChild]->deselect();
      mChildren[index]->select();
      mSelectedChild = index;
    }
  }


  void Container::pack(Component::Ptr component)
  {
    mChildren.push_back(component);
    if (!hasSelection() && component->isSelectable())
      select(mChildren.size() - 1);
  }



  void Container::draw(sf::RenderTarget& target, sf::RenderStates state) const
  {
    state.transform *= getTransform();

    for(auto& child : mChildren)
      target.draw(*child, state);
  }


  void Container::selectNext( )
  {
    if (!hasSelection())
      return;

    int next = mSelectedChild;
    do
    {
      next = (next + 1) % mChildren.size();
    } while (!mChildren[mSelectedChild]->isSelectable());
    select(next);
  }


  void Container::selectPrevious( )
  {
    if (!hasSelection())
      return;

    int previous = mSelectedChild;
    do
    {
      previous = (previous + mChildren.size() - 1) % mChildren.size();
    } while (!mChildren[previous]->isSelectable());
    select(previous);
  }


  bool Container::hasSelection( ) const
  {
    return mSelectedChild >= 0;
  }
}