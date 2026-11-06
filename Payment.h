#ifndef PAYMENT_H
#define PAYMENT_H

#include "HashTable.h"
#include "LinkedList.h"

class Payment {
public:
    double calculateParkingFee(time_t entryTime, time_t exitTime);

    bool returnVehicle(HashTable& hashTable,
                       LinkedList& parkingList);
};

#endif
