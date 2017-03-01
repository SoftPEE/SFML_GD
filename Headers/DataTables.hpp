#pragma once

#include <ResourceIdentifier.hpp>

#include <vector>

struct Direction;

struct AircraftData
{
  int                     hitpoints;
  float                   speed;
  Textures::ID            texture;
  std::vector<Direction>  directions;
};

struct Direction
{
  Direction(float angle, float distance);
      float angle;
      float distance;
};

std::vector<AircraftData> initializeAircraftData();