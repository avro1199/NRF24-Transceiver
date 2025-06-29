// 8 Channel Transmitter (No Trim) | 8 Kanal Verici (Trim Yok)
// Input pin A5

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
const uint64_t pipeOut = 0xE8E8F0F0E1LL;  // NOTE: The same as in the receiver 000322 | Alıcı kodundaki adres ile aynı olmalı
RF24 radio(9, 10);                        // select CE,CSN pin | CE ve CSN pinlerin seçimi

struct Signal {
  byte throttle;
  byte pitch;
  byte roll;
  byte yaw;
  byte aux1;
  byte aux2;
  byte aux3;
  byte aux4;
};

Signal data;

void ResetData() {
  data.throttle = 0;
  data.pitch = 127;
  data.roll = 127;
  data.yaw = 127;
  data.aux1 = 0;  // Signal lost position | Sinyal kesildiğindeki pozisyon
  data.aux2 = 0;
  data.aux3 = 0;
  data.aux4 = 0;
}

void setup() {
  //Configure the NRF24 module  | NRF24 modül konfigürasyonu
  radio.begin();
  Serial.begin(115200);
  radio.openWritingPipe(pipeOut);
  radio.setChannel(100);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  // The lowest data rate value for more stable communication  | Daha kararlı iletişim için en düşük veri hızı.
  radio.setPALevel(RF24_PA_MAX);    // Output power is set for maximum |  Çıkış gücü maksimum için ayarlanıyor.
  radio.stopListening();            // Start the radio comunication for Transmitter | Verici için sinyal iletişimini başlatır.
  ResetData();

  for (int i = 14; i <= 19; i++) {
    pinMode(i, INPUT);
  }
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}
// Joystick center and its borders | Joystick merkez ve sınırları
int Border_Map(int val, int lower, int middle, int upper, bool reverse) {
  val = constrain(val, lower, upper);
  if (val < middle)
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);
  return (reverse ? 255 - val : val);
}
void loop() {
  // Control Stick Calibration for channels  |  Her bir kanal için kumanda Kol Kalibrasyonları

  data.roll = Border_Map(analogRead(A3), 0, 512, 1023, true);  // "true" or "false" for signal direction | "true" veya "false" sinyal yönünü belirler
  data.pitch = Border_Map(analogRead(A2), 0, 512, 1023, true);
  // data.throttle = Border_Map( analogRead(A1),570, 800, 1023, false );  // For Single side ESC | Tek yönlü ESC için
  data.throttle = Border_Map(analogRead(A1), 0, 512, 1023, false);  // For Bidirectional ESC | Çift yönlü ESC için
  data.yaw = Border_Map(analogRead(A0), 0, 512, 1023, true);
  data.aux1 = Border_Map(analogRead(A4), 0, 512, 1023, true);  // "true" or "false" for change signal direction | "true" veya "false" sinyal yönünü değiştirir.
  data.aux2 = Border_Map(analogRead(A5), 0, 512, 1023, true);  // "true" or "false" for change signal direction | "true" veya "false" sinyal yönünü değiştirir.
  data.aux3 = digitalRead(5);
  data.aux4 = digitalRead(4);

  radio.write(&data, sizeof(Signal));
  Serial.print(data.roll);
  Serial.print(" <=> ");
  Serial.print(data.pitch);
  Serial.print(" <=> ");
  Serial.print(data.throttle);
  Serial.print(" <=> ");
  Serial.println(data.yaw);
}