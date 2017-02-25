#include <Component.hpp>

namespace GUI
{
  Component::Component( )
    : mIsSelected{ false }
    , mIsActivated{ false }
  {

  }


  Component::~Component( )
  {

  }


  bool Component::isSelected( ) const
  {
    return mIsSelected;
  }


  void Component::select( )
  {
    mIsSelected = true;
  }


  void Component::deselect( )
  {
    mIsSelected = false;
  }


  bool Component::isActive( ) const
  {
    return mIsActivated;
  }


  void Component::activate( )
  {
    mIsActivated = true;
  }


  void Component::deactivate( )
  {
    mIsActivated = false;
  }
}