$ErrorActionPreference = 'Stop'

function Build-Target($name, $sources) {
    Write-Host "`n[BUILD] $name" -ForegroundColor Cyan
    & g++ -std=c++17 -O2 $sources -o "$name.exe"
    if ($LASTEXITCODE -ne 0) { throw "Bien dich $name that bai." }
}

function Check-Output($file, $patterns) {
    $content = Get-Content $file -Raw
    foreach ($pattern in $patterns) {
        if (-not $content.Contains($pattern)) {
            throw "Khong tim thay ket qua mong doi '$pattern' trong $file"
        }
    }
    Write-Host "[PASS] Kiem tra dau ra: $file" -ForegroundColor Green
}

Build-Target "parking" @("main.cpp", "Menu.cpp", "ParkingList.cpp", "HashTable.cpp", "SendVehicle.cpp", "Payment.cpp", "DisplayParking.cpp")
Build-Target "test_all" @("test_all.cpp", "DisplayParking.cpp", "ParkingList.cpp")
Build-Target "fee_test" @("fee_test.cpp", "Payment.cpp", "HashTable.cpp", "ParkingList.cpp")
Build-Target "bench" @("bench.cpp", "DisplayParking.cpp", "ParkingList.cpp", "HashTable.cpp")

Write-Host "`n[RUN] Nhóm A, B, C, D - parking_testcases.cases"
& .\parking.exe parking_testcases.cases *> .\result_main.txt
if ($LASTEXITCODE -ne 0) { throw "Chay parking_testcases.cases that bai." }
Check-Output ".\result_main.txt" @("Khoi tao bai xe thanh cong!", "Gui xe thanh cong!", "Xe da ton tai!", "Khong tim thay xe trong bai!", "Khong tim thay xe!", "Bai xe da day!", "Da dong chuong trinh!")

Write-Host "`n[RUN] Nhóm A2-A4 va B5 - extra_tests.txt"
& .\parking.exe extra_tests.txt *> .\result_extra.txt
if ($LASTEXITCODE -ne 0) { throw "Chay extra_tests.txt that bai." }
Check-Output ".\result_extra.txt" @("Vui long nhap so nguyen hop le!", "Gia tri phai tu 1 den 26!", "Gia tri phai tu 1 den 1000!", "Vi tri da duoc cap nhat thanh trong.")

Write-Host "`n[RUN] Nhom E1-E8 - test_all.cpp"
& .\test_all.exe *> .\result_display.txt
if ($LASTEXITCODE -ne 0) { throw "test_all that bai." }
Check-Output ".\result_display.txt" @("TC1", "TC8", "Hang Z:", "Tong suc chua: 26")

Write-Host "`n[RUN] Nhom F1-F10 - fee_test.cpp"
& .\fee_test.exe *> .\result_fee.txt
if ($LASTEXITCODE -ne 0) { throw "fee_test that bai." }
Check-Output ".\result_fee.txt" @("F1", "F10", "Ket qua: 10/10 test case dat")

Write-Host "`n[RUN] Nhom G1 va danh gia hieu nang - bench.cpp"
& .\bench.exe *> .\result_bench.txt
if ($LASTEXITCODE -ne 0) { throw "bench that bai." }
Check-Output ".\result_bench.txt" @("26x1000", "26000")

Write-Host "`nHOAN TAT: Cac chuong trinh kiem thu da chay. Xem result_*.txt de doi chieu chi tiet." -ForegroundColor Green
Write-Host "Luu y: ket qua chay tu dong can duoc doc va doi chieu voi tung test case trong Bao cao; script khong tu dong chung nhan 33/33 neu chi kiem tra mot so dong dau ra."
