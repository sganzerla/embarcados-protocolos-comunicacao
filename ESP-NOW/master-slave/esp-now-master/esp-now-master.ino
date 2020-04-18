/*
Ejemplo de comunicación ESP-NOW por Dani No www.esploradores.com
***ESTE SKETCH CORRESPONDE AL PAR MAESTRO***
El sketch permite el envío de dos datos mediante la comunicación ESP-NOW a un par esclavo:
- En la variable -potenciometro- se envía el dato de la lectura de la entrada
analógica del ESP. Se leen y envían -valores entre 0 y 1023- que se hacen variar
mediante un potenciómetro y se utilizarán para regular la intensidad del LED conectado
en el circuito esclavo.
- En la variable -tiempo- se envía el dato del milisegundo en el que el que se envían
los datos al circuito esclavo.
¡¡¡IMPORTANTE!!!
Para hacer funcionar la comunicación ESP-NOW si se tiene instalado en Arduino como gestor
de tarjetas el: esp8266 by ESP8266 Community versión 2.3.0 (Se puede comprobar buscándolo en:
Herramientas->Placa:"NodeMCU 1.0(ESP-5BE Module)"->Gestor de tarjetas..., es necesario editar
el fichero: ~/Library/Arduino15/packages/esp8266/hardware/esp8266/2.1.0/platform.txt,
buscar "compiler.c.elf.libs", y añadir al final de la línea "-lespnow".
*/

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
};

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

    // Pareamento com o dispositivo SLAVE
    // Definir STATION MAC do dispositivo SLAVE aqui
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

    delay(20);

    // Organizando dados a enviar
    ESTRUTURA_DADOS ED;
    ED.potenciometro = analogRead(A0);
    Serial.print("Potenciômetro: ");
    Serial.print(ED.potenciometro);
    ED.tempo = millis();
    Serial.print(". Tempo: ");
    Serial.print(ED.tempo);

    // Enviando dados
    // se o valor for NULL os dados são enviados a todos os dispositivos pareados
    // senão informar o STATION MAC SLAVE
    uint8_t da[6] = {0xD8, 0xF1, 0x5B, 0x0C, 0xDE, 0x4B};
    uint8_t data[sizeof(ED)];
    memcpy(data, &ED, sizeof(ED));
    uint8_t len = sizeof(data);
    esp_now_send(da, data, len);

    // Se houver perda de dados no receptor deve-se aumentar esse tempo
    delay(1);

    // Confirma se os dados foram enviados
    esp_now_register_send_cb([](uint8_t *mac, uint8_t status) {
        char slaveMAC[6];
        sprintf(slaveMAC, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        Serial.print(". Enviado a SLAVE MAC: ");
        Serial.print(slaveMAC);
        Serial.print(". Recebido (0=0K - 1=ERROR): ");
        Serial.println(status);
    });
}
