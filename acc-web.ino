#include <SPI.h>
#include "MFRC522.h"

#define RST_PIN  25
#define SS_PIN  5

MFRC522 mfrc522(SS_PIN, RST_PIN);

String rfid_in = "";

void setup() {
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  digitalWrite(32, 1);  // buzzer off
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("");
}

void loop() {
  // mfrc522.PICC_IsNewCardPresent() = มองหา card ใหม่
  // mfrc522.PICC_ReadCardSerial() = เลือก card ใบใดใบหนึ่ง
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    rfid_in=rfid_read();  // ให้รันฟังก์ชั่นอ่าน rfid
    Serial.println(">>>> " + rfid_in);  // แสดง rfid ใน serial monitor
    if (rfid_in == "F6 70 B4 24") {   // เช็คว่าตรงกับ rfid ของตัวเองไหม 
      digitalWrite(32, 0);  // buzzer on
      delay(1000);
      digitalWrite(32, 1);  // buzzer off
      delay(1000);
      digitalWrite(33, 1);  // relay on
      delay(1000000);
      digitalWrite(33, 0);  // relay off
    } else {
      for (int i = 0; i < 3; i++) {
        digitalWrite(32, 0);  // buzzer on
        delay(650);           // delay 
        digitalWrite(32, 1);  // buzzer off
        delay(650);           // delay
      }
    }
  }
  delay(1);
}

// สร้างฟังก์ชั่นแปลงเลขฐาน 16 ในรูป 4 bytes
String rfid_read() {
  String content = "";  // สร้างตัวแปรรับค่า
  for (byte i = 0; i < mfrc522.uid.size; i++) // ลูปรับค่า
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));   // แปลงให้เป็นฐาน 16
    content.concat(String(mfrc522.uid.uidByte[i], HEX));  // แปลงให้อยู่ในรูป string
  }
  content.toUpperCase();  // แปลงให้เป็นตัวพิมพ์ใหญ่
  return content.substring(1);  // ตัดเอาข้อความในตำแหน่งที่ต้องการ
}