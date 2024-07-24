#include <ModbusRtu.h>

#define TXEN 4
uint16_t au16data[16];

// Datos simulados de la sonda AP-700
float sonda_data[] = {25.5, 7.2, 2.3, 4.1, 10.5, 35.2, 1.0,
                      26.0, 7.3, 2.4, 4.0, 10.3, 35.0, 1.1, 0.0, 0.0};

Modbus slave(1,Serial,TXEN); // esclavo en ID 1 y RS-485

void setup() {
  Serial.begin(19200); // Baud-rate en 19200
  slave.start();
}

void loop() {
  // Actualizar el array au16data con los datos de la sonda
  for (int i = 0; i < 16; ++i) {
    // Convertir cada valor de punto flotante a un valor entero para almacenarlo en au16data
    // Puedes ajustar la escala de conversión según sea necesario
    au16data[i] = (uint16_t)(sonda_data[i] * 10); // Escala por 10 para mantener un decimal
  }
  
  // Responder a las solicitudes de lectura de datos Modbus RTU
  slave.poll(au16data, 16);
}
