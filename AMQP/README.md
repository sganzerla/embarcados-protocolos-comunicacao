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
Broker é uma entidade que recebe mensagens de publicadores, alguns clientes produzem mensagens como os publicadores e outras assinam mensagens, esses são clientes conhecidos como consumidores. AMQP é um protocolo bi-direcional onde o cliente pode enviar e receber mensagens através do broker. Um dos principais Broker deste tipo é o RabbitMQ
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

##### Topic Exchange 

Comunicação padrão do tipo publicador/assinante (publish/subscribe), é utilizado para monitorar mensagens de acordo com critérios no routing key da mensagem. O assinante pode escolher que tipo de mensagem deseja receber e o publicador pode definir um assunto/tópico através do routing key para a mensagem.
 
</p>

Imagem exibe o roteamento de mensagem com "routing key" igual a "kern.warning" para 3 tópicos sendo apenas uma compatível com a chave. Os critérios de filtro são :

- "*" pode substituir uma palavra no "binding key"

- "#" pode substituir uma ou mais palavras no "binding key"

<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77130549-2a153580-6a37-11ea-9904-6bcec6684e38.png">
  <img src="https://user-images.githubusercontent.com/22710963/77130549-2a153580-6a37-11ea-9904-6bcec6684e38.png" alt="reset" style="max-width:100%;"></a></p> 

##### Fanout Exchange
<p>
Encaminha mensagens recebidas para todas as filas vinculadas ao exchange. A chave do roteamento das mensagens é ignorada e uma cópia da mensagem é encaminhada para cada assinante. 
Essa modalidade é bastante utilizada em jogos do tipo MMO (Massively multi-player) onde as atualizações do placar ou outros eventos globais precisam ser compartilhados por todos os jogadores.
</p>

##### Headers Exchange
<p>
Essa modalidade ignora o valor do routing key e utiliza atributos obtidos apartir do header. Uma mensagem é considerada correspondente quando o valor do cabeçalho for igual ao valor especificado nas regras do binding.
</p>
<p>
É possível vincular uma fila a um exchange utilizando mais de um cabeçalho como critério. Porém deve-se observar a configuração no broker para que ocorra a correspondência ao critério, isso é feito através do argumento setado em "x-match" se for definido como "any" qualquer um dos valores do cabeçalho que corresponder é o suficiente mas se for setado como "all" todos os valores do cabeçalho precisam corresponder para entrar na fila.
</p>

#### Filas (Queues)

Filas armazenam mensagens consumidas pelos clientes, elas possuem propriedades similares aos exchanges além de outras adicionais:

- Nome: podem ser definidos pelos clientes ou pelo broker

- Durabilidade: filas duráveis sobrevivem ao reinicio de um broker, as não duráveis são chamadas de transitórias. Uma fila durável não significa que as suas mensagens também sejam, serão recuperadas apenas as mensagens persistentes.

- Exclusiva: usada apenas por uma conexão e será excluída quando a conexão for fechada.

- Auto-Exclusão: a fila que possuir ao menos um consumidor é excluída quando o último cliente cancelar a assinatura.

- Argumentos: campo opcional usado por plugins para informar TTL, ou limite do tamanho da fila.

#### Fonte:

[Embarcados](https://www.embarcados.com.br/amqp-protocolo-de-comunicacao-para-iot)

[RabbitMQ](https://www.rabbitmq.com/tutorials/amqp-concepts.html)