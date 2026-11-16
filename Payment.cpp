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

    // Moi khung gio tren dong ho co su dung se tinh tron mot gio.
    // 05:00-17:59: 3.000 VND; 18:00-22:59: 5.000 VND;
    // 23:00-04:59: mien phi.
    while (current < exitTime) {
        tm* timeInfoPtr = localtime(&current);
        if (timeInfoPtr == nullptr) {
            break;
        }

        tm currentInfo = *timeInfoPtr;
        const int hour = currentInfo.tm_hour;

        double price = 0;
        if (hour >= 5 && hour < 18) {
            price = 3000;
        } else if (hour >= 18 && hour < 23) {
            price = 5000;
        }

        tm nextHourInfo = currentInfo;
        nextHourInfo.tm_min = 0;
        nextHourInfo.tm_sec = 0;
        nextHourInfo.tm_hour += 1;

        const time_t nextHour = mktime(&nextHourInfo);
        if (nextHour == static_cast<time_t>(-1) || nextHour <= current) {
            break;
        }

        totalFee += price;
        current = (exitTime < nextHour) ? exitTime : nextHour;
    }

    return totalFee;
}

bool Payment::returnVehicle(HashTable& hashTable, ParkingList& parkingList) {
    (void)parkingList; // Giu nguyen giao dien ham hien tai.

    string plate;
    cout << "\nNhap bien so xe can tra: ";
    cin >> plate;

    ParkingSlot* slot = searchVehicle(hashTable, plate);
    if (slot == nullptr) {
        cout << "\nKhong tim thay xe!\n";
        return false;
    }

    const time_t exitTime = time(nullptr);

    if (slot->entryTime <= 0) {
        cout << "\nLoi: Thoi gian vao bai chua duoc luu hop le.\n";
        cout << "Xe van duoc giu trong bai.\n";
        return false;
    }

    if (exitTime <= slot->entryTime) {
        cout << "\nLoi: Thoi gian tra xe phai sau thoi gian vao bai.\n";
        cout << "Xe van duoc giu trong bai.\n";
        return false;
    }

    const double fee = calculateParkingFee(slot->entryTime, exitTime);

    cout << "\nHOA DON GUI XE\n";
    cout << "Bien so xe: " << plate << '\n';
    cout << "Vi tri: Hang " << slot->row
         << " - So " << slot->position << '\n';
    cout << "Thoi gian vao: " << ctime(&slot->entryTime);
    cout << "Thoi gian ra: " << ctime(&exitTime);
    cout << "Tong tien: " << fixed << setprecision(0) << fee << " VND\n";

    // Chi giai phong cho sau khi xoa duoc xe khoi HashTable.
    if (!removeVehicle(hashTable, plate)) {
        cout << "Loi: Khong the xoa xe khoi HashTable.\n";
        return false;
    }

    releaseSlot(slot);
    cout << "\nTra xe thanh cong!\n";
    cout << "Vi tri da duoc cap nhat thanh trong.\n";
    return true;
}
