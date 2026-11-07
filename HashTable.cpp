#include "HashTable.h"
#include "ParkingList.h"

void CreateHT (HashTable& ht)
{
  for (int i = 0; i < TABLE_SIZE; ++i)
    {ht.buckets[i] = nullptr;}
}
int HashFunct (const std::string& key)
{
  int hash = 0;
  for (char c : key)
    {hash = (hash * 31 + (unsigned char)c) % TABLE_SIZE;}
  return hash;
}
bool insertVehicle (HashTable& ht, const std::string& plate, ParkingSlot* slotPtr)
{
  if (plate.empty() || slotPtr == nullptr)
    {return false;}
  if (searchVehicle (ht, plate) != nullptr)
    {return false;}
  int index = HashFunct (plate);
  HashNode* newNode = new HashNode;
  newNode->key = plate;
  newNode->slotPtr = slotPtr;
  newNode->next = ht.buckets[index];
  ht.buckets[index] = newNode;
  return true;
}
ParkingSlot* searchVehicle (const HashTable& ht, const std::string& plate)
{
  if (plate.empty ())
  {return nullptr;}
  int index = HashFunct (plate);
  HashNode* current = ht.buckets [index];
  while (current != nullptr)
    {
      if (current->key == plate)
      { return current->slotPtr; }
      current = current->next;
    }
  return nullptr;
}
bool removeVehicle(HashTable& ht, const std::string& plate)
{
    if (plate.empty()) 
    {return false;}
    int index = HashFunct(plate);
    HashNode* current = ht.buckets[index];
    HashNode* prev = nullptr;
    while (current != nullptr) 
    {
        if (current->key == plate) 
        {
            if (prev == nullptr)
            {
                ht.buckets[index] = current->next;
            } 
            else
            {
                prev->next = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}
void destroyHT(HashTable& ht)
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        HashNode* current = ht.buckets[i];
        while (current != nullptr)
        {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
        ht.buckets[i] = nullptr;
    }
}
