#include <WiFi.h>
#include <WebSocketClient.h>

const char* ssid = "Samed";
const char* password = "*****";

char path[] = "/";
char host[] = "192.168.1.3";
String input;

WebSocketClient webSocketClient;
WiFiClient client;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);

  if (client.connect(host, 8055)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }

  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
    Serial.println("Enter your message:");
    

  } else {
    Serial.println("Handshake failed.");
  }



}

void loop() {
  String data;

  if (client.connected()) {
    if (Serial.available()) {
      input = Serial.readStringUntil('\n');
      webSocketClient.sendData(input);
      Serial.println("your message:" + input + ":)");
    }

    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }

  } else {
    Serial.println("Client disconnected.");
  }

  delay(3000);

}
