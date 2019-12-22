#include <WiFiEspClient.h>

#include <WiFiEsp.h>

#include <IRremote.h>

#include <Servo.h>

Servo myservo; // create servo object to control a servo
                // a maximum of eight servo objects can be created

#define servoPin A2
 
int pos = 10; // variable to store the servo position

#include <WiFiEspUdp.h>

#include <PubSubClient.h>

#include "SoftwareSerial.h"

#include <Adafruit_NeoPixel.h>

#define clientId "577092705"//DeviceID

#define username "304833"//ProductID

#define password "2sSrATDl=BmqF0eSVzv4kNN234M="//authinfo 这里是api-key

#define WIFI_AP "1234567"

#define WIFI_PASSWORD "12345678"

void callback(char* topic, byte* payload, unsigned int length);

char MqttServer[] = "183.230.40.39";//onenet mqtt服务器地址

int port=6002; //onenet mqtt服务器端口

// 初始化以太网客户端对象 -- WiFiEspClient.h

WiFiEspClient espClient;

// 初始化DHT11传感器

//DHT dht(DHTPIN, DHTTYPE);

// 初始化MQTT库PubSubClient.h的对象

PubSubClient client(espClient);

SoftwareSerial soft(2, 3); // RX, TX

int status = WL_IDLE_STATUS;

unsigned long lastSend;

void setup() {
  
  myservo.attach(servoPin);
  Serial.begin(9600);

  InitWiFi();                                // 连接WiFi

  client.setServer( MqttServer, port );      // 连接WiFi之后，连接MQTT服务器

  client.setCallback(callback);
  
  lastSend = 0;
  
}

void InitWiFi()

{

  // 初始化软串口，软串口连接ESP模块

  soft.begin(9600);

  // 初始化ESP模块

  WiFi.init(&soft);

  // 检测WiFi模块在不在，宏定义：WL_NO_SHIELD = 255,WL_IDLE_STATUS = 0,

  if (WiFi.status() == WL_NO_SHIELD) {

    Serial.println("WiFi shield not present");

    while (true);

  }

  Serial.println("[InitWiFi]Connecting to AP ...");

  // 尝试连接WiFi网络

  while ( status != WL_CONNECTED) {

    Serial.print("[InitWiFi]Attempting to connect to WPA SSID: ");

    Serial.println(WIFI_AP);

    // Connect to WPA/WPA2 network

    status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);

    delay(50);

  }

  Serial.println("[InitWiFi]Connected to AP");

}


 void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");

  Serial.print(topic);

  Serial.print("] ");

  for (int i = 0; i < length; i++) {

    Serial.print((char)payload[i]);

  }

  Serial.println();

  //测试数据是否成功读取



  // Switch on the LED if an 1 was received as first character

  if ((char)payload[0] == '1') {

   for (pos = 10; pos < 100; pos += 1) 
  {
    myservo.write(pos);            
    delay(15);                    
  }

  } 

  else
  {
 
   pos= 0;
  Serial.write(pos);
    myservo.write(pos);              
    delay(15);                      
  //
    


  }
}

void loop() 
{
 if ( !client.connected() )
 {
    reconnect();
  }
  
  client.loop();
  
}




void reconnect() {

  // 一直循环直到连接上MQTT服务器

  while (!client.connected()) {

    Serial.print("[reconnect]Connecting to MQTT Server ...");

    // 尝试连接connect是个重载函数 (clientId, username, password)

    if ( client.connect(clientId, username, password) ) {

      Serial.println( "[DONE]" );

      client.publish("outTopic", "hello world");

      // ... and resubscribe

      client.subscribe("inTopic");

    } else {

      Serial.print( "[FAILED] [ mqtt connect error code = " );

      Serial.print( client.state() );

      Serial.println( " : retrying in 50 seconds]" );// Wait 5 seconds before retrying

      delay( 50 );

    }

  }

}



