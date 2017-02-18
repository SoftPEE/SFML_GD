#pragma once

#include <memory>
#include <map>
#include <cassert>

#include <ResourceIdentifier.hpp>

template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
  std::map<Identifier, std::unique_ptr<Resource>>  mResourceMap;

public:
  ResourceHolder( );
  ~ResourceHolder( );

public:
        void            load(Identifier id, const std::string& filename);
  template<typename Parameter>
        void            load(Identifier id, const std::string& filename, const Parameter& secondParameter);
  const sf::Resource&   get(Identifier id);
};

#include "ResourceHolder.inl"