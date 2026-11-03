#ifndef PARKINGSET_H
#define PARKINGSET_H

#include <set>
#include <utility>

class ParkingSet {
private:
    std::set<std::pair<int, int>> emptySlots;

public:
    void addEmptySlot(int row, int position);

    bool hasEmptySlot() const;

    std::pair<int, int> findEmptySlot();

    void releaseSlot(int row, int position);
};

#endif