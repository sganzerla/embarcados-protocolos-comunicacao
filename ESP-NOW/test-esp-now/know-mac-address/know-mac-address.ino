#include <ESP8266WiFi.h>
void setup() {
Serial.begin(115200); Serial.println();Serial.println();
Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress()); // MAC como AP
Serial.print("STA MAC: "); Serial.println(WiFi.macAddress()); // MAC como estacion-station
}
void loop() {}
