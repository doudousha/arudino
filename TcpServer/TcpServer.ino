#include <ESP8266WiFi.h>

const char* ssid = "D-Link_DIR-612";
const char* password = "15111881955";
const char* myName ="001" ;

int wifi_led  = 12 ; 

WiFiServer server(23);
WiFiClient client;
String dataContent ;


void setup() {
  Serial.begin(115200);
  pinMode(wifi_led,OUTPUT);

   
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to "); Serial.println(ssid);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //start UART and the server
  Serial.begin(115200);
  server.begin();
  server.setNoDelay(true);

  Serial.print("Ready! Use 'telnet ");
  Serial.print(WiFi.localIP());
  Serial.println(" 23' to connect");




}

void loop() {
  while (!client.connected()) {
    client = server.available();
  }

  while (client.connected()) {
      notifyWifiStatus(true);
    if (client.available()) {
      dataContent = readFromClient(client);
      if(dataContent.indexOf("who are you?") >=  0 ) {
        clientWriteMyName(client);
      }else {
        Serial.println("print---" + dataContent);
        dataContent = "output-" + dataContent;
        clientWrite(client, dataContent);
      }
    }
    clearDataContent();
  }
  client.stop();
  notifyWifiStatus(false);
  Serial.println("client close" );
  delay(100);
}


void notifyWifiStatus(bool status) {
  if(status ) {
    digitalWrite(wifi_led, HIGH);
  }else {
    digitalWrite(wifi_led, LOW);
  }   
  
}
void clientWriteMyName(WiFiClient client){
 clientWrite( client,"myName:"+String(myName)) ;
}

void clearDataContent(){
  dataContent = "";
}

String readFromClient(WiFiClient client) {
  String result;
  while (client.available()) {
    char data = client.read();
    result += data ;
  };
  return result;
}

void clientWrite(WiFiClient client, String str) {
  int str_len = str.length() + 1;
  char char_array[str_len];
  str.toCharArray(char_array, str_len);
  client.write(char_array);
}