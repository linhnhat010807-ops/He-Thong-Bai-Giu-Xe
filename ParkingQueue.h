#ifndef PARKINGQUEUE_H
#define PARKINGQUEUE_H

#include <queue>
#include "ParkingSlot.h"

class ParkingQueue {
private:
    std::queue<ParkingSlot> emptySlots;

public:
    void addEmptySlot(int row, int position);

    bool hasEmptySlot() const;

    ParkingSlot findEmptySlot();

    void releaseSlot(int row, int position);
};

#endif