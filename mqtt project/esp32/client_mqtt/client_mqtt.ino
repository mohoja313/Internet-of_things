#include <WiFi.h>
#include <PubSubClient.h>


const char *ssid = "Product INT"; // Enter your Wi-Fi name
const char *password = "Pr1925D@11IoT";  // Enter Wi-Fi password
const char *mqtt_broker = "10.31.65.90"; // Enter your WiFi or Ethernet IP
const char *topic = "test/topic";
const int mqtt_port = 1883;WiFiClient espClient;
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
}
 
 // publish and subscribe
 client.publish(topic, "Hello From ESP32");
 client.subscribe(topic);
}void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 
 for (int i = 0; i < length; i++) {
  Serial.print((char) payload[i]);
 }
 
 Serial.println();
 Serial.println(" - - - - - - - - - - - -");
}void loop() {
 client.loop();
}
