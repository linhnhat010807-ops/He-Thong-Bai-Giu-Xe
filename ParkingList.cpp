#include "ParkingList.h"

void initParkingList(ParkingList& list, int rows, int slotsPerRow) {
    list.head = nullptr;
    list.rows = rows;
    list.slotsPerRow = slotsPerRow;
    list.capacity = rows * slotsPerRow;

    ParkingSlot* tail = nullptr; 

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
                list.head = node;      // Node đầu tiên
            } else {
                tail->next = node;     // Nối vào cuối list
            }
            tail = node;
        }
    }
}

ParkingSlot* findEmptySlot(const ParkingList& list) {
    ParkingSlot* current = list.head;

    while (current != nullptr) {
        if (!current->isOccupied) {
            return current;            // Gặp chỗ trống đầu tiên
        }
        current = current->next;
    }
    return nullptr;                    // Đã full
}

void destroyParkingList(ParkingList& list) {
    ParkingSlot* current = list.head;

    while (current != nullptr) {
        ParkingSlot* temp = current;
        current = current->next;
        delete temp;                          //Xóa dữ liệu bộ nhớ
    }
    list.head = nullptr;
    list.capacity = 0;
}