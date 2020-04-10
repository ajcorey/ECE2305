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

 String title = "&title:40 Steps\n"; 
 String history = "&history:heres history about 40 steps...";
 String string = title + history;
 bool sendBT = true;

void loop() {
  if (SerialBT.hasClient() && sendBT) {
    //title
    for(long int letter = 0; letter < title.length();letter++){
      Serial.write(title[letter]);
      SerialBT.write(title[letter]);
    }
    
     
    //history
    for(long int letter = 0; letter < history.length();letter++){
      Serial.write(history[letter]);
      SerialBT.write(history[letter]);
    }
    sendBT = false;
  }
 
  if (SerialBT.available() && !sendBT) {
    while(SerialBT.available()){
      int readIn = SerialBT.read();
      Serial.write(readIn);
    }
    
  }

  if(!SerialBT.hasClient()){
    sendBT = true;  
  }
  delay(20);
}
