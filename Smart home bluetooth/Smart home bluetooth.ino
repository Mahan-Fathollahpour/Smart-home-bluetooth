/*Author : Mahan Fathollahpour 
  date   : 12/4/2022   8:46 PM
  USE HC05 for bluetooth module and single channel relay for control the light 



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~include Libraries~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <SoftwareSerial.h>
#include <DallasTemperature.h>
#include <OneWire.h>


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~define macros~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define ONE_WIRE_BUS 4
#define Relay  8
#define RX 2
#define TX 3

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DS18B20 Temprarture Sensor setting up~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Software Serial~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 

SoftwareSerial myserial(RX,TXB80);    /*(RX|TX)*/

int state ;
void setup() {
  // put your setup code here, to run once:
pinMode(Relay,OUTPUT);

Serial.begin(9600);
myserial.begin(9600);

sensors.begin();
digitalWrite(8,1);

}

void loop() {
  // put your main code here, to run repeatedly:

  sensors.requestTemperatures(); 
  float tempF = sensors.getTempFByIndex(0);
  float tempC = sensors.getTempCByIndex(0);

  if(myserial.available()>0){

  
  state=myserial.read();

  if(state==100){  /*if HC05 received 'd' turn on the lamp */
    
    
    digitalWrite(Relay,0);
    
  }

  else if(state==99){ /*if HC05 received 'c' turn off the lamp */
    
    digitalWrite(Relay,1);
  }

  else if (state==101) {    /*if HC05 received 'e' send temprature report to me ! */

     myserial.print('\n');
     myserial.print("Temperature celcius:");
     myserial.print(tempC);
     myserial.print('\n');
     myserial.print("Temperature Farenhait :");
     myserial.println(tempF);
     
  }
  }
}


