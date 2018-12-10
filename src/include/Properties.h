#ifndef PROPERTIES_H
#define PROPERTIES_H
#include <string>
#include <map>

class Properties
{
public:
    Properties();
    Properties (std::string filename);
    std::string getValue(std::string key);
    void setValue (std::string key, std::string value);
    bool contains (std::string key);
    void storeToFile (std::string filename);


private:
    std::map<std::string, std::string> _map;

    void createPropertiesFromString (std::string propertiesString);
    void createPropertyFromString (std::string propertyString);

};

#endif // PROPERTIES_H
