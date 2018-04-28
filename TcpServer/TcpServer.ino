#include <ESP8266WiFi.h>

const char* ssid = "FAST_B638";
const char* password = "QQ3503170";

WiFiServer server(23);
WiFiClient client;
String dataContent ;


void setup() {
  Serial.begin(115200);
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
    if (client.available()) {
      dataContent = readFromClient(client);
      Serial.println("print---" + dataContent);
      dataContent = "output-" + dataContent;
      clientWrite(client, dataContent);
    }
    dataContent = "";
  }
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
