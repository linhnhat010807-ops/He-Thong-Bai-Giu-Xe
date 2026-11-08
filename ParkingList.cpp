#include "ParkingList.h"

void initParkingList(ParkingList& list, int rows, int slotsPerRow) {
    list.head = nullptr;
    list.rows = rows;
    list.slotsPerRow = slotsPerRow;
    list.capacity = rows * slotsPerRow;

    ParkingSlot* tail = nullptr;      // Node cuối hiện tại, để nối node mới vào

    for (int r = 1; r <= rows; r++) {
        for (int p = 1; p <= slotsPerRow; p++) {
            ParkingSlot* node = new ParkingSlot;
            node->slotNumber = (r - 1) * slotsPerRow + p;
            node->row = r;
            node->position = p;
            node->isOccupied = false;
            node->licensePlate = "";
            node->entryTime = 0;
            node->next = nullptr;

            if (list.head == nullptr) {
                list.head = node;          // Node đầu tiên
            } else {
                tail->next = node;      // Nối vào cuối danh sách
            }
            tail = node;
        }
    }
}


ParkingSlot* findEmptySlot(const ParkingList& list) {
    ParkingSlot* current = list.head;

    while (current != nullptr) {
        if (!current->isOccupied) {
            return current;               // Gặp chỗ trống đầu tiên
        }
        current = current->next;
    }
    return nullptr;       // Bãi đầy
}

void releaseSlot(ParkingSlot* slot) {
    if (slot == nullptr) {
        return;                      
    }
    slot->isOccupied = false;
    slot->licensePlate = "";
    slot->entryTime = 0;
}

void destroyParkingList(ParkingList& list) {
    ParkingSlot* current = list.head;

    while (current != nullptr) {
        ParkingSlot* temp = current;
        current = current->next;
        delete temp;
    }
    list.head = nullptr;      // Đưa head về nullptr
    list.rows = 0;          // Reset thông tin bãi xe
    list.slotsPerRow = 0;
    list.capacity = 0;
}
