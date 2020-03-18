# Protocolo I2C  
<p>
Desenvolvido pela Philips nos anos 80,  com o propósito de padronizar a comunicaçãoe entre diferentes dispositivos. Necessita apenas de dois pinos (SDA - para dados, SCL - nosso clock) para conectar até 112 dispositivos para barramentos de 7 bits. Possui uma média de operação por volta de 400KHz, alguns dispositivos que utilizam esse tipo de interface são: display LCDs, RTCs (relógios)...
</p>

#### Funcionamento

<p>
O protocolo I2C funciona com a ideia de hierarquia onde existe um dispositivo mestre e os demais são escravos. A comunicação de dados ocorre no modo Half-Duplex, onde ambos dispositivos mandam e recebem dados mas apenas um envia-os por vez. O mestre é que coordena essa comunicação para evitar colisões de dados.
</p>

<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/76994427-1bdaf280-692d-11ea-9c8b-17a251de3d41.png">
  <img src="https://user-images.githubusercontent.com/22710963/76994427-1bdaf280-692d-11ea-9c8b-17a251de3d41.png" alt="reset" style="max-width:100%;"></a></p> 



 #### Fonte:

http://autocorerobotica.blog.br/conhecendo-o-protocolo-i2c-com-arduino/
