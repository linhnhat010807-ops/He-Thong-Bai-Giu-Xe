//menu nháp

#include <iostream>
#include <limits>
#include <string>

#include "Menu.h"
#include "SendVehicle.h"
#include "Payment.h"
#include "DisplayParking.h"

using namespace std;

void showMenu() {
    cout << "          QUAN LY BAI GIU XE            \n";
    cout << "  1. Gui xe                             \n";
    cout << "  2. Tra xe va thanh toan               \n";
    cout << "  3. Tim kiem thong tin xe              \n";
    cout << "  4. Xem so do va tinh trang bai xe     \n";
    cout << "  5. Thong ke bai xe                    \n";
    cout << "  0. Thoat chuong trinh                 \n";
    cout << "Nhap lua chon: ";
}

int getValidChoice() {
    int choice;

    while (true) {
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice >= 0 && choice <= 5) {
                return choice;
            }

            cout << "Lua chon khong hop le! Nhap lai: ";
        }
        else {
            if (cin.eof()) {
                return 0;
            }

            cout << "Vui long nhap so nguyen! Nhap lai: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void handleMenuChoice(int choice) {

    switch (choice) {

        case 1:
            cout << "\n CHUC NANG GUI XE \n";
            sendVehicle();
            break;

        case 2:
            cout << "\n CHUC NANG TRA XE \n";
            returnVehicle();
            break;

        case 3:
            cout << "\n TIM KIEM THONG TIN XE\n";

            cout << "Chuc nang dang duoc tich hop.\n";
            break;

        case 4:
            cout << "\n TINH TRANG BAI XE\n";
            displayParkingStatus();
            break;

        case 5:
            cout << "\n THONG KE BAI XE\n";

            cout << "Chuc nang thong ke can duoc bo sung.\n";
            break;

        case 0:
            cout << "\nCam on ban da su dung dich vu!\n";
            cout << "Da thoat chuong trinh!\n";
            break;
    }
}

void runProgram() {

    int choice;

    do {
        showMenu();

        choice = getValidChoice();

        handleMenuChoice(choice);

    } while (choice != 0);
}
