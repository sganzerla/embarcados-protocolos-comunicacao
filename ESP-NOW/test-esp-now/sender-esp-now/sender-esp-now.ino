#include <ESP8266WiFi.h>
extern "C"
{
#include <espnow.h>
}

//***ESTRUCTURA DE LOS DATOS TRANSMITIDOS MAESTRO/ESCLAVO***//
//Se de establecer IGUAL en el par esclavo
struct ESTRUCTURA_DATOS
{
    uint16_t potenciometro;
    uint32_t tiempo;
};

void setup()
{

    //***INICIALIZACIÓN DEL PUERTO SERIE***//
    Serial.begin(115200);
    Serial.println();
    Serial.println();

    //***INICIALIZACIÓN DEL PROTOCOLO ESP-NOW***//
    if (esp_now_init() != 0)
    {
        Serial.println("*** ESP_Now init failed");
        ESP.restart();
        delay(1);
    }

    //***DATOS DE LAS MAC (Access Point y Station) del ESP***//
    Serial.print("Access Point MAC de este ESP: ");
    Serial.println(WiFi.softAPmacAddress());
    Serial.print("Station MAC de este ESP: ");
    Serial.println(WiFi.macAddress());

    //***DECLARACIÓN DEL PAPEL DEL DISPOSITIVO ESP EN LA COMUNICACIÓN***//
    //0=OCIOSO, 1=MAESTRO, 2=ESCLAVO y 3=MAESTRO+ESCLAVO
    esp_now_set_self_role(1);

    //***EMPAREJAMIENTO CON EL ESCLAVO***//
    // Dirección MAC del ESP con el que se empareja (esclavo)
    // Se debe introducir la STA MAC correspondiente
    uint8_t mac_addr[6] = {0xD8, 0xF1, 0x5B, 0x0C, 0xDE, 0x4B}; // STA MAC esclavo
    uint8_t role = 2;
    uint8_t channel = 3;
    uint8_t key[0] = {}; //no hay clave
    //uint8_t key[16] = {0,255,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    uint8_t key_len = sizeof(key);
    Serial.print("Tamaño de *key: ");
    Serial.println(key_len);
    esp_now_add_peer(mac_addr, role, channel, key, key_len);
}

void loop()
{

    //***DATOS A ENVIAR***//
    ESTRUCTURA_DATOS ED;
    ED.potenciometro = analogRead(A0);
    Serial.print("Dato potenciometro: ");
    Serial.print(ED.potenciometro);    
    ED.tiempo = millis();
    Serial.print(". Dato tiempo: ");
    Serial.print(ED.tiempo);
    delay(20);
    
    //***ENVÍO DE LOS DATOS***//
    //uint8_t *da=NULL; //NULL envía los datos a todos los ESP con los que está emparejado
    uint8_t da[6] = {0xD8, 0xF1, 0x5B, 0x0C, 0xDE, 0x4B}; // ¿mismos datos que STA MAC?
    uint8_t data[sizeof(ED)];
    memcpy(data, &ED, sizeof(ED));
    uint8_t len = sizeof(data);
    esp_now_send(da, data, len);

    delay(1); //Si se pierden datos en la recepción se debe subir este valor

    //***VERIFICACIÓN DE LA RECEPCIÓN CORRECTA DE LOS DATOS POR EL ESCLAVO***//
    esp_now_register_send_cb([](uint8_t *mac, uint8_t status) {
        char MACesclavo[6];
        sprintf(MACesclavo, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        Serial.print(". Enviado a ESP MAC: ");
        Serial.print(MACesclavo);
        Serial.print(". Recepcion (0=0K - 1=ERROR): ");
        Serial.println(status);
    });
}
