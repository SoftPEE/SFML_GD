/****************************************************************************************************************************
SFML_GD
Author:			      	Patrick Gehrt
Datum:			      	08.02.2017
Letzte Bearbeitung: 23.02.2017
Version:		      	0.0.0.2
SFML-Version:	      2.4.1

Beschreibung:	SFML Game Development
	Lernen wie mit Hilfe der SFML-Bibliothek und C++ ein Spiel entwickelt wird.

****************************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <Windows.h>

#include <Game.hpp>
#include <Configuration.hpp>

int main()
{
  configuration::data myConfigdata;

  std::ifstream f("appConfig.ini");

  f >> myConfigdata;

  std::cout << myConfigdata;

  try
  {
    Game game;
    game.run();
  }
  catch (std::exception e)
  {
    std::cerr << e.what();
    std::cin.get();
  }
  


  return EXIT_SUCCESS;
}