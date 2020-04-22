#include <ESP8266WiFi.h>
extern "C"
{
#include <espnow.h>
}

/*
Estrutura de dados criada para transmitir os dados entre MASTER/SLAVE
Essa estrutura deve ser a mesma tanto no MASTER quanto no SLAVE
*/

struct ESTRUTURA_DADOS
{
    uint16_t potenciometro = 0;
    uint32_t tempo = 0;
    String side = "";
};

/*
PIN LED servem para para indicar a mudança de valor das mensagens 
recebidas do potenciometro dos dispositivos MESTRE em tempo real
Cada MESTRE conectado deve ter um LED no SLAVE
*/
#define PIN_LED_BLUE D6
#define PIN_LED_GREEN D7

void setup()
{
    Serial.begin(115200);
    Serial.println();

    // Inicializando protocolo ESP-NOW
    if (esp_now_init() != 0)
    {
        Serial.println("Erro esp_now_init() ... reconectando.");
        ESP.restart();
        delay(1);
    }

    // Printando o MAC MASTER e SLAVE do dispositivo
    Serial.print("SoftAP MAC: ");
    Serial.println(WiFi.softAPmacAddress());
    Serial.print("STATION MAC: ");
    Serial.println(WiFi.macAddress());

    // Definindo papel desse dispositivo conforme enum da documentação
    // 0=OCIOSO, 1=MASTER, 2=SLAVE y 3=MASTER+SLAVE
    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);

    // Declarando LEDs do MASTER
    pinMode(PIN_LED_BLUE, OUTPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);

    // Recebendo mensagens de ESP-NOW MASTER
    esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len) {
        char masterMAC[6];
        sprintf(masterMAC, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

        ESTRUTURA_DADOS ED;

        // copia n caracteres de uma área da memória de origem para uma
        // área de destino
        // void *memcpy(void *dest, const void * src, size_t n)
        memcpy(&ED, data, sizeof(ED));

        Serial.print("Lado: ");
        Serial.print(ED.side);
        Serial.print(". Potenciometro: ");
        Serial.print(ED.potenciometro);
        Serial.print(". Tempo: ");
        Serial.print(ED.tempo);
        Serial.println();
        if (ED.side == "L")
            analogWrite(PIN_LED_GREEN, ED.potenciometro);

        if (ED.side == "R")
            analogWrite(PIN_LED_BLUE, ED.potenciometro);
    });
}

void loop()
{
}
