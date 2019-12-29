/* These are some support structures from  https://github.com/stuartpittaway/nanodesmapvmonitor
 */

#ifndef SMA_SUPPORT_H
#define SMA_SUPPORT_H 1

const prog_uchar PROGMEM smanet2packetx80x00x02x00[] ={
  0x80, 0x00, 0x02, 0x00};
const prog_uchar PROGMEM smanet2packet2[]  ={ 
  0x80, 0x0E, 0x01, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const prog_uchar PROGMEM SMANET2header[] = {  
  0xFF,0x03,0x60,0x65  };
const prog_uchar PROGMEM InverterCodeArray[] = {   
  0x5c, 0xaf, 0xf0, 0x1d, 0x50, 0x00 };  //SCAFFOLDS000  meaningless really!  This is our fake address on the SMA NETWORK
const prog_uchar PROGMEM fourzeros[]= {
  0,0,0,0};
const prog_uchar PROGMEM smanet2packet6[]={      
  0x54, 0x00, 0x22, 0x26, 0x00, 0xFF, 0x22, 0x26, 0x00};
const prog_uchar PROGMEM smanet2packet99[]= {
  0x00,0x04,0x70,0x00};
const prog_uchar PROGMEM smanet2packet0x01000000[]=  {
  0x01,0x00,0x00,0x00};

//Password needs to be 12 bytes long, with zeros as trailing bytes (Assume SMA INVERTER PIN code is 0000)
const prog_uchar PROGMEM SMAInverterPasscode[]={
  '0','0','0','0',0,0,0,0,0,0,0,0};

#endif
