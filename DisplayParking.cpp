#include "DisplayParking.h"
#include <iostream>
#include <string>
using namespace std;

static char rowToLetter(int row) {
    return static_cast<char>('A' + row - 1);
}

void displayParkingStatus(const ParkingList& list) {
    if (list.head == nullptr) {
        cout << "Bai xe chua duoc khoi tao!\n";
        return;
    }

    int emptyCount = 0;
    int totalCount = 0;
    string emptyList = "";
    int currentRow = -1;

    cout << "===== SO DO BAI GIU XE =====\n";
    cout << "[ ] = trong    [X] = co xe\n\n";

    for (ParkingSlot* cur = list.head; cur != nullptr; cur = cur->next) {
        if (cur->row != currentRow) {
            if (currentRow != -1) cout << "\n";
            currentRow = cur->row;
            cout << "Hang " << rowToLetter(cur->row) << ": ";
        }

        string name = string(1, rowToLetter(cur->row)) + to_string(cur->position);
        cout << name;
        if (cur->isOccupied) {
            cout << "[X] ";
        } else {
            cout << "[ ] ";
            emptyCount++;
            emptyList += name + " ";
        }
        totalCount++;
    }

    cout << "\n\n";
    cout << "Danh sach cho trong: "
         << (emptyCount > 0 ? emptyList : "(khong con cho trong)") << "\n";
    cout << "Tong so cho trong: " << emptyCount << "/" << totalCount << "\n";
}
