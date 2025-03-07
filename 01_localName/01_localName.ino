#include <ArduinoBLE.h>

// Crear el servicio Device Information con UUID 180A
BLEService deviceInfoService("180A");

// Características del DIS
BLEStringCharacteristic manufacturerCharacteristic("2A29", BLERead, 20);
BLEStringCharacteristic modelCharacteristic("2A24", BLERead, 20);

void setup() {
  Serial.begin(115200);
  if (!BLE.begin()) {
    Serial.println("Fallo al iniciar BLE");
    while (1);
  }

  // Configurar el servicio DIS
  BLE.setLocalName("MiDispositivo");
  BLE.setAdvertisedService(deviceInfoService);

  // Agregar características al servicio
  deviceInfoService.addCharacteristic(manufacturerCharacteristic);
  deviceInfoService.addCharacteristic(modelCharacteristic);
  
  BLE.addService(deviceInfoService);

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
      // El dispositivo permanece en espera mientras está conectado
    }
    Serial.println("Dispositivo desconectado.");
  }
}
