#include "HashTable.h"

void CreateHT(HashTable& ht) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        ht.buckets[i] = nullptr;
    }
}

int HashFunct(const std::string& key) {
    unsigned int hash = 0;
    for (unsigned char c : key) {
        hash = (hash * 31u + c) % TABLE_SIZE;
    }
    return static_cast<int>(hash);
}

bool insertVehicle(HashTable& ht, const std::string& plate, ParkingSlot* slotPtr) {
    if (plate.empty() || slotPtr == nullptr) {
        return false;
    }

    if (searchVehicle(ht, plate) != nullptr) {
        return false;
    }

    const int index = HashFunct(plate);
    HashNode* newNode = new HashNode{plate, slotPtr, ht.buckets[index]};
    ht.buckets[index] = newNode;
    return true;
}

ParkingSlot* searchVehicle(const HashTable& ht, const std::string& plate) {
    if (plate.empty()) {
        return nullptr;
    }

    const int index = HashFunct(plate);
    HashNode* current = ht.buckets[index];

    while (current != nullptr) {
        if (current->key == plate) {
            return current->slotPtr;
        }
        current = current->next;
    }

    return nullptr;
}

bool removeVehicle(HashTable& ht, const std::string& plate) {
    if (plate.empty()) {
        return false;
    }

    const int index = HashFunct(plate);
    HashNode* current = ht.buckets[index];
    HashNode* previous = nullptr;

    while (current != nullptr) {
        if (current->key == plate) {
            if (previous == nullptr) {
                ht.buckets[index] = current->next;
            } else {
                previous->next = current->next;
            }

            delete current; // Khong xoa ParkingSlot; slot thuoc ParkingList.
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

void destroyHT(HashTable& ht) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashNode* current = ht.buckets[i];

        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }

        ht.buckets[i] = nullptr;
    }
}
