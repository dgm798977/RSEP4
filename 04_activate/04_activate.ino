#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

// Crear el servicio Device Information con UUID 180A
BLEService deviceInfoService("180A");

// Características del DIS
BLEStringCharacteristic manufacturerCharacteristic("2A29", BLERead, 20);
BLEStringCharacteristic modelCharacteristic("2A24", BLERead, 20);
BLECharacteristic accelCharacteristic("2C06", BLERead | BLENotify, sizeof(float) * 3);

BLEByteCharacteristic accelControlCharacteristic("2B33", BLEWrite);

bool accelEnabled = true;

void setup() {
  Serial.begin(115200);
  if (!BLE.begin()) {
    Serial.println("Fallo al iniciar BLE");
    while (1)
      ;
  }
  if (!IMU.begin()) {
    Serial.println("Error iniciando IMU!");
    while (1)
      ;
  }

  // Configurar el servicio DIS
  BLE.setLocalName("MiDispositivo");
  BLE.setAdvertisedService(deviceInfoService);

  // Agregar características al servicio
  deviceInfoService.addCharacteristic(manufacturerCharacteristic);
  deviceInfoService.addCharacteristic(modelCharacteristic);
  deviceInfoService.addCharacteristic(accelCharacteristic);
  deviceInfoService.addCharacteristic(accelControlCharacteristic);
  
  BLE.addService(deviceInfoService);
  accelControlCharacteristic.setEventHandler(BLEWritten, onWrite);

  // Escribir valores en las características
  manufacturerCharacteristic.writeValue("MiFabricante");
  modelCharacteristic.writeValue("ModeloX123");

  // Iniciar la publicidad BLE
  BLE.advertise();
  Serial.println("Dispositivo BLE en espera de conexión...");
}

void loop() {
  BLEDevice central = BLE.central();
  if (central) {
    Serial.println("Dispositivo conectado.");
    while (central.connected()) {
      if (accelEnabled) {
        float x, y, z;
        if (IMU.accelerationAvailable()) {
          IMU.readAcceleration(x, y, z);

          // Empaquetamos los datos en un array de floats
          float accelData[3] = { x, y, z };

          // Actualizamos la característica y notificamos
          accelCharacteristic.writeValue((byte*)accelData, sizeof(accelData));

          Serial.print("Accel: X=");
          Serial.print(x);
          Serial.print(" Y=");
          Serial.print(y);
          Serial.print(" Z=");
          Serial.println(z);
        }
      }
      delay(100);  // Pequeña pausa para evitar sobrecarga
    }
    Serial.println("Dispositivo desconectado.");
  }
}

void onWrite(BLEDevice central, BLECharacteristic characteristic) {
  if (characteristic.uuid() == "2B33") {
    uint8_t value = accelControlCharacteristic.value();
    accelEnabled = (value == 1);  // Si se recibe 1, activamos; si es 0, desactivamos

    Serial.print("Acelerómetro ");
    Serial.println(accelEnabled ? "Activado" : "Desactivado");
  }
}
