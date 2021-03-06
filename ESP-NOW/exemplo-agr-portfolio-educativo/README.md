# ESP-NOW - Comunicação Master-Slave

## Créditos

Este tutorial é baseado na publicação do [Portfólio Educativo](http://agrportfolioeducativo.blogspot.com/2020/03/nodemcu-04espnow-comunicacion.html)

### Visão geral

Com esse tutorial será possível enviar mensagens via ESP-NOW de um dispositivo `MASTER` para um dispositivo `SLAVE` utilizando dois ou mais `NodeMCU ESP8266`.

As mensagens nesse exemplo serão os valores lidos numa porta analógica de um potenciômetro no dispositivo `MASTER`. Os valores enviados para o dispositivo `SLAVE` acenderão um led variando a intensidade da luz conforme o valor recebido (0 - 1024).

### Vídeo
[![Vídeo](https://user-images.githubusercontent.com/22710963/79707084-b2cefd80-8291-11ea-9707-5355fad051d5.png)](https://youtu.be/N-B2Ebryfm0)]

### Hardware necessário

- a) 2 NodeMCU ESP8266 ou mais
- b) 1 Potenciômetro de 500k
- c) 1 Protoboard de 400 pinos
- d) 1 LED 5V  (1 para cada `MASTER`)
- e) 5 Fio de conexão (`Jumper` tipo macho)

#### a) NodeMCU ESP8266

![image](https://user-images.githubusercontent.com/22710963/79626592-9e5ef980-8107-11ea-8245-9ef23642a350.png)

#### b) Potenciômetro 500k

![image](https://user-images.githubusercontent.com/22710963/79626612-c77f8a00-8107-11ea-9c39-c90192c62aac.png)

#### c) Protoboard 400 pinos

![image](https://user-images.githubusercontent.com/22710963/79626629-e716b280-8107-11ea-84f8-45d4f999800d.png)

#### d) LED 5V

Corrente em placas NodeMCU é 3v então não é necessário utilizar um resistor de 220ohms.

![image](https://user-images.githubusercontent.com/22710963/79626643-001f6380-8108-11ea-8705-a3e44ed63dce.png)

#### e) Fio de conexão (`Jumper` tipo macho)

![image](https://user-images.githubusercontent.com/22710963/79626716-a1a6b500-8108-11ea-98b1-d4e4ff02e706.png)

### Montagem do Circuito

![image](https://user-images.githubusercontent.com/22710963/79627091-cc463d00-810b-11ea-9e62-4553dbd829e2.png)

### Identificar o MAC dos `NodeMCU ESP8266`

Antes de publicar o código nas placas é necessário descobrir o endereço MAC das placas para definir os pareamentos. Cada placa possui endereços distintos para comunicação como  `SOFTAP` e para comunicação como `STATION`, eles podem ser identificados usando o seguinte script.

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

### Fluxograma de comunicação `MASTER` X `SLAVE`

![image](https://user-images.githubusercontent.com/22710963/79627929-d7e93200-8112-11ea-9017-0fac7e9934fd.png)

## Fonte

[AGR Portfólio Educativo](http://agrportfolioeducativo.blogspot.com/2020/03/nodemcu-04espnow-comunicacion.html) - Acessado em Maio 2020.
