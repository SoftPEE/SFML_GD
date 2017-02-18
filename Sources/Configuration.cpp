#include <Configuration.hpp>

namespace configuration
{

  // Der istream Operator ließt die Konfigurationsdatei (configuration::data) bis zum EOF.
  // Ungültige Daten werden ignoriert
  //
  std::istream& operator >> (std::istream& is, data& d)
  {
    std::string s;
    std::string key;
    std::string value;

    //Für jedes (Key, Value) Paar in der config Datei.
    while (std::getline(is,s))
    {
      std::string::size_type begin = s.find_first_not_of(" \f\t\v");

      //Leere Zeilen ignorieren
      if (begin == std::string::npos)
        continue;

      //Kommentare ignorieren
      if (std::string("#;").find( s[begin] ) != std::string::npos)
        continue;

      //Key-Wert extrahieren
      std::string::size_type end = s.find('=', begin);
      key = s.substr(begin, end - begin);

      //Entfernt führende oder endende Leerzeichen
      key.erase(key.find_last_not_of(" \f\t\v") + 1);

      //Leere Schlüssel-Werte sind nicht erlaubt
      if( key.empty())
        continue;

      //Value-Wert extrahieren
      begin = s.find_first_not_of(" \f\n\r\t\v", end + 1);
      end   = s.find_last_not_of(" \f\n\r\t\v") + 1;

      value = s.substr(begin, end - begin);

      //Key - Value Paar einfügen
      d[key] = value;
    }

    return is;
  }


  std::ostream& operator<< (std::ostream& os, const data& d)
  {
    data::const_iterator iter;

    for (iter = d.begin(); iter != d.end(); iter++)
    {
      os << iter->first << " = " << iter->second << std::endl;
    }
    return os;
  }
}  //namespace configuration