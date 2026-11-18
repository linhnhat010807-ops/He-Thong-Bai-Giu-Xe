#include "HashTable.h"
#include "ParkingList.h"
#include "DisplayParking.h"
#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using Clock = chrono::steady_clock;

static double ms(Clock::time_point a, Clock::time_point b) {
    return chrono::duration<double, milli>(b - a).count();
}

int main() {
    int sizes[][2] = {{1, 100}, {4, 250}, {5, 1000}, {26, 200}, {26, 1000}};
    printf("%-9s %-7s | %-12s %-11s | %-8s %-9s | %-13s %-13s\n",
           "Bai(NxM)", "N cho", "Dien day(ms)", "TB/xe(us)", "Chuoi TB", "Chuoi max",
           "Tim bam(us)", "Tim DSLK(us)");
    for (auto& s : sizes) {
        ParkingList list;
        initParkingList(list, s[0], s[1]);
        HashTable ht;
        CreateHT(ht);
        int N = list.capacity;

        vector<string> plates;
        plates.reserve(N);
        char buf[32];
        for (int i = 0; i < N; i++) {
            snprintf(buf, sizeof buf, "51A-%05d", i);
            plates.push_back(buf);
        }

        auto t0 = Clock::now();
        for (int i = 0; i < N; i++) {
            ParkingSlot* sl = findEmptySlot(list);
            sl->isOccupied = true;
            sl->licensePlate = plates[i];
            sl->entryTime = 1;
            insertVehicle(ht, plates[i], sl);
        }
        auto t1 = Clock::now();

        int used = 0, mx = 0;
        long total = 0;
        for (int b = 0; b < TABLE_SIZE; b++) {
            int len = 0;
            for (HashNode* n = ht.buckets[b]; n; n = n->next) len++;
            if (len) used++;
            total += len;
            if (len > mx) mx = len;
        }

        volatile long sink = 0;
        const int PASSES = 5;
        auto h0 = Clock::now();
        for (int ps = 0; ps < PASSES; ps++)
            for (int i = 0; i < N; i++) sink += (searchVehicle(ht, plates[i]) != nullptr);
        auto h1 = Clock::now();

        int sample = N < 200 ? N : 200;
        auto l0 = Clock::now();
        for (int k = 0; k < sample; k++) {
            const string& p = plates[(long)k * N / sample];
            for (ParkingSlot* c = list.head; c; c = c->next)
                if (c->licensePlate == p) { sink += 1; break; }
        }
        auto l1 = Clock::now();

        printf("%-9s %-7d | %-12.2f %-11.2f | %-8.1f %-9d | %-13.3f %-13.3f\n",
               (to_string(s[0]) + "x" + to_string(s[1])).c_str(), N,
               ms(t0, t1), ms(t0, t1) * 1000.0 / N,
               (double)total / (used ? used : 1), mx,
               ms(h0, h1) * 1000.0 / ((double)N * PASSES), ms(l0, l1) * 1000.0 / sample);

        destroyHT(ht);
        destroyParkingList(list);
    }

    int dsizes[][2] = {{1, 100}, {4, 250}, {26, 1000}, {100, 1000}, {1000, 1000}};
    printf("\n%-10s %-9s | %-22s\n", "Bai(NxM)", "N cho", "displayParkingStatus(ms)");
    for (auto& s : dsizes) {
        ParkingList list;
        initParkingList(list, s[0], s[1]);
        ParkingSlot* c = list.head;
        for (int i = 0; c && i < list.capacity / 2; i++, c = c->next) c->isOccupied = true;

        streambuf* old = cout.rdbuf();
        cout.rdbuf(nullptr);
        displayParkingStatus(list);
        const int REPS = (list.capacity >= 1000000) ? 5 : 30;
        auto d0 = Clock::now();
        for (int r = 0; r < REPS; r++) displayParkingStatus(list);
        auto d1 = Clock::now();
        cout.rdbuf(old);
        cout.clear();

        printf("%-10s %-9d | %-22.3f\n",
               (to_string(s[0]) + "x" + to_string(s[1])).c_str(), list.capacity, ms(d0, d1) / REPS);
        destroyParkingList(list);
    }
    return 0;
}
