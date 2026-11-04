#ifndef DISPLAYPARKING_H
#define DISPLAYPARKING_H

#include "ParkingSlot.h"


struct ParkingNode {
    ParkingSlot data;
    ParkingNode* next;
};
// ================================================================

void displayParkingStatus(ParkingNode* head);

#endif