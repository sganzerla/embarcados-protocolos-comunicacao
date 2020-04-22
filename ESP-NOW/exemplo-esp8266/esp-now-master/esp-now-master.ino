/*
 Testing ESP-Now
 See https://espressif.com/en/products/software/esp-now/overview
 ESP-Now enables fast lightwieght connectionless communication between ESP8266's.
 So for example a remote sensor node could send a reading using ESP-Now in just a few
 hundred milliseconds and deepSleep the rest of the time and so get increased battery
 life compared to the node using a regular WiFi connection which could take 10 times
 as long to connect to WiFi and send a sensor reading.
 
 ESP-Now has the concept of controllers and slaves. AFAICT the controller is the remote
 sensor node and the slave is the always on "gateway" node that listens for sensor node readings.
 **** This sketch is the controller/sensor node ****
 *** Note: to compile ESP-Now (with arduino/esp8266 release 2.3.0) need to edit
 * ~/Library/Arduino15/packages/esp8266/hardware/esp8266/2.1.0/platform.txt
 * Search "compiler.c.elf.libs", and append "-lespnow" at the end of the line.
 * See: http://www.esp8266.com/viewtopic.php?p=44161#p44161
 ***
 Ant Elder
 License: Apache License v2
*/
#include <ESP8266WiFi.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_PIN D2

OneWire oneWire_ds18b20_1(ONE_WIRE_PIN);
DallasTemperature sensor_ds18b20_1(&oneWire_ds18b20_1);

extern "C"
{
#include <espnow.h>
}

// this is the MAC Address of the remote ESP which this ESP sends its data too
uint8_t remoteMac[] = {0x86, 0xF3, 0xEB, 0X62, 0x71, 0xEC};

#define WIFI_CHANNEL 1
#define SLEEP_TIME 36e8 //has to be number of seconds * 1000 * 1000 i.e. 10s is 10 * 1000 * 1000 = 10000000 or 1e7 ( 1 + 7 zeros) for testing 1e7
#define SEND_TIMEOUT 10000

// keep in sync with slave struct
struct SENSOR_DATA_DS18B20_1
{
    String name_ds18b20_1;
    float temp_ds18b20_1;
    float t_ds18b20_1;
};

volatile boolean readingSent;

void setup()
{

    Serial.begin(115200);
    Serial.println();

    WiFi.mode(WIFI_STA); // Station mode for sensor/controller node
    WiFi.begin();
    Serial.print("This node mac: ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init() != 0)
    {
        Serial.println("*** ESP_Now init failed");
        ESP.restart();
    }

    delay(1); // This delay seems to make it work more reliably???

    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_add_peer(remoteMac, ESP_NOW_ROLE_SLAVE, WIFI_CHANNEL, NULL, 0);

    esp_now_register_send_cb([](uint8_t *mac, uint8_t status) {
        Serial.print("send_cb, status = ");
        Serial.print(status);
        Serial.print(", to mac: ");
        char macString[50] = {0};
        sprintf(macString, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        Serial.println(macString);

        readingSent = true;
    });
    sensor_ds18b20_1.requestTemperatures();
    sendReading();
}

void loop()
{
    if (readingSent || (millis() > SEND_TIMEOUT))
    {
        Serial.print("Going to sleep, uptime: ");
        Serial.println(millis());
        ESP.deepSleep(SLEEP_TIME, WAKE_RF_DEFAULT);
        ESP.restart();
    }
}

void sendReading()
{
    void sendReading()
    {
        readingSent = false;
        SENSOR_DATA_DS18B20_1 sd_ds18b20_1;
        sd_ds18b20_1.name_ds18b20_1 = "B1";
        sd_ds18b20_1.temp_ds18b20_1 = sensor_ds18b20_1.getTempCByIndex(0);
        sd_ds18b20_1.t_ds18b20_1 = millis();

        Serial.print("sendReading, t=");
        Serial.println(sd_ds18b20_1.t_ds18b20_1);
        Serial.print(sd_ds18b20_1.name_ds18b20_1);
        Serial.print(" Temperature = ");
        Serial.print(sd_ds18b20_1.temp_ds18b20_1);
        Serial.println("\u2103");

        u8 bs[sizeof(sd_ds18b20_1)];
        memcpy(bs, &sd_ds18b20_1, sizeof(sd_ds18b20_1));
        esp_now_send(NULL, bs, sizeof(bs)); // NULL means send to all peers
    }