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

#### Endereços no barramento

<p>
Para que seja possível que o mestre envie dados para um determinado escravo ele precisa saber o endereço, que está no formato hexadecimal, do dispositivo. Pode ocorrer, muito raramente, de dois dispositos totalmente diferentes possuírem o mesmo endereço nesses casos pode-se verificar se um dos dispositivos que estão em conflito possuem recurso para mudarem o endereço.   
</p>

Nesse exemplo o módulo I2C para Display LCD possui esse recurso, bastando fazer uma ligação de solda nos pinos A0, A1 ou A2.

<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/76995597-d9b2b080-692e-11ea-8abc-f1f0983499db.png">
  <img src="https://user-images.githubusercontent.com/22710963/76995597-d9b2b080-692e-11ea-8abc-f1f0983499db.png" alt="reset" style="max-width:100%;"></a></p> 


 #### Fonte:

http://autocorerobotica.blog.br/conhecendo-o-protocolo-i2c-com-arduino/
