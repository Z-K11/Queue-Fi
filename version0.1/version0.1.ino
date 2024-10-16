#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char* ssid = "ZK11";   
const char* password = "datastructures"; 
#define Max 100
class queue
{
  public:
  int q[Max];
  int front;
  int rear;
  static int ticket;
  queue()
  {
    front=-1;
    rear=-1;
  }
  void enqueue();
  void dequeue();
  int currentlyServing();
};
int queue::ticket =0;

ESP8266WebServer server(80);
bool LEDstatus = LOW;
queue disableCounter;
queue seniorCounter;
queue citizenCounter;
bool pushButton = digitalRead(0);


void setup() {
  pinMode(0,INPUT);
  Serial.begin(9600);
  delay(100);
  pinMode(D4, OUTPUT);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check NodeMCU is connected to Wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());
  server.on("/", handle_OnConnect);
  server.on("/disability", handle_disables);
  server.on("/senior", handle_seniors);
  server.on("/citizen", handle_citizens);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}
void loop() {
  server.handleClient();
  if(pushButton==LOW)
  {
    disableCounter.dequeue();
  }


}

void handle_OnConnect() {
  server.send(200, "text/html", customerMode()); 
}

void handle_disables() {
  disableCounter.enqueue();
  Serial.println("new Enque on disable Counter");
  server.send(200, "text/html", disableMode()); 
}

void handle_seniors() {
  seniorCounter.enqueue();
  Serial.println("new Enque on Seniors Counter");
  server.send(200, "text/html", seniorMode()); 
}
void handle_citizens() {
  citizenCounter.enqueue();
  Serial.println("new Enque on Citizenss Counter");
  server.send(200, "text/html", citizenMode()); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String customerMode(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Queue-Fi</title>\n";
  ptr +="<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #0902f8;margin: 50px auto 30px;} h3 {color: #0f0d6f;margin-bottom: 50px;}\n";
  ptr +=".button {display: inline-block;float: left;width: 290px;height:80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 150px 68px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-enqueue {background-color: #3498db;}\n";
  ptr +=".button-enqueue:active {background-color: #3498db;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Queue-Fi Managment System</h1>\n";
  ptr +="<h3>Version 0.1</h3>\n";
  ptr +="<div class=\"holder\">\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/disability\">En-Queue <br>Disability-Counter<br>Currently-Serving: ";
    ptr += disableCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/senior\">En-Queue <br>Seniors-Counter<br>Currently-Serving: ";
    ptr += seniorCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/citizen\">En-Queue <br>Citizens-Counter<br>Currently-Serving: ";
    ptr += citizenCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="</div>";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
String disableMode(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Queue-Fi</title>\n";
  ptr +="<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #0902f8;margin: 50px auto 30px;} h3 {color: #0f0d6f;margin-bottom: 50px;}\n";
  ptr +=".button {display: inline-block;float: left;width: 290px;height:80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 150px 68px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-enqueue {background-color: #3498db;}\n";
  ptr +=".button-enqueue:active {background-color: #3498db;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Queue-Fi Managment System</h1>\n";
  ptr +="<h3>Version 0.1</h3>\n";
  ptr +="<div class=\"holder\">\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/disability\">En-Queue <br>Disability-Counter<br>Currently-Serving: ";
    ptr += disableCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/senior\">En-Queue <br>Seniors-Counter<br>Currently-Serving: ";
    ptr += seniorCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/citizen\">En-Queue <br>Citizens-Counter<br>Currently-Serving: ";
    ptr += citizenCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="</div>";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
String seniorMode(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Queue-Fi</title>\n";
  ptr +="<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #0902f8;margin: 50px auto 30px;} h3 {color: #0f0d6f;margin-bottom: 50px;}\n";
  ptr +=".button {display: inline-block;float: left;width: 290px;height:80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 150px 68px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-enqueue {background-color: #3498db;}\n";
  ptr +=".button-enqueue:active {background-color: #3498db;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Queue-Fi Managment System</h1>\n";
  ptr +="<h3>Version 0.1</h3>\n";
  ptr +="<div class=\"holder\">\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/disability\">En-Queue <br>Disability-Counter<br>Currently-Serving: ";
    ptr += disableCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/senior\">En-Queue <br>Seniors-Counter<br>Currently-Serving: ";
    ptr += seniorCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/citizen\">En-Queue <br>Citizens-Counter<br>Currently-Serving: ";
    ptr += citizenCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="</div>";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
String citizenMode(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Queue-Fi</title>\n";
  ptr +="<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #0902f8;margin: 50px auto 30px;} h3 {color: #0f0d6f;margin-bottom: 50px;}\n";
  ptr +=".button {display: inline-block;float: left;width: 290px;height:80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 150px 68px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-enqueue {background-color: #3498db;}\n";
  ptr +=".button-enqueue:active {background-color: #3498db;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Queue-Fi Managment System</h1>\n";
  ptr +="<h3>Version 0.1</h3>\n";
  ptr +="<div class=\"holder\">\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/disability\">En-Queue <br>Disability-Counter<br>Currently-Serving: ";
    ptr += disableCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/senior\">En-Queue <br>Seniors-Counter<br>Currently-Serving: ";
    ptr += seniorCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="<a class=\"button button-enqueue\" href=\"/citizen\">En-Queue <br>Citizens-Counter<br>Currently-Serving: ";
    ptr += citizenCounter.currentlyServing();
    ptr += "</a>\n";
    ptr +="</div>";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

int queue::currentlyServing()
{
  return q[front+1];
}
void queue::enqueue()
{
  if((rear+1)%Max == front)
    return;
  ++ticket;
  //(((rear+1)%Max)==front) ? return : ++ticket;
  rear=(rear+1)%Max;
  q[rear]=ticket;
}
void queue::dequeue()
{
  if(rear == front)
    return;
  front = (front +1)%Max;
  //(rear == front ) ? return : front = (front+1)%Max;
}