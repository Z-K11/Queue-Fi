#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<WifiClient.h>
#include<ESP8266mDNS.h>
const char* ssid="ZK11";
const char* password="datastructures";
ESP8266WebServer server(80);
MDNSResponder mdns;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\n ");
  Serial.print("Connected to : ");
  Serial.print(ssid);
  Serial.print("\n");
  Serial.print("IP Address : ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
  server.on("/",[]
  {
    server.send(200,"text/hmtl","Hello World !!!!");
  });
  server.begin();
  Serial.print("HTTP SERVER STARTED \n");

}




void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
