# ESP-NOW

## Introdução

### Visão geral

É uma tecnologia de comunicação sem fio rápida que tem como característica a transmissão de pequenos pacotes. É ideal para lâmpadas inteligentes, dispositivos de controle remoto, sensores e outras aplicações.

O `ESP-NOW` é regulado pela norma **IEEE802.11** e foi desenvolvido pela empresa chinesa **Espressif**, a mesma das placas `ESP32` e `ESP8266`.

### Recursos (faz / não faz)

Capacidades do `ESP-NOW`:

- Comunicação `unicast` criptografada e não criptografada.
- Dispositivos pares criptografados e não criptografados.
- `Payload` de até 250 bytes.
- Envio da função `callback` pode ser configurada para informar camada de aplicação sobre falha ou sucesso na transmissão.

Limitações do `ESP-NOW`:

- Não suporta `Broadcast`, envio de mensagens do mestre para todos os escravos ao mesmo tempo.
- No máximo 10 pares criptografados são suportados no modo `Station`; no máximo 6 no modo `SoftAP` ou `SoftAP` + `Station`. Vários pares não criptografados são suportados, porém o número total deve ser menor que 20, contando com eventuais pares criptografados junto.
- `Payload` limitado a 250 bytes.

## Guia Usuário

### Decrição

Uma lista vinculada das informações do dispositivo local e do dispositivo de mesmo vível será exibida mantida na camada de baixo nível do `ESP-NOW`. A informações dos dispositivos são usadas para enviar e receber dados. O `ESP-NOW` mantém as informações essenciais dos pares, como `MAC` e a chave no nível baixo. `EP-NOW` também armazena os dados frequentemente usados pela camada de aplicação para evitar a sobrecarga na manutenção secundária da lista vinculada.

As informações envolvidas sobre:

- o dispositivo local
  - `PMK`
  - `Role` (função)
  
- o par (incluindo informações usadas com frequência e outras definidas pelo usuário)
  - `key`
  - `MAC Address`
  - `Role`
  - `Channel`

![image](https://user-images.githubusercontent.com/22710963/79470613-031b3680-7fd8-11ea-9071-79c3063639b2.png)

## Fonte

[ESP-NOW User Guide - 2016](https://www.espressif.com/sites/default/files/documentation/esp-now_user_guide_en.pdf) - Acessado em Maio 2020.
