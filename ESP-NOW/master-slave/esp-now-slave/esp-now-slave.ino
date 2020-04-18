/*
Ejemplo de comunicación ESP-NOW por Dani No www.esploradores.com
***ESTE SKETCH CORRESPONDE AL PAR ESCLAVO***
El sketch permite la recepción de una comunicación vía ESP-NOW de dos datos enviados
por el par maestro.
- En la variable -potenciometro- se envía el dato de la lectura de la entrada
analógica del circuito maestro -valores entre 0 y 1023-, que se utilizarán
para regular la intensidad del LED conectado en el circuito esclavo.
- En la variable -tiempo- se envía el dato del milisegundo en el que el circuito maestro
realiza la comunicación con el circuito esclavo.
¡¡¡IMPORTANTE!!!
Para hacer funcionar la comunicación ESP-NOW si se tiene instalado en Arduino como gestor
de tarjetas el: esp8266 by ESP8266 Community versión 2.3.0 (Se puede comprobar buscándolo en:
Herramientas->Placa:"NodeMCU 1.0(ESP-12E Module)"->Gestor de tarjetas..., es necesario editar
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

/*
PIN LED servem para para indicar a mudança de valor das mensagens 
recebidas do potenciometro dos dispositivos MESTRE em tempo real
Cada MESTRE conectado deve ter um LED no SLAVE
*/
#define PIN_LED_BLUE D5
// STATION MAC
char *mac_addres_led_blue = '2C:F4:32:78:6D:55';
#define PIN_LED_GREEN D6
// STATIO MAC
char *mac_addres_led_green = "2C:F4:32:78:6A:29";
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
    esp_now_set_self_role(2);

    // Declarando LEDs do MASTER
    pinMode(PIN_LED_BLUE, OUTPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);
}

void loop()
{

    // Recebendo mensagens de ESP-NOW MASTER
    esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len) {
        char MasterMAC[6];
        sprintf(MasterMAC, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        //   Serial.print("Recebido de MASTER MAC: ");
        //  Serial.print(MasterMAC);

        ESTRUTURA_DADOS ED;
        memcpy(&ED, data, sizeof(ED));

        //  Serial.print(". Potenciômetro: ");
        //   Serial.print(ED.potenciometro);
        //  Serial.print(". Tempo: ");
        //   Serial.println(ED.tempo);
        Serial.println();
        Serial.print(MasterMAC);
        Serial.print("=");
        Serial.print(mac_addres_led_blue);
        if (MasterMAC == mac_addres_led_blue)
            analogWrite(PIN_LED_BLUE, ED.potenciometro);

        if (MasterMAC == mac_addres_led_green)
            analogWrite(PIN_LED_GREEN, ED.potenciometro);
    });
}
