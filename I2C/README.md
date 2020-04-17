# Protocolo I2C  

## Introdução

Desenvolvido pela `Philips` nos anos 80,  com o propósito de padronizar a comunicação entre diferentes dispositivos. Necessita apenas de dois pinos (`SDA` - para dados, `SCL` - `clock`) para conectar até 112 dispositivos para barramentos de 7 bits. Possui uma média de operação por volta de 400KHz, alguns dispositivos que utilizam esse tipo de interface são: display LCDs, RTCs (relógios), acelerômetros ...

### Funcionamento

O protocolo `I2C` funciona com a ideia de hierarquia onde existe um dispositivo mestre e os demais são escravos. A comunicação de dados ocorre no modo Half-Duplex, onde ambos dispositivos mandam e recebem dados mas apenas um envia por vez. O mestre é quem controla a ordem dos emissores e receptores dessa comunicação para evitar colisões de dados.

![image](https://user-images.githubusercontent.com/22710963/76994427-1bdaf280-692d-11ea-9c8b-17a251de3d41.png)

 Por ser do tipo `Half Duplex`, podem ocorrer alguns atrasos, quando o mestre enviar uma dado e o escravo não conseguir tratá-los fazendo com que o mestre force uma estado de espera. Não é possível inverter os pinos nesse barramento, `SDA` tem que ser ligado com `SDA` e `SCL` com `SCL`.

### Endereços no barramento

Para que seja possível que o mestre envie dados para um determinado escravo ele precisa saber o endereço do dispositivo, que está no formato hexadecimal. Pode ocorrer, muito raramente, de dois dispositos totalmente diferentes possuírem o mesmo endereço, nesses casos pode-se verificar se um dos dispositivos que estão em conflito possuem recurso para mudarem o endereço.

Um exemplo de alteração de endereços é o dos acelerômetros `GY-521`. Se o pino `ADO` estiver alimentado o endereço do dispositivo é `0x69` senão estiver ele será `0x68`.

![image](https://user-images.githubusercontent.com/22710963/79519760-24594280-802b-11ea-9c6d-3109892b7245.png)

Com esse código é possível testar se o endereço de um acelerômetro está correto com a ligação dos fios.

´´´
#include "Wire.h"

const int MPU_addr=0x69; // I2C address of the MPU-6050

void setup() {
Wire.begin();

Serial.begin(115200);
}

void loop() {
byte error;
// We are using the return value of
// the Write.endTransmisstion to see if
// a device did acknowledge to the address.
Wire.beginTransmission(MPU_addr);
error = Wire.endTransmission();

if (error == 0)
{
Serial.println("Device Found");
}
else
{
Serial.println("No Device Found");
}
delay(5000); // Wait 5 seconds and scan again
}

´´´

Nesse outro exemplo abaixo o módulo `I2C` para Display LCD possui esse recurso também, bastando fazer uma ligação de solda nos pinos `A0`, `A1` ou `A2`.

![image](https://user-images.githubusercontent.com/22710963/79517081-8615ae80-8023-11ea-8ea9-feefc6d5cd8f.png)


#### Diferença de ligação com I2C

Ligação de Tela LCD sem conexão `I2C`

![image](https://user-images.githubusercontent.com/22710963/79517369-5e731600-8024-11ea-9362-c47e6b824213.png)

Ligação de Tela LCD com conexão `I2C`

![image](https://user-images.githubusercontent.com/22710963/79517399-75196d00-8024-11ea-92dd-3d06dce1e55d.png)

### Transmissão de dados

É realizada com um bit de `start` `S` enviada pelo mestre, em seguida o endereço físico do escravo e no bit `LSB` informa-se o que deve ser feito: uma leitura `HIGH` ou uma escrita `LOW`. Após o escravo receber o dado de `start` ele devolve um bit de reconhecimento `ACK` deixando o pino de `SDA` como `LOW` disponível para o mestre.

![image](https://user-images.githubusercontent.com/22710963/76998072-344e0b80-6933-11ea-91ec-cec615d8c269.png)

Após o reconhecimento do dispositivo escravo o mestre envia os dados em duas partes, a primeira com 4 bits espera que o escravo retorne o bit de confirmação de recebimento para só então enviar a segunda com os outros 3 bits. Quando o escravo recebeu tudo corretamente ele permanece com o pino `SDA` como `LOW` até o mestre enviar a condição de STOP, caso contrário o escravo muda o valor para `HIGH` indicando não ter reconhecido o dado enviado pelo mestre.  

### Pinagem do protocolo I2C no Arduino e NodeMCU

|         Modelo     | SDA | SCL |
| -------------------|-----|-----|
|     Arduino UNO    |  A4 |  A5 |
|     Arduino MEGA   |  44 |  43 |
|     Arduino DUE    |  20 |  21 |
|     Arduino YÚN    |  19 |  18 |
|     Arduino MICRO  |  19 |  18 |
|    Arduino NANO    |  27 |  28 |
|   Arduino PRO MINI |  A4 |  A5 |
|      NODEMCU       |  D2 |  D1 |

### Fonte

[Auto Core Robótica](http://autocorerobotica.blog.br/conhecendo-o-protocolo-i2c-com-arduino) - Acessado em Março de 2020.
