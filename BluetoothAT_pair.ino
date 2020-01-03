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
#include "util.h"

#undef debugMsgln 
#define debugMsgln(s) (__extension__(  {Serial.println(F(s));}  ))
// #define debugMsgln(s) (__extension__(  {__asm__("nop\n\t"); }  ))

#undef debugMsg
#define debugMsg(s) (__extension__(  {Serial.print(F(s));}  ))
// #define debugMsg(s) (__extension__(  { __asm__("nop\n\t");  }  ))

#include "sma_support.h"

void bt_clear(void) {
  char c;
  util::println(F("bt_clear"));
  while (Serial3.available()) {
    c=Serial3.read();
    delay(10);
  }
  util::println(F("end bt_clear"));
}


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

char *InverterBTAddress=NULL;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(38400);
  Serial3.begin(38400);
  bt_clear();
  util::println(F("Wait for possible data"));
  delay(3000);
  if(Serial3.available()){
    util::println(F("got data from BT. Must be in data mode."));
  }
  else{
    // there is available after clear -> BT must be in cmd mode and waiting for AT commands
    Serial.println("must be in CMD-mode");
    InverterBTAddress=BTScanForSMAInverterToPairWith();
    util::println(F("\n\n"));
    util::printf (F("Now I am ready to be connected to the inverter. Its address is: %s\n"),InverterBTAddress);
    util::println(F("Unplug the Arduino, switch to DATA mode and replug."));
    util::println(F("The HC-05 should auto-connect. Watch out for blink-blink-pause. In the serial monitor you should see this sequence:"));	
    util::println(F("0x7e ~ | 0x1f . | 0x00 . | 0x61 a | 0x2a * | 0xc3 . | 0x08 . | 0x25 % | 0x80 . | 0x00 . | 0x00 . | 0x00 . | 0x00 . | 0x00 . | 0x00 . | 0x00 . | 0x02 . | 0x00 . | 0x00 . | 0x04 . | 0x70 p | 0x00 . | 0x0a . | 0x00 . | 0x00 . | 0x00 . | 0x00 . | 0x01 . | 0x00 . | 0x00 . | 0x00 ."));
  }
}

// the loop routine runs over and over again forever:
void loop() {
  unsigned char c;
  static int i=0;
  if(Serial3.available()){
    c=Serial3.read();
    if(++i > 16 || c == 0x7e){
      util::println();
      i=0;
    }
    util::print(F("0x"));
    if(c < 0x10)
      util::print(F("0"));
    util::printf(F("%x %c | "),c,(c >= 0x20 && c <= 0x7e) ? c : '.');
  }else{
    delay(10);
  }
}
