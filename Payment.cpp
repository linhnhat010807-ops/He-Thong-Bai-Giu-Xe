#include "Payment.h"
#include <iostream>
#include <cmath>
#include <iomanip>

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

        // Tinh thoi gian cua gio dang xet
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

    HashNode* node = searchVehicle(plate);

    if (node == nullptr) {
        cout << "\nKhong tim thay xe!\n";
        return false;
    }

    ParkingSpot* spot = node->spot;

    time_t exitTime = time(nullptr);

    double fee = calculateParkingFee(
        spot->entryTime,
        exitTime
    );

    cout << "\nHOA DON GUI XE\n";

    cout << "Bien so xe: " << plate << endl;

    cout << "Vi tri: Hang " << spot->row
         << " - So " << spot->position << endl;

    cout << "Thoi gian vao: "
         << ctime(&spot->entryTime);

    cout << "Thoi gian ra: "
         << ctime(&exitTime);

    cout << "Tong tien: "
         << fixed << setprecision(0)
         << fee << " VND\n";


    removeVehicle(plate);


    parkingList.releaseSpot(spot);

    cout << "\nTra xe thanh cong!\n";
    cout << "Vi tri da duoc cap nhat thanh trong.\n";

    return true;
}
