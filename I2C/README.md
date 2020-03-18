# Protocolo SPI (Serial Peripheral Interface)
<p>
Desenvolvido pela Motorola, precisa apenas de 3 fios mais um para cada dispositivo interligado a ele para que possa realizar a comunicação entre todos. O seu propósito é interligar periféricos a um dispositivo mestre ligando os escravos em série.
</p>
### Principais conexões
<p>

- MISO(Master In Slave Out): Uso do barramento slave para enviar dados do escravo para o mestre.

- MOSI(Master Out Slave In): Uso do barramento master para enviar dados do mestre para os periféricos escravos.

- SCLK(Serial Clock): O relógio de pulsos que sincroniza a transmissão de dados gerada pelo mestre.

</p>
#### Exemplo de ligação de dispositivos

<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/76923712-f9a48e80-68b2-11ea-9931-b6771902471f.png">
  <img src="https://user-images.githubusercontent.com/22710963/76923712-f9a48e80-68b2-11ea-9931-b6771902471f.png" alt="reset" style="max-width:100%;"></a></p> 




https://autocorerobotica.blog.br/conhecendo-o-protocolo-spi-com-arduino/