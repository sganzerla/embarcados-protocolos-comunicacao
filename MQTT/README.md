# Protocolo MQTT (Message Queue Telemetry Transport)
<p>
Desenvolvido pela IBM no final dos anos 90, originalmente para sistemas de supervisão e coleta de dados, mas ainda assim pode ser utilizado com IoTs mesmo não sendo tão sofisticado quanto o AMQP.
</p>

### Funcionamento

<p>

MQTT funciona  no paradigma publish/subscribe. Sendo um broker para receber mensagens de publicadores quanto para enviar mensagens para quem assina as publicações dos publicadores. Um dos broker mais populares desse protocolo é o Mosquito](http://mosquitto.org) 

<p> 

<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77186859-4f935500-6ab2-11ea-86f4-5c409c20e984.png">
  <img src="https://user-images.githubusercontent.com/22710963/77186859-4f935500-6ab2-11ea-86f4-5c409c20e984.png" alt="reset" style="max-width:100%;"></a></p> 

<p>
 As mensagens, ao serem publicadas, podem ser agrupadas em tópicos, algo muito similar ao conceito de URI, sendo separados por barras ("/"). Os assinantes podem recuperar as mensagens acessando os tópicos espcíficos informando os nomes completos ou utilizando-se caracteres coringas como o sinal de mais ("+") e sharp ("#"). O caracter cifrão ($) indica que o tópico é reservado para uso interno do broker. 
</p>

<p>
Os seguintes tópicos abaixo de temperatura e umidade são oriundos de duas áreas diferentes (10, 20), monitorados por 4 sensores diferentes (5000, 5001, 4000, 4001) e registram duas informações distintas (temperatura e umidade):

```

  - area/10/sensor/5000/temperatura

  - area/10/sensor/5000/umidade

  - area/10/sensor/5001/temperatura

  - area/10/sensor/5001/umidade

  - area/20/sensor/4000/temperatura

  - area/20/sensor/4000/umidade

  - area/20/sensor/4001/temperatura

  - area/20/sensor/4001/umidade


```

</p>

<p>
Os assinantes podem se inscrever para assinar essas publicações especificando o tópico que desejam ou utilizar coringas para assinarem mais de um tópico ao mesmo tempo.

- Para assinar todas as publicações dos sensores de temperatura da área 10 o assinante poderia utilizar o caracter coringa mais ("+")

```

 area/10/sensor/+/temperatura

```

- Para monitorar todos os sensores da área 20 poderia ser utilizado o caracter sharp ("#") que significa "qualquer coisa abaixo do nível desse tópico "

```

area/20/sensor/#


```

</p>

#### Qualidade do Serviço (QoS)

<p>

Os clientes (publicadores e assinantes) conectam-se ao broker originalmente por TCP, sendo opcionais login (usuário/senha) e uso de criptografia SSL/TLS. As conexões precisam definir um nível de qualidade de serviço para a relação entre os comunicantes e o broker. O nível de qualidade pode ser diferente para o publicador e para o assinante.

</p>

##### QoS 0 (at most once)

<p>
"Best effort" ou melhor esforço, parecida com o protocolo UDP, não se tem confirmação da entrega da mensagem, quem publica também não tem obrigação de manter a mensagem armazenada p/ realizar nova retransmissão. Essa modalidade deve ser usada quando ocasionalmente a perda de dados não tão prejuízos a aplicação ou quando os dados forem enviados em intervalos curtos.
 
</p>
 
<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77193005-4ad39e80-6abc-11ea-9ab3-edc7c8290d18.png">
  <img src="https://user-images.githubusercontent.com/22710963/77193005-4ad39e80-6abc-11ea-9ab3-edc7c8290d18.png" alt="reset" style="max-width:100%;"></a></p> 


 ##### QoS 1 (at least once)
 <p>

Garante que uma mensagem seja entregue pelo menos uma vez ao destinatário. Existe a confirmação da entrega da mensagem. Quem envia a mensagem pode gerar várias mensagens iguais possivelmente por uma atraso na mensagem de confirmação de recebimento. Quem envia a mensagem deve manter a mensagem armazenada até que o receptor confirme o recebimento.

Usar quando não se pode perder mensagens e é esperado uma entrega rápida, a aplicação porém precisa ser tolerante e tratar possíveis mensagens duplicadas.

 </p>
<p>
<a target="_blank" href="https://user-images.githubusercontent.com/22710963/77193251-b584da00-6abc-11ea-810f-3603e6e2851e.png">
<img src="https://user-images.githubusercontent.com/22710963/77193251-b584da00-6abc-11ea-810f-3603e6e2851e.png" style="max-with:100%;">
</a>

</p>

 ##### QoS 2 (exactly once)
 <p>

Garante que a mensagem seja entregue exatamente uma vez, sendo retornado a confirmação do recebimento e a confirmação da confirmação do recebimento. É o nível mais seguro e mais lento. A confirmação de uma mensagem é feita por 4 handshake (aperto de mãos) entre remetente e destinatário.

Usado quando é essencial que a aplicação receba exatamente uma vez a mesma mensagem pois uma mensagem duplicada pode trazer prejuízos aos clientes assinantes.
 </p>

<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77194335-896a5880-6abe-11ea-89c3-f31f0b099795.png">
  <img src="https://user-images.githubusercontent.com/22710963/77194335-896a5880-6abe-11ea-89c3-f31f0b099795.png" alt="reset" style="max-width:100%;"></a></p> 

<p>
Todas as mensagens enviadas com QoS 1 e 2 são enfileiradas para os assinantes que estiverem offline. No entanto essa fila só é possível se o cliente tiver uma sessão persistente.
</p>


#### Métodos MQTT

<p>

MQTT define pacotes de controle (Control Packets) para indicar a ação desejada a ser executada pelo recurso desejado. Eles são os seguintes:

```

CONNECT
    Cliente solicita uma ligação com um servidor

CONNACK
    Reconhece solicitação de conexão

PUBLISH
    publicar mensagem

PUBACK
    reconhecimento de publicação

PUBREC
    Publicação recebida.(QoS 2 Publicação recebida., part 1)

PUBREL
    Publicação publicada. (QoS 2 Publicação recebida., part 2)

PUBCOMP
    Publicação completada. (QoS 2 Publicação recebida., part 3)

SUBSCRIBE
    Inscrever-se em um tópico

SUBACK
    Reconhecimento de inscrição

UNSUBSCRIBE
    Cancelamento de inscrição em um tópico

UNSUBACK
    Reconhecimento de cancelamento de inscrição.

PINGREQ
    PING request

PINGRESP
    PING response

DISCONNECT
    Notificação de desconexão

``` 

</p>


#### Fonte:

[Embarcados](https://www.embarcados.com.br/mqtt-protocolos-para-iot)

[HiveMQ](https://www.hivemq.com/blog/mqtt-essentials-part-6-mqtt-quality-of-service-levels)

[Wikipedia](https://pt.wikipedia.org/wiki/MQTT)
