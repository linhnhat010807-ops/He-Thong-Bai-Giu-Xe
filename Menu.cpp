#include <iostream>
#include "Menu.h"
#include "SendVehicle.h"
#include "Payment.h"
#include "DisplayParking.h"

using namespace std;

void showMenu() {
    cout << "\n========== QUAN LY BAI GIU XE ==========\n";
    cout << "1. Gui xe\n";
    cout << "2. Tra xe\n";
    cout << "3. Xem tinh trang bai xe\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "========================================\n";
    cout << "Nhap lua chon: ";
}

// Dieu khien cac chuc nang
void runProgram() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                sendVehicle();
                break;

            case 2:
                returnVehicle();
                break;

            case 3:
                displayParkingStatus();
                break;

            case 0:
                cout << "\nDa thoat chuong trinh!\n";
                break;

            default:
                cout << "\nLua chon khong hop le! Vui long nhap lai.\n";
        }

    } while (choice != 0);
}