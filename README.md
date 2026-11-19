# Hệ thống bãi giữ xe

Đồ án C++ quản lý bãi giữ xe bằng danh sách liên kết và bảng băm.

## Yêu cầu

- Trình biên dịch `g++` hỗ trợ C++17 (MSYS2 MinGW-w64 trên Windows, hoặc `g++` trên Linux/macOS/GitHub Codespaces)
- Windows: PowerShell. Linux/macOS/Codespaces: bash

> Lưu ý: PowerShell dùng dấu `\` (`.\parking.exe`), còn bash dùng dấu `/` (`./parking`).
> Gõ sai kiểu sẽ báo `command not found`.

## Biên dịch

```
g++ -std=c++17 -O2 main.cpp Menu.cpp ParkingList.cpp HashTable.cpp SendVehicle.cpp Payment.cpp DisplayParking.cpp -o parking
```

## Chạy chương trình

### Windows (PowerShell)

```powershell
.\parking.exe                              # chạy tương tác
.\parking.exe parking_testcases.cases      # dữ liệu kiểm thử chính (nhóm A, B, C, D)
.\parking.exe extra_tests.txt              # dữ liệu kiểm thử bổ sung (A2–A4 và B5)
```

### Linux / macOS / GitHub Codespaces (bash)

```bash
./parking                                  # chạy tương tác
./parking parking_testcases.cases          # dữ liệu kiểm thử chính (nhóm A, B, C, D)
./parking extra_tests.txt                  # dữ liệu kiểm thử bổ sung (A2–A4 và B5)
```

## Các chương trình kiểm thử

| File | Phạm vi theo báo cáo |
|---|---|
| `parking_testcases.cases` | Nhóm A1, A5, B1–B4, C1–C2, D1–D2 |
| `extra_tests.txt` | Nhóm A2–A4 và B5 |
| `test_all.cpp` | Nhóm E1–E8: hiển thị bãi xe |
| `fee_test.cpp` | Nhóm F1–F10: tính phí |
| `bench.cpp` | Đo hiệu năng; có cấu hình bãi 26 × 1000 (26.000 chỗ), phục vụ mục 5.3 |
| `run_tests.ps1` | Windows: biên dịch và chạy nhóm A–F và hiệu năng |
| `run_tests.sh` | Linux/Codespaces: như trên, thêm nhóm G1 (gửi đầy 26.000 chỗ bằng chương trình chính) |

## Chạy toàn bộ kiểm thử

Windows (PowerShell, tại thư mục dự án):

```powershell
.\run_tests.ps1
```

Linux / macOS / Codespaces (bash, tại thư mục dự án):

```bash
bash run_tests.sh
```

Script biên dịch các chương trình kiểm thử, chạy từng nhóm và lưu kết quả vào:

- `result_main.txt`
- `result_extra.txt`
- `result_display.txt`
- `result_fee.txt`
- `result_bench.txt`
- `result_g1.txt` (chỉ có trong `run_tests.sh`)

Đối chiếu các kết quả này với Bảng 6 và Bảng 7 trong báo cáo. Thời gian benchmark có thể khác nhau tùy cấu hình máy.
