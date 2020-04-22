//==========================================================================================//
// THIS CODE IS MASTER - SEND BUTTON                                                        //
// Edited and Adapted by: Engineer Jemerson Marques, On: 12.10.2019 - FVM Learning website  //
// Available at: https://www.fvml.com.br and on Youtube channel                             //
// https://www.youtube.com/c/FVMLearning - I hope you have fun - Good luck                  //
//------------------------------------------------------------------------------------------//

#include <ESP8266WiFi.h>
extern "C" {
    #include <espnow.h>
}
// This is the MAC Address of the slave which receives the data
uint8_t mac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
#define WIFI_CHANNEL 4
int prevstate = LOW;
#define BTN D1
#define LED D6
//===========================================================================================
// must match the slave struct
struct __attribute__((packed)) 
DataStruct {
char text[32];
};
DataStruct buttonpressed;

struct __attribute__((packed)) 
DataStruct2 {
char text[32];
};
DataStruct2 buttonreleased;

//============================================================================================
void setup() {
  pinMode(BTN,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
    Serial.begin(115200); Serial.println();
    Serial.println("Starting EspnowController.ino");
    WiFi.mode(WIFI_STA); // Station mode for esp-now controller
    WiFi.disconnect();
    Serial.printf("This mac: %s, ", WiFi.macAddress().c_str());
    Serial.printf("slave mac: %02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.printf(", channel: %i\n", WIFI_CHANNEL);
    if (esp_now_init() != 0) 
    {
    Serial.println("*** ESP_Now initialization failed");
    }
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_add_peer(mac, ESP_NOW_ROLE_SLAVE, WIFI_CHANNEL, NULL, 0);
    strcpy(buttonpressed.text,"Button pressed");
    strcpy(buttonreleased.text,"Button Released");
    Serial.println("Setup finished");
}

//============================================================================================
void loop() {
    sendData();
}

//============================================================================================
void sendData() {
  int currentstate = digitalRead(BTN);
  if(prevstate != currentstate){
    if(currentstate == HIGH){
       uint8_t bs[sizeof(buttonpressed)];
        memcpy(bs, &buttonpressed, sizeof(buttonpressed));
        esp_now_send(NULL, bs, sizeof(buttonpressed));
        Serial.println(buttonpressed.text);
        digitalWrite(LED, LOW);
    }else if(currentstate == LOW){
        uint8_t bs[sizeof(buttonreleased)];
        memcpy(bs, &buttonreleased, sizeof(buttonreleased));
        esp_now_send(NULL, bs, sizeof(buttonreleased));
      Serial.println(buttonreleased.text);
      digitalWrite(LED, HIGH);
    }
  }prevstate = currentstate;
}

//====================================== www.fvml.com.br =====================================