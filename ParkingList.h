#ifndef PARKINGLIST_H
#define PARKINGLIST_H

#include <string>
#include <ctime>

struct ParkingSlot {
    int slotNumber;
    int row;
    int position;
    bool isOccupied;
    std::string licensePlate;
    std::time_t entryTime;
    ParkingSlot* next;
};

struct ParkingList {
    ParkingSlot* head;
    int rows;
    int slotsPerRow;
    int capacity;
};

void initParkingList(ParkingList& list, int rows, int slotsPerRow);
ParkingSlot* findEmptySlot(const ParkingList& list);
void releaseSlot(ParkingSlot* slot);
void destroyParkingList(ParkingList& list);

#endif
