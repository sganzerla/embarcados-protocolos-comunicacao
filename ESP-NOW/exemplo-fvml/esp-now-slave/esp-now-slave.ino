//==========================================================================================//
// THIS CODE IS SLAVE - RECEIVER BUTTON                                                     //
// Edited and Adapted by: Engineer Jemerson Marques, On: 12.10.2019 - FVM Learning website  //
// Available at: https://www.fvml.com.br and on Youtube channel                             //
// https://www.youtube.com/c/FVMLearning - I hope you have fun - Good luck                  //
//------------------------------------------------------------------------------------------//

#include <ESP8266WiFi.h>

extern "C"
{
#include <espnow.h>
#include <user_interface.h>
}
uint8_t mac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};

//===========================================================================================
int Led1 = D6;

void initVariant()
{
    WiFi.mode(WIFI_AP);
    wifi_set_macaddr(SOFTAP_IF, &mac[0]);
}

//===========================================================================================
#define WIFI_CHANNEL 4

// must match the controller struct
struct __attribute__((packed))
DataStruct
{
    char text[32];
    unsigned int time;
};
DataStruct myData;

//===========================================================================================
void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println("Starting EspnowSlave.ino");
    Serial.print("This node AP mac: ");
    Serial.println(WiFi.softAPmacAddress());
    Serial.print("This node STA mac: ");
    Serial.println(WiFi.macAddress());
    pinMode(Led1, OUTPUT);

    if (esp_now_init() != 0)
    {
        Serial.println("*** ESP_Now init failed");
        while (true)
        {
        };
    }
    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(receiveCallBackFunction);
    Serial.println("End of setup - waiting for messages");
}
//===========================================================================================
void loop()
{
}

//===========================================================================================

void receiveCallBackFunction(uint8_t *senderMac, uint8_t *incomingData, uint8_t len)
{
    memcpy(&myData, incomingData, sizeof(myData));

    Serial.print("NewMsg ");
    Serial.print(myData.text);
    Serial.println();
    digitalWrite(Led1, !digitalRead(Led1));
}

//====================================== www.fvml.com.br ====================================
