#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Pinii pentru conectarea Bluetooth HC-05
const int bluetoothTx = 2; // Conectat la RX pe HC-05
const int bluetoothRx = 3; // Conectat la TX pe HC-05

// Pinii pentru conectarea modulului GPS NEO-6M
const int gpsTx = 6;       // Conectat la TX pe GPS
const int gpsRx = 7;       // Conectat la RX pe GPS

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);  // Configurare modul Bluetooth
SoftwareSerial gpsSerial(gpsTx, gpsRx);              // Configurare modul GPS
TinyGPSPlus gps;                                     // Obiect pentru TinyGPS++

float latitude, longitude;

void setup() {
  Serial.begin(9600);         // Conectare la serial monitor
  bluetooth.begin(9600);      // Initializare Bluetooth HC-05
  gpsSerial.begin(9600);      // Initializare GPS NEO-6M

  Serial.println("Așteptare semnal GPS...");
}

void loop() {
  // Citirea datelor de la GPS și actualizarea TinyGPS++
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());  // Transmiterea fiecărui caracter la TinyGPS++
  }

  // Verificăm dacă locația a fost actualizată
  if (gps.location.isUpdated()) {
    latitude = gps.location.lat();   // Latitudine
    longitude = gps.location.lng();  // Longitudine

    // Transmiterea datelor prin Bluetooth
    bluetooth.print(latitude, 6);
    bluetooth.print(",");
    bluetooth.print(longitude, 6);
    bluetooth.print("\n");

    // Opțional: Afișarea datelor pe serial monitor
    Serial.print("Latitudine: ");
    Serial.print(latitude, 6);
    Serial.print(", Longitudine: ");
    Serial.println(longitude, 6);

    delay(1000);  // Pauză între transmisii
  } 
}