#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

struct ParkingSlot {
    int row;
    int position;
    bool occupied;

    ParkingSlot(int r = 0, int p = 0, bool o = false)
        : row(r), position(p), occupied(o) {}
};

#endif