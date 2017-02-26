#pragma once

#include <ResourceIdentifier.hpp>

#include <vector>

struct AircraftData
{
  int             hitpoints;
  float           speed;
  Textures::ID    texture;
};

std::vector<AircraftData> initializeAircraftData();