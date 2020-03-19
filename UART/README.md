# Protocolo UART (Universal Asynchronous Receiver/Transmiter)
<p>
 Protocolo de transmissão e recepção universal assíncrono full duplex. Não existe um sinal de clock para sincronizar o sinal transmitido com o sinal recebido.
</p>


<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77001201-4d0cf000-6938-11ea-8ec1-f7c2754ca190.png">
  <img src="https://user-images.githubusercontent.com/22710963/77001201-4d0cf000-6938-11ea-8ec1-f7c2754ca190.png" alt="reset" style="max-width:100%;"></a></p> 

#### Funcionamento
<p>
Para que os bits possam ser transmitidos e recebidos, transmissor e receptor devem estar configurados com o mesmo valor de baudrate, dado em bits por segundo, que é a taxa de transmissão de dados entre os dispositivos.
</p>

<p>
Quando não há dados no barramento ele é colocado em estado Bus Idle, mantido em lógico HIGH. Quando um dispositivo possui dados para transmitir, primeiro é enviado um bit de inicialização chamado Start Bit, esse bit está em nível lógico LOW. Depois é enviado um byte (8 bits) e para encerrar o envio dos dados é enviado um bit chamado Stop Bit que possui estado lógico HIGH.
</p>

<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77005851-4d10ee00-6940-11ea-80ae-0b11bd281e9c.png">
  <img src="https://user-images.githubusercontent.com/22710963/77005851-4d10ee00-6940-11ea-80ae-0b11bd281e9c.png" alt="reset" style="max-width:100%;"></a></p> 




### Principais conexões

<p>

- MISO(Master In Slave Out): Uso do barramento slave para enviar dados do escravo para o mestre.

- MOSI(Master Out Slave In): Uso do barramento master para enviar dados do mestre para os periféricos escravos.

- SCLK(Serial Clock): O relógio de pulsos que sincroniza a transmissão de dados gerada pelo mestre.

</p>

#### Exemplo de ligação de dispositivos

<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/76923712-f9a48e80-68b2-11ea-9931-b6771902471f.png">
  <img src="https://user-images.githubusercontent.com/22710963/76923712-f9a48e80-68b2-11ea-9931-b6771902471f.png" alt="reset" style="max-width:100%;"></a></p> 

<p>
Os pinos SSX são os pinos de seleção (Slave Select), eles indicam qual dispositivo escravo o mestre quer se comunicar no momento. Quando o pino slave select está baixo há comunicação entre o escravo e o mestre, e quando está alto ele ignora o mestre. A arquitetura do tipo FULL DUPLEX permite que o envio e o recebimento de dados seja feito simultaneamente.
</p>

#### Pontos importantes

<p>

- A velocidade máxima de comunição entre os dispositivos é controlada pelo primeiro parâmetro no SPISettings, um chip de 15MHz deve ser setado como 15 000 000.

- O deslocamento de dados pode ser feito tanto pelo "bit mais significativo" (MSB) quanto pelo "bit menos significativo" (LSB). Isso é definido pelo segundo parâmetro do SPISettings, MSBFIRST ou LSBFIRST.


</p>

#### Vantagens

<p>

- Comunicação Full Duplex

- Flexibilidade no protocolo completo para os bits transferidos.

- Requer menos energia que o I2C por ter menos circuitos.

- Não requer resistores do tipo pull-up.

- Escravos não precisam de endereço único.

</p>

#### Desvantagens

<p>

- Requer mais pinos CI.

- Não há reconhecimento do escravo.

- Suporta apenas um dispositivo mestre.

- Nenhum protocolo de verificação de erros é definido.

</p>

#### Pinagem do protocolo SPI no Arduino

<p>
<a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/76925129-29559580-68b7-11ea-9267-c58700c13aca.png">
  <img src="https://user-images.githubusercontent.com/22710963/76925129-29559580-68b7-11ea-9267-c58700c13aca.png" alt="reset" style="max-width:100%;"></a></p> 


#### Fonte:

[Embarcados](https://www.embarcados.com.br/interface-grafica-para-uart/)
