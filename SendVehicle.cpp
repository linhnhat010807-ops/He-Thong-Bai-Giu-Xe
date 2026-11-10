#include "SendVehicle.h"
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

bool sendVehicle(ParkingList& parkingList, HashTable& hashTable) {
    string plate;

    cout << "Nhap bien so xe: ";
    getline(cin >> ws, plate);

    if (hashTable.searchVehicle(plate)) {
        cout << "Xe da ton tai!\n";
        return false;
    }

    ParkingSlot* slot = findEmptySlot(head);

    if (slot == nullptr) {
        cout << "Bai xe da day!\n";
        return false;
    }

    slot->isOccupied = true;
    slot->licensePlate = plate;
    slot->checkInTime = time(nullptr);

    hashTable.insertVehicle(plate, slot);

    cout << "Gui xe thanh cong!\n";
    cout << "Hang: " << slot->row
         << " - Vi tri: " << slot->position << endl;

    return true;
}
