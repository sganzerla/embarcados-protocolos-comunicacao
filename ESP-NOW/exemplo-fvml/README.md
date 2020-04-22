# ESP-NOW - Comunicação Master-Slave

## Créditos

Este tutorial é baseado na publicação do [FVML](https://www.fvml.com.br/2020/01/o-que-e-esp-now-e-como-funciona-codigo.html)

### Visão geral

Com esse tutorial será possível verificar a comunicação entre dois dispositivos utilizando o protocolo `ESP-NOW` enviando como mensagem o status de um botão no lado `MASTER` e acendendo um led no lado `SLAVE`.

### Vídeo
[![Vídeo](https://user-images.githubusercontent.com/22710963/80032601-ca8cc880-84c1-11ea-921e-d1b7c1e65e0b.png)](https://youtu.be/FUOs7lKOCe8)]

### Hardware necessário

- a) 2 NodeMCU ESP8266 ou mais
- b) 1 Botão Táctil
- c) 1 Protoboard de 400 pinos
- d) 2 LED 5V
- e) 3-6 Fio de conexão (`Jumper` tipo macho)

#### a) NodeMCU ESP8266

![image](https://user-images.githubusercontent.com/22710963/79626592-9e5ef980-8107-11ea-8245-9ef23642a350.png)

#### b) Botão Táctil

![image](https://user-images.githubusercontent.com/22710963/79934801-d2992980-8429-11ea-96bc-fd1b74d76aa0.png)

#### c) Protoboard 400 pinos

![image](https://user-images.githubusercontent.com/22710963/79626629-e716b280-8107-11ea-84f8-45d4f999800d.png)

#### d) LED 5V

Corrente em placas NodeMCU é 3v então não é necessário utilizar um resistor de 220ohms.

![image](https://user-images.githubusercontent.com/22710963/79626643-001f6380-8108-11ea-8705-a3e44ed63dce.png)

#### e) Fio de conexão (`Jumper` tipo macho)

![image](https://user-images.githubusercontent.com/22710963/79626716-a1a6b500-8108-11ea-98b1-d4e4ff02e706.png)

### Montagem do Circuito

![image](https://user-images.githubusercontent.com/22710963/79934886-f9eff680-8429-11ea-83af-3f7732798f61.png)

## Fonte

[AGR Portfólio Educativo](http://agrportfolioeducativo.blogspot.com/2020/03/nodemcu-04espnow-comunicacion.html) - Acessado em Maio 2020.
