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

Nesse exemplo abaixo o módulo I2C para Display LCD possui esse recurso, bastando fazer uma ligação de solda nos pinos A0, A1 ou A2.

<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/76995597-d9b2b080-692e-11ea-8abc-f1f0983499db.png">
  <img src="https://user-images.githubusercontent.com/22710963/76995597-d9b2b080-692e-11ea-8abc-f1f0983499db.png" alt="reset" style="max-width:100%;"></a></p> 


#### Transmissão de dados
<p>
É realizada com um bit de start (S) enviada pelo mestre, em seguida o endereço físico do escravo e no bit LSB informa-se o que deve ser feito: uma leitura (HIGH) ou uma escrita (LOW). Após o escravo receber o dado de start ele devolve um bit de reconhecimento (ACK) deixando o pino de SDA como LOW, disponível para o mestre.
</p>

<p>
  Após o reconhecimento do dispositivo escravo o mestre envia os dados em duas partes, a primeira com 4 bits espera que o escravo retorne o bit de confirmação de recebimento para só então enviar a segunda com os outros 3 bits. Quando o escravo recebeu tudo corretamente ele permanece com o pino SDA como LOW até o mestre enviar a condição de STOP, caso contrário o escravo muda o valor para HIGH indicando não ter reconhecido o dado enviado pelo mestre.  
  </p>
  
  <p>
  <a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/76998072-344e0b80-6933-11ea-91ec-cec615d8c269.png">
  <img src="https://user-images.githubusercontent.com/22710963/76998072-344e0b80-6933-11ea-91ec-cec615d8c269.png" alt="reset" style="max-width:100%;"></a>  
  </p>

 #### Fonte:

http://autocorerobotica.blog.br/conhecendo-o-protocolo-i2c-com-arduino/
