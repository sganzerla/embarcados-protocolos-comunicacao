# Broker Mosquitto
 

#### SandBox Broker

- http://www.hivemq.com/demos/websocket-client/

- https://iot.eclipse.org/projects/sandboxes/

#### Mosquitto Broker

Demonstração realizada com publicador e assinante dentro da mesma máquina.
 
<p>
    <a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/78743497-289fa480-7935-11ea-8229-f3050a8a8069.png">
  <img src="https://user-images.githubusercontent.com/22710963/78743497-289fa480-7935-11ea-8229-f3050a8a8069.png" alt="reset" style="max-width:100%;">
  </a>
</p>

##### Criando o Broker no Ubuntu

1) Liberar no firewall porta padrão TCP 1883

```
$ sudo apt-get install ufw
$ sudo ufw allow 1883/tcp
$ sudo ufw enable
$ sudo ufw status verbose
```

<p>
    <a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/78740251-ad39f500-792c-11ea-8f40-0b17a5ed22a7.png">
  <img src="https://user-images.githubusercontent.com/22710963/78740251-ad39f500-792c-11ea-8f40-0b17a5ed22a7.png" alt="reset" style="max-width:100%;">
  </a>
</p>
  
2) Instalar broker

```
$ sudo apt-get update
$ sudo apt-get install mosquitto
```

3.1) Criar tópico e enviar mensagem sem autenticação

```
$ sudo mosquitto_pub -m "mensagem enviada sem autenticação" -t "test"
```

3.2) Criar usuário e senha p/ publicar mensagens e assinar publicações

```
$ sudo mosquitto_passwd -c /etc/mosquitto/passwd algum-login
Password: password
```

3.2.1) Criar o arquivo de configuração do mosquitto

```
$ sudo nano /etc/mosquitto/conf.d/default.conf
```

3.2.2) Desabilitar acesso anônimo e indicar lista de usuários. Colar dentro de default.conf

```
allow_anonymous false
password_file /etc/mosquitto/passwd
```

3.2.3) Reiniciar serviço para pegar as mudanças

```
$ sudo systemctl restart mosquitto
```

3.2.4) Publicar mensagem em um tópico com autenticação

```
$ sudo mosquitto_pub -t "test" -m "mensagem enviada com autenticação" -u "algum-login" -P "password"
```

##### Client Raspberry

Instalar Mosquitto-client

```
$ sudo apt-get install mosquitto-clients
```

Fazer inscrição em um tópico sem autenticação

```
$ sudo mosquitto_sub -t "test"
```

Fazer inscrição em um tópico com autenticação

```
$ sudo mosquitto_sub -t "test" -u "algum-login" -P "password"
```

Caso um cliente assine um tópico que exija autenticação sem enviar os parâmetros corretos receberá a mensagem de erro, o mesmo pode ocorrer quando um tópico originalmente anônimo passa a ser autenticado derrubando os clientes antes conectados.

```
Connection Refused: not authorised.
Error: The connection was refused.
```

</p>


#### Fonte:

[VULTR](https://www.vultr.com/docs/how-to-install-mosquitto-mqtt-broker-server-on-ubuntu-16-04)

[FilipeFlop](https://www.filipeflop.com/blog/controle-monitoramento-iot-nodemcu-e-mqtt/)
