#ifndef PAYMENT_H
#define PAYMENT_H

#include "HashTable.h"
#include "ParkingList.h"

class Payment {
public:
    double calculateParkingFee(
        std::time_t entryTime, 
        std::time_t exitTime);

    bool returnVehicle(HashTable& hashTable,
                       ParkingList& parkingList);
};

#endif
