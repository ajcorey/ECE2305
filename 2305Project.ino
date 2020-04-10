//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

 String string1 = "i should be able to type as much as i want in here. "; 
 String string2 = "how about i throw in a newline character because why not. \n hopefully its a new line \n";
 String string = string1 + string2;
 bool sendBT = true;

void loop() {
  if (SerialBT.hasClient() && sendBT) {
    for(long int letter = 0; letter < string.length();letter++){
      Serial.write(string[letter]);
      SerialBT.write(string[letter]);
    }
    sendBT = false;
  }
 
  if (SerialBT.available() && !sendBT) {
    while(SerialBT.available()){
      int readIn = SerialBT.read();
      Serial.write(readIn);
    }
    
//    sendBT = true;
  }

  if(!SerialBT.hasClient()){
    sendBT = true;  
  }
  delay(20);
}
