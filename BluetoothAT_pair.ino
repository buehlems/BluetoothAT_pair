/*
  BluetoothAT_test: tests the  Bluetooth Shield v2.2
  Settings: Baud=38400, data bits: 8, stop bits: 1, parity none, flow control none
  Connection BT-Arduino: Tx - Rx3, Rx - Tx3

*/

/* This has been derived from:
NANODE SMA PV MONITOR
C:\Daten\Markus\Arduino\arduino-1.0.1\sketches\nanodesmapvmonitor
 
 Latest version found at https://github.com/stuartpittaway/nanodesmapvmonitor
 
 */
#define  __PROG_TYPES_COMPAT__ 1
#include <Arduino.h>
#include <HardwareSerial.h>

#include <Time.h> 

#include "Bluetooth.h"
#include "SMANetArduino.h"

#undef debugMsgln 
#define debugMsgln(s) (__extension__(  {Serial.println(F(s));}  ))
// #define debugMsgln(s) (__extension__(  {__asm__("nop\n\t"); }  ))

#undef debugMsg
#define debugMsg(s) (__extension__(  {Serial.print(F(s));}  ))
// #define debugMsg(s) (__extension__(  { __asm__("nop\n\t");  }  ))

#include "sma_support.h"



void printBlue(char *str){
  Serial.print(str);
  Serial3.print(str);
}

void getResponse(char *response){
  while(Serial3.available()) {
    int inByte = Serial3.read();
    Serial.write(inByte);
    *response++=inByte;
 }
}

void sendCMD(char *cmd){
  char response[128];
  printBlue(cmd);
  delay(100);        // delay in between reads for stability
  waitResponse();
  getResponse(response);
}
void waitResponse(){
  delay(100);
  Serial.println("check for response");
}

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(38400);
  Serial3.begin(38400);
  BTScanForSMAInverterToPairWith();	
}

// the loop routine runs over and over again forever:
void loop() {
  sendCMD("AT\r\n");
  delay(1000);
  sendCMD("AT+name?\r\n");
  delay(1000);
}
