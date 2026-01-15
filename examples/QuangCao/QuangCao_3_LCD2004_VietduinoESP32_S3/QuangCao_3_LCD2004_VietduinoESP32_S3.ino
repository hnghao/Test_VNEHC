// Add the library
#include <MKL_LiquidCrystal_I2C.h>

// Khai báo 3 đối tượng LCD với địa chỉ và kích thước tương ứng
MKL_LiquidCrystal_I2C lcd1(0x27, 16, 2); // LCD 1602 địa chỉ 0x27
MKL_LiquidCrystal_I2C lcd2(0x26, 20, 4); // LCD 2004 địa chỉ 0x26
MKL_LiquidCrystal_I2C lcd3(0x25, 20, 4); // LCD 2004 địa chỉ 0x25

const char* message = "TEST VNEHC I2C LCD";

void setup() {
  // Khởi tạo LCD 1
  lcd1.init();
  lcd1.backlight();
  
  // Khởi tạo LCD 2
  lcd2.init();
  lcd2.backlight();
  
  // Khởi tạo LCD 3
  lcd3.init();
  lcd3.backlight();
}

void loop() {
  // --- Hiển thị trên LCD 1 ---
  lcd1.setCursor(0, 0);       // Dòng 1
  lcd1.print(message);
  delay(2000);                // Đợi 2 giây
  lcd1.clear();               // Xóa để chuyển sang màn tiếp theo

  // --- Hiển thị trên LCD 2 ---
  lcd2.setCursor(0, 0);       // Dòng 1
  lcd2.print(message);
  delay(2000);
  lcd2.clear();

  // --- Hiển thị trên LCD 3 ---
  lcd3.setCursor(0, 0);       // Dòng 1
  lcd3.print(message);
  delay(2000);
  lcd3.clear();
}