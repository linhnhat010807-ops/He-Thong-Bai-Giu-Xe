#include "Payment.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

double Payment::calculateParkingFee(
    time_t entryTime,
    time_t exitTime
) {
    double totalFee = 0;

    time_t current = entryTime;

    while (current < exitTime) {

        tm* timeInfo = localtime(&current);

        int hour = timeInfo->tm_hour;

        double price = 0;

        if (hour >= 5 && hour < 18) {
            price = 3000;
        }
        else if (hour >= 18 && hour < 23) {
            price = 5000;
        }

        double remaining = difftime(exitTime, current);

        double usedSeconds = min(remaining, 3600.0);

        if (price > 0) {
            totalFee += price;
        }

        current += static_cast<time_t>(usedSeconds);
    }

    return totalFee;
}

bool Payment::returnVehicle(
    HashTable& hashTable,
    ParkingList& parkingList
) {
    string plate;

    cout << "\nNhap bien so xe can tra: ";
    cin >> plate;

    ParkingSlot* slot = searchVehicle(hashTable, plate);
    
    if (slot == nullptr) {
        cout << "\nKhong tim thay xe!\n";
        return false;
    }

    time_t exitTime = time(nullptr);

    double fee = calculateParkingFee(
        slot->entryTime,
        exitTime
    );

    cout << "\nHOA DON GUI XE\n";

    cout << "Bien so xe: " << plate << endl;

    cout << "Vi tri: Hang " << slot->row
         << " - So " << slot->position << endl;

    cout << "Thoi gian vao: "
         << ctime(&slot->entryTime);

    cout << "Thoi gian ra: "
         << ctime(&exitTime);

    cout << "Tong tien: "
         << fixed << setprecision(0)
         << fee << " VND\n";

    removeVehicle(hashTable, plate);
    
    releaseSlot(slot);

    cout << "\nTra xe thanh cong!\n";
    cout << "Vi tri da duoc cap nhat thanh trong.\n";

    return true;
}
