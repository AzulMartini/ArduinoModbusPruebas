#include <SimpleModbusSlave.h>

/*
    CONEXIONES FÍSICAS E/ ARDUINO - RS485
    DE/RE (en serie)-> pin 4 
    RO -> RX
    DI -> TX

*/
//////////////// registers of your slave ///////////////////
enum
{    
  // just add or remove registers and your good to go...
  // The first register starts at address 0
  AI0, //0    
  AI1, //1
  AI2, //2
  AI3, //3
  TOTAL_ERRORS, //4      
  HOLDING_REGS_SIZE // leave this one
  // total number of registers for function 3 and 16 share the same register array
  // i.e. the same address space
};




unsigned int holdingRegs[HOLDING_REGS_SIZE]; // function 3 and 16 register array
unsigned int counter;
////////////////////////////////////////////////////////////


//void(* resetFunc) (void) = 0;


void setup()
{
  modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE, holdingRegs);
 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  holdingRegs[AI0] = 0;
  delay(100);
}


void loop()
{


  holdingRegs[AI0] = holdingRegs[AI0] + 1; // update data to be read by the master
  holdingRegs[AI1] = 1; // update data to be read by the master
  holdingRegs[AI2] = 2; // update data to be read by the master
  holdingRegs[AI3] = 3; // update data to be read by the master


  if (holdingRegs[AI1] == 12){
    digitalWrite(LED_BUILTIN, HIGH);
    holdingRegs[AI1] = 1;
  }  


holdingRegs[TOTAL_ERRORS] = modbus_update();
 
//  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
 
 
}
