# Protocolo AMQP (Advanced Message Queuing Protocol)

<p>
É um protocolo que roda na camada de aplicação do modelo OSI rodando acima do protocolo TCP que pertence a camada de transporte. Ele permite o envio e recebimento de mensagens de forma assíncrona, sem retorno de confirmação do receptor. Pode ser vulgarmente definido como HTTP assíncrono onde o cliente comunica-se com um broker no meio do caminho.
</p>

<p>
Originalmente desenvolvido pela comunidade do mercado financeiro visava permitir a interoperabilidade entre dispositivos. É padronizado pela norma ISO/IEC 19464, está na versão 1.0.

</p>

### Funcionamento

#### Broker

<p>
Broker é uma entidade que recebe mensagens de publicadores, alguns clientes produzem mensagens como os publicadores e outras assinam mensagens, esses são clientes conhecidos como consumidores. AMQP é um protocolo bi-direcional onde o cliente pode enviar e receber mensagens através do broker.
</p>

<p>
Quando um publicador (publisher) produz uma mensagem, ele encaminha a uma entidade chamada "exchange" que possui regras configuráveis denominadas "binding" depois entram em filas (queues) e então são consumidos por um assinante (consumers). Uma característica do AMQP é que o "publisher" jamais publica uma mensagem diretamente para uma fila, ela sempre vai para o "exchange" e de acordo com seu tipo e conforme configurações especificadas através de "bindings" encaminha para determinada fila ou são descartados.

</p>

#### Exchange

<p>
É uma entidade que recebe as mensagens que chegam no broker oriundas das aplicações dos clientes. Estas aplicações não tem conhecimento nenhum sobre as filas, é o exchange que determina para qual fila deve ir uma mensagem recebida conforme as regras (binding)definidas.

</p>

<p>
Exchange possui nome, durabilidade, auto-delete, argumentos entre outros parametros. E podem ser de diferentes tipos conforme as características de roteamento: Direct, Fanout, Topic e Headers.  
</p>

##### Direct Exchange

<p>
Entrega mensagens às filas de acordo com o "routing key" definido na mensagem, ele deve possuir o mesmo que a fila.
</p>


<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77130121-66e02d00-6a35-11ea-9766-4b5b7d5f056b.png">
  <img src="https://user-images.githubusercontent.com/22710963/77130121-66e02d00-6a35-11ea-9766-4b5b7d5f056b.png" alt="reset" style="max-width:100%;"></a></p> 

<p>
 
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


#### Fonte

[Auto Core Robótica](https://autocorerobotica.blog.br/conhecendo-o-protocolo-spi-com-arduino)
