#!/usr/bin/env bash
# Chạy toàn bộ kiểm thử trên Linux / macOS / GitHub Codespaces.
# Dùng: bash run_tests.sh   (tại thư mục gốc của dự án)
set -e

CXX="g++ -std=c++17 -O2"

build() {  # build <tên> <các file nguồn...>
    local name=$1; shift
    echo "[BUILD] $name"
    $CXX "$@" -o "$name"
}

check() {  # check <file> <chuỗi mong đợi...>
    local file=$1; shift
    for pattern in "$@"; do
        if ! grep -qF -- "$pattern" "$file"; then
            echo "[FAIL] Không tìm thấy '$pattern' trong $file"
            exit 1
        fi
    done
    echo "[PASS] Kiểm tra đầu ra: $file"
}

build parking  main.cpp Menu.cpp ParkingList.cpp HashTable.cpp SendVehicle.cpp Payment.cpp DisplayParking.cpp
build test_all test_all.cpp DisplayParking.cpp ParkingList.cpp
build fee_test fee_test.cpp Payment.cpp HashTable.cpp ParkingList.cpp
build bench    bench.cpp DisplayParking.cpp ParkingList.cpp HashTable.cpp

echo; echo "[RUN] Nhóm A, B, C, D - parking_testcases.cases"
./parking parking_testcases.cases > result_main.txt
check result_main.txt "Khoi tao bai xe thanh cong!" "Gui xe thanh cong!" "Xe da ton tai!" \
      "Khong tim thay xe trong bai!" "Khong tim thay xe!" "Bai xe da day!" "Da dong chuong trinh!"

echo; echo "[RUN] Nhóm A2-A4 và B5 - extra_tests.txt"
./parking extra_tests.txt > result_extra.txt
check result_extra.txt "Vui long nhap so nguyen hop le!" "Gia tri phai tu 1 den 26!" \
      "Gia tri phai tu 1 den 1000!" "Vi tri da duoc cap nhat thanh trong."

echo; echo "[RUN] Nhóm E1-E8 - test_all.cpp"
./test_all > result_display.txt
check result_display.txt "TC1" "TC8" "Hang Z:" "Tong suc chua: 26"

echo; echo "[RUN] Nhóm F1-F10 - fee_test.cpp"
./fee_test > result_fee.txt
check result_fee.txt "F1" "F10" "Ket qua: 10/10 test case dat"

echo; echo "[RUN] Nhóm G1 - gửi đầy 26.000 chỗ (26 x 1000) bằng chương trình chính"
{
    echo 26; echo 1000
    for i in $(seq 0 25999); do echo 1; printf '51A-%05d\n' "$i"; done
    echo 1; echo 51A-99999   # xe thứ 26.001 phải bị từ chối
    echo 4; echo 0
} > g1_input.tmp
./parking g1_input.tmp > result_g1.txt
rm -f g1_input.tmp
ok=$(grep -c "Gui xe thanh cong!" result_g1.txt || true)
full=$(grep -c "Bai xe da day!" result_g1.txt || true)
echo "Gửi thành công: $ok / 26000; bị từ chối vì đầy: $full / 1"
[ "$ok" -eq 26000 ] && [ "$full" -eq 1 ] || { echo "[FAIL] G1"; exit 1; }
check result_g1.txt "Tong so cho trong: 0" "Tong suc chua: 26000"

echo; echo "[RUN] Hiệu năng - bench.cpp"
./bench > result_bench.txt
check result_bench.txt "26x1000" "26000"

echo; echo "HOÀN TẤT: các chương trình kiểm thử đã chạy. Xem result_*.txt để đối chiếu với báo cáo."
echo "Lưu ý: script chỉ kiểm tra một số dòng đầu ra; vẫn cần đọc kết quả và đối chiếu từng test case."
