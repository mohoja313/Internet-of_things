#include "WiFi.h"   /*Wi-Fi library included*/
#include "esp_wifi.h"  
const char *ssid = "ESP32AP";    /*SSID of ESP32 Access point*/
const char *password = "123456789";  /*password for Access point*/
void PrintStations()
{
  wifi_sta_list_t stationList;    /*Number of connected stations*/
  esp_wifi_ap_get_sta_list(&stationList);  
  Serial.print("N of connected stations: ");
  Serial.println(stationList.num);
  for(int i = 0; i < stationList.num; i++) {
    wifi_sta_info_t station = stationList.sta[i];
    for(int j = 0; j< 6; j++){
      char str[3];
      sprintf(str, "%02x", (int)station.mac[j]);  /*prints MAC address of connected station*/
      Serial.print(str);
      if(j<5){
        Serial.print(":");
      }
    }
    Serial.println();
  }
  Serial.println("-----------------");
}
 
void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);   /*initialize ESP32 Access point*/
  Serial.println();
  Serial.print("IP address: ");  
  Serial.println(WiFi.softAPIP());    /*prints Access point IP address*/
}
void loop() {
  PrintStations(); /*prints number of station*/
  delay(5000);  /*wait 5 sec to check for new stations MAC address*/
}
