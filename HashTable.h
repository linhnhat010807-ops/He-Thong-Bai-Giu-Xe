#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include "ParkingList.h"
#define TABLE_SIZE 101

struct HashNode
{
  std::string key;
  ParkingSlot* slotPtr;
  HashNode* next;
};
struct HashTable
{
  HashNode* buckets[TABLE_SIZE];
};
void CreateHT (HashTable& ht);
int HashFunct (std::string key);
void insertVehicle (HashTable& ht, std::string plate, ParkingSlot* slotPtr);
ParkingSlot* searchVehicle (HashTable ht, std::string plate);
bool remove (HashTable& ht, std::string plate);
void destroyHT (HashTable& ht);
#endif
