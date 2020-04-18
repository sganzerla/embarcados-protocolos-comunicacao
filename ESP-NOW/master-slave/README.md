# ESP-NOW - Comunicação Master-Slave

## Créditos

Este tutorial é baseado na publicação do [Portfólio Educativo](http://agrportfolioeducativo.blogspot.com/2020/03/nodemcu-04espnow-comunicacion.html)

### Visão geral

Com esse tutorial será possível enviar mensagens via ESP-NOW do dispositivo `MASTER` para o dispositivo `SLAVE` utilizando dois ou mais `NodeMCU ESP8266`.

Nesse exemplo, será utilizado um potenciômetro no dispositivo `MASTER` para que envio o valor lido na porta analógica para o dispositivo `SLAVE` e com isso acendendo um led e variando a intensidade da luz.

### Hardware necessário

a - 2 NodeMCU ESP8266 ou mais
b - 1 Potenciômetro de 500k
c - 1 Protoboard de 400 pinos
d - 1 LED 5V  (1 para cada `MASTER`)
e - 5 Fio de conexão (`Jumper` tipo macho)

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

## Fonte

[AGR Portfólio Educativo](http://agrportfolioeducativo.blogspot.com/2020/03/nodemcu-04espnow-comunicacion.html) - Acessado em Maio 2020.
