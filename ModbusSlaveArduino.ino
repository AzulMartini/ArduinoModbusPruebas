/**
 *  Modbus slave example 3:
 *  The purpose of this example is to link a data array
 *  from the Arduino to an external device through RS485.
 *
 *  Recommended Modbus Master: QModbus
 *  http://qmodbus.sourceforge.net/
 * CONEXIONES FÍSICAS E/ ARDUINO - RS485

    DE/RE (en serie)-> pin 4 
    RO -> RX
    DI -> TX

 */

#include <ModbusRtu.h>

// assign the Arduino pin that must be connected to RE-DE RS485 transceiver
#define TXEN	4 

// data array for modbus network sharing
uint16_t au16data[16] = {
  3, 1415, 9265, 4, 2, 7182, 28182, 8, 0, 0, 0, 0, 0, 0, 1, -1 };

/**
 *  Modbus object declaration
 *  u8id : node id = 0 for master, = 1..247 for slave
 *  port : serial port
 *  u8txenpin : 0 for RS-232 and USB-FTDI 
 *               or any pin number > 1 for RS-485
 */
Modbus slave(1,Serial,TXEN); // this is slave @1 and RS-485

void setup() {
  Serial.begin( 19200 ); // baud-rate at 19200
  slave.start();
}

void loop() {
  slave.poll( au16data, 16 );
}
