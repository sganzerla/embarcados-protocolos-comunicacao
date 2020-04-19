# ESP-NOW - Comunicação Master-Slave

## Créditos

Este tutorial é baseado na publicação do [Random Nerd Tutorials](https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide)

### Visão geral

Com esse tutorial será possível enviar mensagens via ESP-NOW de um dispositivo `MASTER` para um dispositivo `SLAVE` utilizando dois ou mais `NodeMCU ESP8266`.

As mensagens enviadas por um dispositivo do tipo `MASTER` podem ser observadas no dispositivo `SLAVE` utilizando-se a porta Serial. Para fazer esse tutorial basta apenas duas placas NodeMCU ESP8266.

### Hardware necessário

- a) 2 NodeMCU ESP8266

#### a) NodeMCU ESP8266

![image](https://user-images.githubusercontent.com/22710963/79626592-9e5ef980-8107-11ea-8245-9ef23642a350.png)

## Conceitos

Depois de pareados dois dispositivos, a conexão é persistente, se por acaso uma placa perder a energia ou for reiniciada, ela se conectará automaticamente ao seu par quando for reiniciada novamente.

O `ESP-NOW` é muito versátil e pode-se ter comunicação unidirecional e biderecional em diferentes configurações.

### Comunicação `One-Way` (1 via)

Há fluxo de dados apenas de uma direção, do dispositivo `MASTER` para `SLAVE` ou vice e versa.

- 1 `MASTER` envia para 1 `SLAVE`
   Há fluxo de dados do dispositivo `MASTER` para `SLAVE`. Essa é uma configuração fácil de implementar e é ótima para enviar dados de leituras de sensores ou comandos `ON|OFF` para controlar `GPIOs`.

- 1 `MASTER` envia para vários `SLAVE`
  Há fluxo de dados  do dispositivo `MASTER` para outras `SLAVE`, mensagens podem ser para todas ou para apenas uma placa. Configuração ideal para fazer controle remoto com várias placas espalhadas pela casa.

- 1 `SLAVE` recebe dados de vários `MASTER`
   Essa configuração é ideal para coletar dados de vários nós de sensores e repassar para um servidor web centralizando numa placa apenas.

### Comunicação `Two-Way` (2 vias)

Cada dispositivo pode tanto enviar quanto receber mensagens a qualquer tempo. Apenas é preciso que tenha sido estabelecido pareamento entre as placas.

Essa modalidade pode ser aplicada com duas ou com mais placas da rede.

## Configurando as placas

Antes de publicar o código nas placas é necessário descobrir o endereço MAC das placas para definir os pareamentos.

### Identificar o MAC dos `NodeMCU ESP8266`

 Cada placa possui endereços distintos para comunicação como  `SOFTAP` e para comunicação como `STATION`, eles podem ser identificados usando o seguinte script.

```
#include <ESP8266WiFi.h>
void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println();
    Serial.print("AP MAC: ");
    Serial.println(WiFi.softAPmacAddress());
    Serial.print("STA MAC: ");
    Serial.println(WiFi.macAddress());
}
void loop() {}
```

Depois de descobrir o MAC `STATION` da placa `SLAVE`, deve-se alterar o código do arquivo master-sender.ino com valor correto:

```
// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xD8, 0xF1, 0x5B, 0x0C, 0xDE, 0x4B};
```

Depois de alterado basta carregar o código `master-sender.ino` para a placa `MASTER` e o código `slave-receiver.ino` para a placa `SLAVE`.

## Fonte

[Random Nerd Tutorials](https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide) - Acessado em Maio 2020.
