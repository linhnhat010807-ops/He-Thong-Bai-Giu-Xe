// ============================================================
// ParkingList.h
// Người phụ trách: Duy Hiếu
// Nhiệm vụ: Xây dựng Linked List, khởi tạo bãi xe,
//           quản lý vị trí và tìm chỗ trống gần nhất.
// ============================================================
#ifndef PARKINGLIST_H
#define PARKINGLIST_H

#include <string>
#include <ctime>

struct ParkingSlot {
    int slotNumber;            
    int row;                   
    int position;              
    bool isOccupied;        
    std::string licensePlate;  // Biển số xe đang đỗ ("" nếu trống)
    std::time_t entryTime;     // Thời điểm gửi xe (0 nếu trống)
    ParkingSlot* next;         // Con trỏ tới vị trí kế tiếp
};

struct ParkingList {
    ParkingSlot* head;   
    int rows;           
    int slotsPerRow;    
    int capacity;        
};

void initParkingList(ParkingList& list, int rows, int slotsPerRow);

ParkingSlot* findEmptySlot(const ParkingList& list);

void destroyParkingList(ParkingList& list);

#endif 