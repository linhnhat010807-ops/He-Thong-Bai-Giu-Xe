#include "ParkingQueue.h"

void ParkingQueue::addEmptySlot(int row, int position) {
    emptySlots.push(ParkingSlot(row, position, false));
}

bool ParkingQueue::hasEmptySlot() const {
    return !emptySlots.empty();
}

ParkingSlot ParkingQueue::findEmptySlot() {

    if (emptySlots.empty()) {
        return ParkingSlot(-1, -1, true);
    }

    ParkingSlot slot = emptySlots.front();
    emptySlots.pop();

    return slot;
}

void ParkingQueue::releaseSlot(int row, int position) {
    emptySlots.push(ParkingSlot(row, position, false));
}