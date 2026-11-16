#include "Payment.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

double Payment::calculateParkingFee(time_t entryTime, time_t exitTime) {
    if (entryTime <= 0 || exitTime <= entryTime) {
        return 0;
    }

    double totalFee = 0;
    time_t current = entryTime;

    while (current < exitTime) {
        tm* timeInfoPtr = localtime(&current);
        if (timeInfoPtr == nullptr) {
            break;
        }
        tm currentInfo = *timeInfoPtr;
        int hour = currentInfo.tm_hour;

        double price = 0;
        if (hour >= 5 && hour < 18) {
            price = 3000;
        }
        else if (hour >= 18 && hour < 23) {
            price = 5000;
        }
        tm nextHourInfo = currentInfo;
        nextHourInfo.tm_min = 0;
        nextHourInfo.tm_sec = 0;
        nextHourInfo.tm_hour += 1;

        time_t nextHour = mktime(&nextHourInfo);
        if (nextHour == static_cast<time_t>(-1) || nextHour <= current) {
            break;
        }
        time_t segmentEnd = (exitTime < nextHour) ? exitTime : nextHour;
        totalFee += price;

        current = segmentEnd;
    }

    return totalFee;
}

bool Payment::returnVehicle(HashTable& hashTable, ParkingList& parkingList) {
    (void)parkingList;

    string plate;

    cout << "\nNhap bien so xe can tra: ";
    cin >> plate;

    ParkingSlot* slot = searchVehicle(hashTable, plate);

    if (slot == nullptr) {
        cout << "\nKhong tim thay xe!\n";
        return false;
    }

    time_t exitTime = time(nullptr);
    if (slot->entryTime <= 0) {
        cout << "\nLoi: Thoi gian vao bai cua xe chua duoc luu hop le.\n";
        cout << "Khong the tinh tien. Xe van duoc giu trong bai.\n";
        return false;
    }

    if (exitTime <= slot->entryTime) {
        cout << "\nLoi: Thoi gian tra xe phai sau thoi gian vao bai.\n";
        cout << "Xe van duoc giu trong bai.\n";
        return false;
    }

    double fee = calculateParkingFee(slot->entryTime, exitTime);

    cout << "\nHOA DON GUI XE\n";
    cout << "Bien so xe: " << plate << endl;
    cout << "Vi tri: Hang " << slot->row
         << " - So " << slot->position << endl;

    cout << "Thoi gian vao: " << ctime(&slot->entryTime);
    cout << "Thoi gian ra: " << ctime(&exitTime);

    cout << "Tong tien: "
         << fixed << setprecision(0)
         << fee << " VND\n";

    removeVehicle(hashTable, plate);
    releaseSlot(slot);

    cout << "\nTra xe thanh cong!\n";
    cout << "Vi tri da duoc cap nhat thanh trong.\n";

    return true;
}
