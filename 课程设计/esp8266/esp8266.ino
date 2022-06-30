/*
 * 本代码已删除服务器连接信息
 */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
/* 连接您的WIFI SSID和密码 */
#define WIFI_SSID         ""
#define WIFI_PASSWD       ""
/* 设备的三元组信息*/
#define PRODUCT_KEY       ""//设备PRODUCT_KEY
#define DEVICE_NAME       ""//替换DEVICE_NAME
#define DEVICE_SECRET     ""//替换DEVICE_SECRET
#define REGION_ID         ""
/* 线上环境域名和端口号，不需要改 */
#define MQTT_SERVER       PRODUCT_KEY ".iot-as-mqtt." REGION_ID ".aliyuncs.com"
#define MQTT_PORT         1883
#define MQTT_USRNAME      DEVICE_NAME "&" PRODUCT_KEY

#define CLIENT_ID         ""
#define MQTT_PASSWD       ""

#define ALINK_BODY_FORMAT         "{\"id\":\"ESP8266\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
#define ALINK_TOPIC_PROP_POST     "/sys/" PRODUCT_KEY "/" DEVICE_NAME "/thing/event/property/post"

unsigned long lastMs = 0;
float RH,T,RH_sum,T_sum,distance;
//unsigned char count=0;
WiFiClient espClient;
PubSubClient  client(espClient);
/* 软串口 */
SoftwareSerial serial_51(D7,D8);//RX=d7,TX=d8
String UART_String="";

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    payload[length] = '\0';
    Serial.println((char *)payload);

}

void wifiInit()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWD);   //连接WiFi
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }
    Serial.println("Connected to AP");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  
    Serial.print("espClient [");
    client.setServer(MQTT_SERVER, MQTT_PORT);   // 连接WiFi之后，连接MQTT服务器 
    client.setCallback(callback);
}


void mqttCheckConnect()
{
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT Server ...");
        if (client.connect(CLIENT_ID, MQTT_USRNAME, MQTT_PASSWD))
        {
            Serial.println("MQTT Connected!");
        }
        else
        {
            Serial.print("MQTT Connect err:");
            Serial.println(client.state());
            delay(5000);
        }
    }
}


void mqttIntervalPost()//数据上报
{
    char param[32];
    char jsonBuf[128];
    sprintf(param, "{\"distance\":%f}",distance);
    sprintf(jsonBuf, ALINK_BODY_FORMAT, param);
    Serial.println(jsonBuf);
    boolean d = client.publish(ALINK_TOPIC_PROP_POST, jsonBuf);
    if(d){
      Serial.println("publish distance success"); 
    }else{
      Serial.println("publish distance fail"); 
    }
}


//https://blog.zeruns.tech
void setup() 
{
    /* initialize serial for debugging */
    Serial.begin(115200);
    Serial.println("Demo Start");
    wifiInit();
    unsigned char i=0;
    serial_51.begin(9600);
    serial_51.listen();
}

void loop()
{
  if(serial_51.available()>0)
  {
    if(serial_51.peek()!='\n')//在收到换行符前软串口接受数据并链接为字符串
    {
      UART_String+=(char)serial_51.read();
    }
    else
    {
      serial_51.read();
      Serial.print("serial_51 data:");
      Serial.println(UART_String);
      UART_String=UART_String.substring(12); //去掉字符串的前12个字符
      distance=UART_String.toFloat();
      Serial.print("distance:");  //向串口打印 Humidity:
      Serial.print(distance);    //向串口打印湿度数据
       UART_String=""; 
    if (millis() - lastMs >= 3000)
      {
        lastMs = millis();//获取Arduino开机后运行的时间长度
        mqttCheckConnect(); 
        /* 上报 */
        mqttIntervalPost();
      }
 
 client.loop();   
    }
 }
}
