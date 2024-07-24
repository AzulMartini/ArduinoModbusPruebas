/* Programa serie - serie
 *  Toma datos desde el puerto serie del arduino (Serial) y lo envia a traves de un puerto serie por software (mySerial) al conversor RS485
 *  El conversor lo envia via formato fisico RS485 al conversor RS485-USB que aparece nuevamente como un puerto COM en la PC. 
 *  Para ver el puerto del arduino usamos el IDE de Arduino, y para ver el otro puerto usamo el visor de puerto serie Hercules 
 *  (Configuracion: 9600 Baudios, 8 bits, sin paridad, handshake OFF, Mode Free) 
 *  Al enviar datos por uno de los visores aparece en el otro y viceversa. El objetivo del progrma fue chekear la comunicacion bilateral y el armado del circuito
 *  
 *  Circuito
 *  
 *  Arduino a conversor RS485
 *  pin 11 (tx) --- DI
 *  pin 10 (rx) --- R0
 *  pin4 --- DE
 *  pin4 --- RE
 *  
 *  Conversor RS485 a conversor RS485-USB
 *  gnd --- pin3
 *  A --- 4
 *  B --- 5
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
const int pinDireccion = 4;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(pinDireccion, OUTPUT);
  Serial.println("Puerto Serie Arduino ON");
  mySerial.begin(9600);
//  mySerial.println("Hello, world?");
}

void loop() {
  // Cambiar a la dirección de escritura - DESDE CONVERSOR A ARDUINO
  digitalWrite(pinDireccion, LOW);
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }

  // Cambiar a la dirección de lectura -- DESDE ARDUINO A CONVERSOR
  digitalWrite(pinDireccion, HIGH);
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}
