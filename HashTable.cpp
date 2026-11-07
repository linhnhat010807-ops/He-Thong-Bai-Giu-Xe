#include "HashTable.h"
#include "ParkingList.h"

void CreateHT (HashTable& ht)
{
  for (int i = 0; i < TABLE_SIZE; ++i)
    {ht.buckets[i] = nullptr;}
};
int HashFunct (const std::string& key)
{
  int hash = 0;
  for (char c : key)
    {hash = (hash * 31 + (unsigned char)c) % TABLE_SIZE;}
  return hash;
};
bool insertVehicle (HashTable& ht, const std::string& plate, ParkingSlot* slotPtr)
{
  if (plate.empty() || slotPtr == nullptr)
    {return false;}
  if (searchVehicle (ht, plate) != nullptr)
    {return false;}
  int index = HashFunct (plate)
  HashNode* newNode = new HashNode;
  newNode->key = plate;
  newNode->slotPtr = slotPtr;
  newNode->next = ht.buckets[index];
  ht.buckets[index] = newNode;
  return true;
}
