#include "DisplayParking.h"
#include <iostream>
using namespace std;

static void occupy(ParkingList& l, int n) {
    ParkingSlot* s = l.head;
    for (int i = 0; i < n && s; i++, s = s->next) s->isOccupied = true;
}

int main() {
    cout << "### TC1: chua khoi tao\n";
    ParkingList a = {nullptr, 0, 0, 0};
    displayParkingStatus(a);

    cout << "\n### TC2: head null nhung capacity > 0\n";
    ParkingList b = {nullptr, 2, 2, 4};
    displayParkingStatus(b);

    cout << "\n### TC3: 1x1 trong\n";
    ParkingList c; initParkingList(c, 1, 1);
    displayParkingStatus(c);

    cout << "\n### TC4: 1x1 co xe (day)\n";
    occupy(c, 1);
    displayParkingStatus(c);
    destroyParkingList(c);

    cout << "\n### TC5: 2x4, co xe A1 va A3\n";
    ParkingList d; initParkingList(d, 2, 4);
    d.head->isOccupied = true;
    d.head->next->next->isOccupied = true;
    displayParkingStatus(d);
    destroyParkingList(d);

    cout << "\n### TC6: 3x3 day het\n";
    ParkingList e; initParkingList(e, 3, 3);
    occupy(e, 9);
    displayParkingStatus(e);
    destroyParkingList(e);

    cout << "\n### TC7: gui 2 xe roi tra A1\n";
    ParkingList f; initParkingList(f, 2, 3);
    ParkingSlot* s1 = findEmptySlot(f); s1->isOccupied = true;
    ParkingSlot* s2 = findEmptySlot(f); s2->isOccupied = true;
    displayParkingStatus(f);
    releaseSlot(s1);
    displayParkingStatus(f);
    destroyParkingList(f);

    cout << "\n### TC8: 26 hang x 1 cho\n";
    ParkingList g; initParkingList(g, 26, 1);
    displayParkingStatus(g);
    destroyParkingList(g);

    return 0;
}
