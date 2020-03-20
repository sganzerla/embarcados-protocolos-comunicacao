# Protocolo MQTT (Message Queue Telemetry Transport)
<p>
Desenvolvido pela IBM no final dos anos 90, originalmente para sistemas de supervisão e coleta de dados, mas ainda assim pode ser utilizado com IoTs mesmo não sendo tão sofisticado quanto o AMQP.
</p>

### Funcionamento

<p>
MQTT funciona  no paradigma publish/subscribe. Sendo um broker para receber mensagens de publicadores quanto para enviar mensagens para quem assina as publicações dos publicadores. Um dos broker mais populares desse protocolo é o [Mosquito](http://mosquitto.org/) .

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
 

#### Fonte

[Embarcados](https://www.embarcados.com.br/mqtt-protocolos-para-iot)
