#include "shipparts.h"
#include <fstream>
#include "utility.h"

using namespace std;

ShipPartDictionary ShipPartDict;

ShipPart::ShipPart()
  {
  ID = desc = string("null");
  price = 0;
  }

ShipSails::ShipSails()
  {
  lateen = square = turning = 0;
  }

ShipArmor::ShipArmor()
  {
  armor = 0;
  speed = 0;
  }

ShipStatue::ShipStatue()
  {
  protection = healing = dodging = 0;
  }

ShipSails ShipPartDictionary::getSail(const std::string& ID)
  {
  auto it = sailList.find(ID);
  if (it == sailList.end())
    return ShipSails();
  return it->second;
  }

ShipStatue ShipPartDictionary::getFigurehead(const std::string& ID)
  {
  auto it = figureheadList.find(ID);
  if (it == figureheadList.end())
    return ShipStatue();
  return it->second;
  }

ShipArmor ShipPartDictionary::getArmor(const std::string& ID)
  {
  auto it = armorList.find(ID);
  if (it == armorList.end())
    return ShipArmor();
  return it->second;
  }

string JSONToShipPart::slurp(const string& filename)
  {
  fstream file(filename.c_str());
  string output; output.clear();
  string buffer; buffer.clear();
  while (!file.eof())
    {
    getline(file, buffer);
    output.append(buffer + string("\n"));
    }
  return output;
  }

void JSONToShipPart::readShipParts(ShipPartDictionary& dict)
  {
  string index;
  Json::Value root;
  Json::Reader reader;
  index = slurp(string("resources/shipparts.json"));
  bool parsingSuccess = reader.parse(index, root);
  if (!parsingSuccess)
    {
    cout << "Didn't succeed: " << reader.getFormattedErrorMessages();
    cin.ignore();
    return;
    }
  int counter = 0;

  while (!root[counter].isNull())
    {
    Json::Value shippart = root[counter];
    string type = shippart["type"].asString();
    if (type == string("sail"))
      {
      ShipSails sails;
      sails.ID = shippart["ID"].asString();
      sails.name = shippart["name"].asString();
      sails.price = shippart["price"].asInt();
      sails.lateen = shippart["lateen"].asInt();
      sails.square = shippart["square"].asInt();
      sails.turning = shippart["turning"].asDouble();
      if(!shippart["desc"].isNull())
        sails.desc = shippart["desc"].asString();
      dict.sailList[sails.ID] = sails;
      }
    else if (type == string("plate"))
      {
      ShipArmor armor;
      armor.ID = shippart["ID"].asString();
      armor.price = shippart["price"].asInt();
      armor.armor = shippart["armor"].asInt();
      armor.speed = shippart["speed"].asDouble();
      if(!shippart["desc"].isNull())
        armor.desc = shippart["desc"].asString();
      dict.armorList[armor.ID] = armor;
      }
    else if (type == string("statue"))
      {
      ShipStatue statue;
      statue.ID = shippart["ID"].asString();
      statue.price = shippart["price"].asInt();
      statue.protection = shippart["protection"].asInt();
      statue.healing = shippart["healing"].asInt();
      statue.dodging = shippart["dodging"].asInt();
      if(!shippart["desc"].isNull())
        statue.desc = shippart["desc"].asString();
      dict.figureheadList[statue.ID] = statue;
      }
    counter++;
    }
  };