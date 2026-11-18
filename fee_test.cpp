#include "Payment.h"
#include <ctime>
#include <iostream>
using namespace std;

static time_t T(int d, int h, int m) {
    tm t = {};
    t.tm_year = 126;
    t.tm_mon = 10;
    t.tm_mday = d;
    t.tm_hour = h;
    t.tm_min = m;
    t.tm_isdst = -1;
    return mktime(&t);
}

int main() {
    Payment p;
    struct Case {
        const char* ten;
        time_t vao, ra;
        long mongDoi;
    } cases[] = {
        {"F1  17:00 -> 18:00", T(10, 17, 0), T(10, 18, 0), 3000},
        {"F2  17:30 -> 18:30 (qua moc 18h)", T(10, 17, 30), T(10, 18, 30), 8000},
        {"F3  18:00 -> 19:00", T(10, 18, 0), T(10, 19, 0), 5000},
        {"F4  10:00 -> 10:10 (10 phut)", T(10, 10, 0), T(10, 10, 10), 3000},
        {"F5  10:00 -> 11:01", T(10, 10, 0), T(10, 11, 1), 6000},
        {"F6  05:00 -> 23:00", T(10, 5, 0), T(10, 23, 0), 64000},
        {"F7  04:30 -> 05:30 (qua moc 5h)", T(10, 4, 30), T(10, 5, 30), 3000},
        {"F8  22:30 -> 23:30 (qua moc 23h)", T(10, 22, 30), T(10, 23, 30), 5000},
        {"F9  23:30 -> 04:30 (ban dem)", T(10, 23, 30), T(11, 4, 30), 0},
        {"F10 gio ra bang gio vao", T(10, 10, 0), T(10, 10, 0), 0},
    };

    int dat = 0, tong = 0;
    for (const Case& c : cases) {
        long thucTe = static_cast<long>(p.calculateParkingFee(c.vao, c.ra));
        bool ok = (thucTe == c.mongDoi);
        cout << c.ten << " | mong doi " << c.mongDoi << " | thuc te " << thucTe
             << " | " << (ok ? "DAT" : "KHONG DAT") << "\n";
        tong++;
        if (ok) dat++;
    }
    cout << "\nKet qua: " << dat << "/" << tong << " test case dat\n";
    return (dat == tong) ? 0 : 1;
}
