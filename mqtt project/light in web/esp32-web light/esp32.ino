#include <WiFi.h>
#include <PubSubClient.h>


const char *ssid = ""; // Enter your Wi-Fi name
const char *password = "";  // Enter Wi-Fi password
const char *mqtt_broker = "192.168.1.5"; // Enter your WiFi or Ethernet IP
const char *topic = "test/topic";

const int mqtt_port = 1883;WiFiClient espClient;

const int PinBool = 23;


PubSubClient client(espClient);void setup() {
 // Set software serial baud to 115200;

 Serial.begin(115200);
 
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
 }
 
 Serial.println("Connected to the WiFi network");
 
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 
 while (!client.connected()) {
 String client_id = "esp8266-client-";
 client_id += String(WiFi.macAddress());
 
 Serial.printf("The client %s connects to mosquitto mqtt broker\n", client_id.c_str());
 
 if (client.connect(client_id.c_str())) {
  Serial.println("Public emqx mqtt broker connected");
  
 } else {
  Serial.print("failed with state ");
  Serial.print(client.state());
  delay(2000);
 }
 pinMode(ledPinBool, OUTPUT);
 pinMode(PinBool, INPUT);
 digitalRead(PinBool);
}
 
 // publish and subscribe
 client.publish(topic, "salam seyed");
 
 client.subscribe(topic);
}void callback(char *topic, byte *message, unsigned int length) {
 Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

 Serial.println(" - - - - - - - - - - - -");
}void loop() {
 if(digitalRead(PinBool)==1){
 client.publish(topic, "1");
 }
  else if(digitalRead(PinBool)==0){
 client.publish(topic, "0");
 }
 delay(1000);
 client.loop();
}
