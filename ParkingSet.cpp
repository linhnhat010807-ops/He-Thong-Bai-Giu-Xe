#include "ParkingSet.h"

void ParkingSet::addEmptySlot(int row, int position) {
    emptySlots.insert({row, position});
}

bool ParkingSet::hasEmptySlot() const {
    return !emptySlots.empty();
}

std::pair<int, int> ParkingSet::findEmptySlot() {

    if (emptySlots.empty()) {
        return {-1, -1};
    }

    auto slot = *emptySlots.begin();

    emptySlots.erase(emptySlots.begin());

    return slot;
}

void ParkingSet::releaseSlot(int row, int position) {
    emptySlots.insert({row, position});
}