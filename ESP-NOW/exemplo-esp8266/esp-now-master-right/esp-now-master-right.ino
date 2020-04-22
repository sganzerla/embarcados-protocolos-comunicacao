
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
} ED;

void setup()
{
    Serial.begin(115200);
    Serial.println();
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
    esp_now_set_self_role(1);

    // lendo valor do SD Card
    ED.side = "R";

    // Pareamento com o dispositivo SLAVE
    // Definir STATION MAC do dispositivo SLAVE aqui
    // lendo valor do SD Card
    uint8_t mac_addr[6] = {0xD8, 0xF1, 0x5B, 0x0C, 0xDE, 0x4B};
    uint8_t role = 2;
    uint8_t channel = 3;
    uint8_t key[0] = {}; // pode-se definir uma chave //uint8_t key[16] = {0,255,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    uint8_t key_len = sizeof(key);
    Serial.print("Tamanho da chave: ");
    Serial.println(key_len);

    // adicionando pareamento
    esp_now_add_peer(mac_addr, role, channel, key, key_len);
}

void loop()
{

    ED.potenciometro = analogRead(A0);
    Serial.print("Side: ");
    Serial.print(ED.side);
    Serial.print(". Potenciometro: ");
    Serial.print(ED.potenciometro);
    ED.tempo = millis();
    Serial.print(". Tempo: ");
    Serial.print(ED.tempo);
    Serial.println();
    // Enviando dados
    // se o valor for NULL os dados são enviados a todos os dispositivos pareados
    // senão informar o STATION MAC SLAVE
    uint8_t da[6] = {0xD8, 0xF1, 0x5B, 0x0C, 0xDE, 0x4B};
    uint8_t data[sizeof(ED)];
    memcpy(data, &ED, sizeof(ED));
    uint8_t len = sizeof(data);
    esp_now_send(da, data, len);

    // Se houver perda de dados no receptor deve-se aumentar esse tempo
    delay(20);
}
