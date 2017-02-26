#include <DataTables.hpp>
#include <Aircraft.hpp>

std::vector<AircraftData> initializeAircraftData( )
{
  std::vector<AircraftData> data{ Aircraft::TypeCounts};

  data[Aircraft::Eagle].hitpoints = 100;
  data[Aircraft::Eagle].speed = 200.f;
  data[Aircraft::Eagle].texture = Textures::Eagle;

  data[Aircraft::Raptor].hitpoints = 20;
  data[Aircraft::Raptor].speed = 80.f;
  data[Aircraft::Raptor].texture = Textures::Raptor;

  return data;
}