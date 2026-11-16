#include "SendVehicle.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

bool sendVehicle(ParkingList& parkingList, HashTable& hashTable) {
    string plate;

    cout << "Nhap bien so xe: ";
    getline(cin >> ws, plate);

    if (plate.empty()) {
        cout << "Bien so xe khong duoc de trong!\n";
        return false;
    }

    if (searchVehicle(hashTable, plate) != nullptr) {
        cout << "Xe da ton tai!\n";
        return false;
    }

    ParkingSlot* slot = findEmptySlot(parkingList);
    if (slot == nullptr) {
        cout << "Bai xe da day!\n";
        return false;
    }

    const time_t now = time(nullptr);
    if (now == static_cast<time_t>(-1) || now <= 0) {
        cout << "Khong lay duoc thoi gian he thong!\n";
        return false;
    }

    slot->isOccupied = true;
    slot->licensePlate = plate;
    slot->entryTime = now;

    if (!insertVehicle(hashTable, plate, slot)) {
        releaseSlot(slot);
        cout << "Loi: Khong the luu xe vao HashTable!\n";
        return false;
    }

    cout << "Gui xe thanh cong!\n";
    cout << "Hang: " << slot->row
         << " - Vi tri: " << slot->position << '\n';
    cout << "Thoi gian vao: " << ctime(&slot->entryTime);

    return true;
}
