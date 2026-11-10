
#include <iostream>
#include <limits>
#include <string>
#include <ctime>
#include "Menu.h"
#include "ParkingList.h"
#include "HashTable.h"
#include "SendVehicle.h"
#include "Payment.h"
#include "DisplayParking.h"

using namespace std;

void showMenu() {
    cout << "\nHE THONG BAI GIU XE\n";
    cout << "1. Gui xe\n";
    cout << "2. Tra xe va thanh toan\n";
    cout << "3. Tim kiem xe theo bien so\n";
    cout << "4. Xem danh sach cho trong\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "Nhap lua chon: ";
}

int getValidNumber(const string& message, int minValue, int maxValue) {
    int number;

    while (true) {
        cout << message;

        if (cin >> number) {
            if (number >= minValue && number <= maxValue) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return number;
            }

            cout << "Gia tri phai tu " << minValue
                 << " den " << maxValue << "!\n";
        }
        else {
            if (cin.eof()) {
                return -1;
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Vui long nhap so nguyen hop le!\n";
        }
    }
}

int getValidChoice() {
    return getValidNumber("Nhap lua chon: ", 0, 4);
}

void searchVehicleMenu(const HashTable& hashTable) {
    string plate;

    cout << "\nNhap bien so xe can tim: ";
    getline(cin >> ws, plate);

    if (plate.empty()) {
        cout << "Bien so khong duoc de trong!\n";
        return;
    }

    ParkingSlot* slot = searchVehicle(hashTable, plate);

    if (slot == nullptr || !slot->isOccupied) {
        cout << "Khong tim thay xe trong bai!\n";
        return;
    }

    cout << "\nTHONG TIN XE\n";
    cout << "Bien so: " << slot->licensePlate << endl;
    cout << "Hang: " << static_cast<char>('A' + slot->row - 1) << endl;
    cout << "Vi tri: " << slot->position << endl;

    cout << "Thoi gian gui: ";
    if (slot->entryTime > 0) {
        cout << ctime(&slot->entryTime);
    }
    else {
        cout << "Khong co du lieu\n";
    }
}

void runProgram() {
    cout << "KHOI TAO BAI GIU XE\n";

    int rows = getValidNumber("Nhap so hang (1-26): ", 1, 26);
    if (rows == -1) return;

    int slotsPerRow = getValidNumber("Nhap so vi tri moi hang: ", 1, 1000);
    if (slotsPerRow == -1) return;

    ParkingList parkingList;
    initParkingList(parkingList, rows, slotsPerRow);

    HashTable hashTable;
    CreateHT(hashTable);
    
    Payment payment;

    cout << "\nKhoi tao bai xe thanh cong!\n";
    cout << "Tong suc chua: " << parkingList.capacity << " cho.\n";

    int choice;

    do {
        showMenu();
        choice = getValidChoice();

        switch (choice) {
        case -1:
            cout << "\nKet thuc nhap du lieu.\n";
            break;

        case 1:
            sendVehicle(parkingList, hashTable);
            break;

        case 2:
            payment.returnVehicle(hashTable, parkingList);
            break;

        case 3:
            searchVehicleMenu(hashTable);
            break;

        case 4:
            displayParkingStatus(parkingList);
            break;

        case 0:
            cout << "\nDang thoat chuong trinh...\n";
            break;
        }

    } while (choice != 0 && choice != -1);

    destroyHT(hashTable);
    destroyParkingList(parkingList);

    cout << "Da dong chuong trinh!\n";
}
