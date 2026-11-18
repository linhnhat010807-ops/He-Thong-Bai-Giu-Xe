# Hệ thống bãi giữ xe

Đồ án C++ quản lý bãi giữ xe bằng danh sách liên kết và bảng băm.

## Yêu cầu

- Windows 10/11
- MSYS2 MinGW-w64 hoặc môi trường có `g++`
- PowerShell

## Chạy chương trình

Biên dịch:

```powershell
g++ -std=c++17 -O2 main.cpp Menu.cpp ParkingList.cpp HashTable.cpp SendVehicle.cpp Payment.cpp DisplayParking.cpp -o parking.exe
```

Chạy tương tác:

```powershell
.\parking.exe
```

Chạy dữ liệu kiểm thử chính (nhóm A, B, C, D):

```powershell
.\parking.exe parking_testcases.cases
```

Chạy dữ liệu kiểm thử bổ sung (A2–A4 và B5):

```powershell
.\parking.exe extra_tests.txt
```

## Các chương trình kiểm thử

| File | Phạm vi theo báo cáo |
|---|---|
| `parking_testcases.cases` | Nhóm A1, A5, B1–B4, C1–C2, D1–D2 |
| `extra_tests.txt` | Nhóm A2–A4 và B5 |
| `test_all.cpp` | Nhóm E1–E8: hiển thị bãi xe |
| `fee_test.cpp` | Nhóm F1–F10: tính phí |
| `bench.cpp` | Đo hiệu năng; có cấu hình bãi 26 × 1000 (26.000 chỗ), phục vụ kiểm tra G1 và mục 5.3 |

## Chạy toàn bộ bộ kiểm thử

Mở PowerShell tại thư mục dự án và chạy:

```powershell
.\run_tests.ps1
```

Script sẽ biên dịch các chương trình kiểm thử, chạy từng nhóm và lưu kết quả vào:

- `result_main.txt`
- `result_extra.txt`
- `result_display.txt`
- `result_fee.txt`
- `result_bench.txt`

Đối chiếu các kết quả này với Bảng 6 và Bảng 7 trong báo cáo. Thời gian benchmark có thể khác nhau tùy cấu hình máy.
