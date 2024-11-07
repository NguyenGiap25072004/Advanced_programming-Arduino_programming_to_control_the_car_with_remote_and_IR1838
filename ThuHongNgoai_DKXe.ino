#include <IRremote.h>

const int chanRemote = 10;
IRrecv irrecv(chanRemote);
decode_results results;
int in1 = 3; // Bánh xe trái tiến
int in2 = 5; // Bánh xe trái lùi
int in3 = 6; // Bánh xe phải tiến
int in4 = 9; // Bánh xe phải lùi

unsigned long lastReceiveTime = 0; // Thời gian nhận tín hiệu cuối
const unsigned long stopDelay = 200; // Thời gian dừng sau khi mất tín hiệu
bool moving = false; // Trạng thái chuyển động

int speedLeft = 50;  // Tốc độ bánh xe trái (0 - 255)
int speedRight = 50; // Tốc độ bánh xe phải (0 - 255)

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT); 
}

void loop() {
  if (irrecv.decode(&results)) {
    lastReceiveTime = millis(); // Cập nhật thời gian nhận tín hiệu

    // Kiểm tra mã tín hiệu và điều khiển xe
    if (results.value == 0xFF18E7) { // Nhấn nút lên
      toi();
      moving = true;
    } else if (results.value == 0x1BC0157B) { // Nhấn nút xuống
      lui();
      moving = true;
    } else if (results.value == 0x8C22657B) { // Nhấn nút trái
      trai();
      moving = true;
    } else if (results.value == 0x449E79F) { // Nhấn nút phải
      phai();
      moving = true;
    } else if (results.value == 0x488F3CBB) { // Nhấn nút dừng
      dung();
      moving = false;
    }
    
    irrecv.resume(); // Chuẩn bị nhận tín hiệu mới
  }

  // Nếu không có tín hiệu mới trong khoảng thời gian stopDelay, dừng xe
  if (moving && (millis() - lastReceiveTime > stopDelay)) {
    dung();
    moving = false; // Đặt lại trạng thái
  }
}

void lui() {
  digitalWrite(in1, speedLeft);
  digitalWrite(in2, LOW);
  digitalWrite(in3, speedRight);
  digitalWrite(in4, LOW);
}

void toi() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, speedLeft);
  digitalWrite(in3, LOW);
  digitalWrite(in4, speedRight);
}

void dung() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void trai() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, speedLeft);
}

void phai() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, speedRight);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}