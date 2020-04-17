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

### Descrição

Uma lista vinculada das informações do dispositivo local e do dispositivo de mesmo vível será exibida mantida na camada de baixo nível do `ESP-NOW`. As informações dos dispositivos são usadas para enviar e receber dados. O `ESP-NOW` mantém as informações essenciais dos pares, como `MAC` e a chave no nível baixo. `EP-NOW` também armazena os dados frequentemente usados pela camada de aplicação para evitar a sobrecarga na manutenção secundária da lista vinculada.

As informações envolvidas sobre:

- o dispositivo local
  - `PMK`
  - `Role`
  
- o par (incluindo informações usadas com frequência e outras definidas pelo usuário)
  - `key`
  - `MAC Address`
  - `Role`
  - `Channel`

![image](https://user-images.githubusercontent.com/22710963/79470613-031b3680-7fd8-11ea-9071-79c3063639b2.png)


### Funcionamento

#### Definir o envio da função de `callback`
  
O envio da função `callback` pode ser usada para informar o sucesso ou falha da transmissão.

Algumas observações ao utilizar a função `sending-callback`:

- para comunicação `unicast`:
  - se a camada de aplicação não recebe o pacote, mas a função `callback` retorna sucesso, talvez isso seja:
    - ataques de um dispositivo não autorizado
    - erro de configuração da chave criptografada
    - pacote perdido na camada de aplicação
  - se a camada de aplicação recebeu o pacote mas a função `callback` retornou falha, talvez isso seja:
    - canal está ocupado e o `ACK` não é recebido.
  
A camada de aplicação pode retransmitir o pacote, nesse caso, o receptor precisa verificar o pacote retransmitido.

- para comunicação `multicast` (inclui `broadcast` também):
  - se a função de `callback` retornar sucesso, significa que o pacote foi enviado corretamente.
  - se a função de `callback` retornar falha, significa que o pacote não foi enviado com sucesso.
  
#### Definir a recepção da função `callback`

O retorno da função `callback` pode ser usado para informar a camada de aplicativo que o pacote enviado pelo par foi recebido. A função de retorno da chamada retornará o endereço MAC do par e a carga útil do pacote.

#### Se a chave precisar ser criptografada, a API que define o PMK (KOK) pode ser chamada para configurá-la

Se o `PMK` não estiver configurado, ele usará as configurações padrões.

#### Selecione a interface de comunicação para os dispositivos

Geralmente a interface `STATION` é definida para `CONTROLLER` e a interface `SOFTAP` para `SLAVE` e `COMBO`.

Não é recomendável enviar pacotes para um dispositivo que esteja somente no modo `STATION`, pois o mesmo pode estar em suspensão.

#### Selecione a mesma chave para todos os dispositivos. Chame a função para adicionar pares

Ver tabela descritiva no início da página.

#### Chame a função de envio para retornar o `payload`

Se a função de envio retornar o endereço MAC especificado, será enviada para o dispositivo especificado. Se a função de envio retornar `null`, será enviada a todos os pares, o que pode resultar em falha ou atraso na transmissão devido ao congestionamento da rede.

### Exemplo Código

```
void ICACHE_FLASH_ATTR simple_cb(u8 *macaddr, u8 *data, u8 len)
{
   int i;
   u8 ack_buf[16];
   u8 recv_buf[17];
   os_printf("now from[");
   for (i = 0; i < 6; i++)
      os_printf("%02X, ", macaddr[i]);
   os_printf(" len: %d]:", len);
   os_bzero(recv_buf, 17);
   os_memcpy(recv_buf, data, len < 17 ? len : 16);
   if (os_strncmp(data, "ACK", 3) == 0)
      return;
   os_sprintf(ack_buf, "ACK[%08x]", ack_count++);
   esp_now_send(macaddr, ack_buf, os_strlen(ack_buf));
}
void user_init(void)
{
   u8 key[16] = {0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44,
                 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44};
   u8 da1[6] = {0x18, 0xfe, 0x34, 0x97, 0xd5, 0xb1};
   u8 da2[6] = {0x1a, 0xfe, 0x34, 0x97, 0xd5, 0xb1};
   if (esp_now_init() == 0)
   {
      os_printf("esp_now init ok\n");
      esp_now_register_recv_cb(simple_cb);
      esp_now_set_self_role(1);
      esp_now_add_peer(da1, 1, key, 16);
      esp_now_add_peer(da2, 2, key, 16)
   }
   else
   {
      os_printf("esp_now init failed\n");
   }
}
void ICACHE_FLASH_ATTR demo_send(u8 *mac_addr, u8 *data, u8 len)
{
   esp_now_send(NULL, data, len); /* the demo will send to two devices which added by esp_now_add_peer() */
   //esp_now_send(mac_addr, data, len); /* send to the specified mac_addr * /
}
```

## Fonte

[ESP-NOW User Guide - 2016](https://www.espressif.com/sites/default/files/documentation/esp-now_user_guide_en.pdf) - Acessado em Maio 2020.

[Random Nerd Tutorials](https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide) - Acessado em Maio 2020.
