#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//#include <Servo.h>
// http://blog.xuite.net/laoweiz/blog/494414489-WeMos+D1+with+Arduino+IDE+%E6%8E%83%E7%9E%84wifi%E7%B6%B2%E8%B7%AF
const char* ssid = "B-LINK";
const char* password = "wq123654987";
const int led = 12;
//Servo myservo;        // 创建一个舵机对象
int pos = 0;          // 变量pos用来存储舵机位置
ESP8266WebServer server(80);

void setup(void){
  //myservo.attach(10);
    pinMode(led, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", []{
     String state=server.arg("state");
       Serial.print("state:");
         Serial.println(state);

//          for(pos = 0; pos < 180; pos += 1){    // 舵机从0°转到180°，每次增加1°          
//              myservo.write(pos);           // 给舵机写入角度   
//              delay(15);                    // 延时15ms让舵机转到指定位置
//           }

 
 if(state=="ok") {
  digitalWrite(led, HIGH);
 }else{
  digitalWrite(led, LOW);
 }
     server.send(200, "text/plain",  state+"-"+millis());
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
