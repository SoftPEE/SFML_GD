#pragma once

#include <map>
#include <string>
#include <iostream>

namespace configuration
{
  struct data : std::map<std::string, std::string>
  {

  };

  std::istream& operator>> (std::istream& is, data& d);
  std::ostream& operator<< (std::ostream& os, const data& d);
}