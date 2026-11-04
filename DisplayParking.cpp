#include "DisplayParking.h"
#include <iostream>
#include <string>
using namespace std;

// Đổi số hàng sang chữ cái: 1 -> 'A', 2 -> 'B', ...
static char rowToLetter(int row) {
    return static_cast<char>('A' + row - 1);
}

void displayParkingStatus(ParkingNode* head) {
    if (head == nullptr) {
        cout << "Bai xe chua duoc khoi tao!\n";
        return;
    }

    int emptyCount = 0;
    int totalCount = 0;
    string emptyList = "";
    int currentRow = -1;   // -1 = chưa in hàng nào

    cout << "===== SO DO BAI GIU XE =====\n";
    cout << "[ ] = trong    [X] = co xe\n\n";

    for (ParkingNode* cur = head; cur != nullptr; cur = cur->next) {
        const ParkingSlot& s = cur->data;

        if (s.row != currentRow) {            // gặp hàng mới
            if (currentRow != -1) cout << "\n";
            currentRow = s.row;
            cout << "Hang " << rowToLetter(s.row) << ": ";
        }

        string name = string(1, rowToLetter(s.row)) + to_string(s.position);
        cout << name;
        if (s.occupied) {
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