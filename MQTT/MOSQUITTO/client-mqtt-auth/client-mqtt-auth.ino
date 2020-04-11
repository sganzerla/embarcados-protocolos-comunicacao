
// https://www.embarcados.com.br/mqtt-dash/

//Acionamento de lampada com MQTT Dash
//Por: Fábio Souza
//Data: 12/02/18

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DEBUG

#include <Servo.h>

Servo meuservo; // instância chamada meuservo

#define MOTOR1_PIN D4
int limites_angulo_motor1[] = {0, 80};

int delayFechamento = 4000; // tempo para fechar o portão

#define L1 13 //pino de saida para acionamento da Lampada L1

//informações da rede WIFI
const char* ssid = "xxxxx";                 //SSID da rede WIFI
const char* password =  "xxxxxxx";    //senha da rede wifi //senha da rede wifi

//informações do broker MQTT - Verifique as informações geradas pelo CloudMQTT
const char *mqttServer = "192.168.1.8"; //server
const char *mqttUser = "yuri";            //user
const char *mqttPassword = "password";    //password
const int mqttPort = 1883;                   //port
const char *mqttTopicSub = "casa/L1";         //tópico que sera assinado

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{

  Serial.begin(115200);
  meuservo.attach(MOTOR1_PIN);
  pinMode(L1, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
#ifdef DEBUG
    Serial.println("Conectando ao WiFi..");
#endif
  }
#ifdef DEBUG
  Serial.println("Conectado na rede WiFi");
#endif

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected())
  {
#ifdef DEBUG
    Serial.println("Conectando ao Broker MQTT...");
#endif

    if (client.connect("ESP8266Client", mqttUser, mqttPassword))
    {
#ifdef DEBUG
      Serial.println("Conectado");
#endif
    }
    else
    {
#ifdef DEBUG
      Serial.print("falha estado  ");
      Serial.print(client.state());
#endif
      delay(2000);
    }
  }

  //subscreve no tópico
  client.subscribe(mqttTopicSub);
}

void loop()
{
  if (!client.connected())
  {
    reconect();
  }
  client.loop();
}

void callback(char *topic, byte *payload, unsigned int length)
{

  //armazena msg recebida em uma sring
  payload[length] = '\0';
  String strMSG = String((char *)payload);

#ifdef DEBUG
  Serial.print("Mensagem chegou do tópico: ");
  Serial.println(topic);
  Serial.print("Mensagem:");
  Serial.print(strMSG);
  Serial.println();
  Serial.println("-----------------------");
#endif

  //aciona saída conforme msg recebida
  if (strMSG == "1")
  { //se msg "1"
    movimentaMotor(meuservo, limites_angulo_motor1, true);
  }
}

//função pra reconectar ao servido MQTT
void reconect()
{
  //Enquanto estiver desconectado
  while (!client.connected())
  {
#ifdef DEBUG
    Serial.print("Tentando conectar ao servidor MQTT");
#endif

    bool conectado = strlen(mqttUser) > 0 ? client.connect("ESP8266Client", mqttUser, mqttPassword) : client.connect("ESP8266Client");

    if (conectado)
    {
#ifdef DEBUG
      Serial.println("Conectado!");
#endif
      //subscreve no tópico
      client.subscribe(mqttTopicSub, 1); //nivel de qualidade: QoS 1
    }
    else
    {
#ifdef DEBUG
      Serial.println("Falha durante a conexão.Code: ");
      Serial.println(String(client.state()).c_str());
      Serial.println("Tentando novamente em 10 s");
#endif
      //Aguarda 10 segundos
      delay(10000);
    }
  }
}

void movimentaMotor(Servo motor, int limite_angulo[], bool manterAberto)
{

  Serial.println(" ");
  for (int pos = limite_angulo[0]; pos <= limite_angulo[1]; pos += 1)
  {
    // crescente
    meuservo.write(pos);
    Serial.print(" ");
    Serial.print(pos);
    Serial.print(" ");
    delay(35);
  }
  Serial.println(" ");

  if (!manterAberto)
  {

    delay(delayFechamento);

    for (int pos = limite_angulo[1]; pos >= limite_angulo[0]; pos -= 1)
    {
      // descrescente
      meuservo.write(pos);
      Serial.print(" ");
      Serial.print(pos);
      Serial.print(" ");
      delay(35);
    }
  }
}