#include <WiFi.h>
#include <WebServer.h>
WebServer server(80);
void redON()
{
  digitalWrite(23,1);
  server.send(200, "text/html","<center><h1>red OFF</h1><br><a href=\"/\">Back to homepage</a></html>");
}
void redOFF()
{
  digitalWrite(23,0);
  server.send(200, "text/html","<center><h1>red OFF</h1><br><a href=\"/\">Back to homepage</a></html>");
}
void greenON()
{
  digitalWrite(19,1);
  server.send(200,"text/html","<center><h1>Green ON</h1><br><a href=\"/\">Back to homepage</a></html>");
}
void greenOFF()
{
  digitalWrite(19,0);
  server.send(200,"text/html","<center><h1>Green OFF</h1><br><a href=\"/\">Back to homepage</a></html>");
}
void blueON()
{
  digitalWrite(18,1);
  server.send(200,"text/html","<center><h1>blue ON</h1><br><a href=\"/\">Back to homepage</a></html>");
}
void blueOFF()
{
  digitalWrite(18,0);
  server.send(200,"text/html","<center><h1>blue OFF</h1><br><a href=\"/\">Back to homepage</a></html>");
}
void relayON()
{
  digitalWrite(33,1);
  server.send(200,"text/html","<center><h1>relay ON</h1><br><a href=\"/\">Back to homepage</a></html>");
}
void relayOFF()
{
  digitalWrite(33,0);
  server.send(200,"text/html","<center><h1>relay OFF</h1><br><a href=\"/\">Back to homepage</a></html>");
}
void handleRoot()
{
  String s = "<html>";
  s += "<h1>MRP-IOT</h> <br><br>"
  s += "<center><a href=\"\\red\\on\">[ON]Red</a><br> ";
  s += "<a href=\"\\red\\off\">[OFF]Red</a> <br>";
  s += "<center><a href=\"\\green\\on\">[ON]Green</a><br> ";
  s += "<a href=\"\\green\\off\">[OFF]Green</a> <br>";
  s += "<center><a href=\"\\blue\\on\">[ON]Blue</a> <br>";
  s += "<a href=\"\\blue\\off\">[OFF]Blue</a> <br>";
  s += "<center><a href=\"\\relay\\on\">[ON]Relay</a> <br>";
  s += "<a href=\"\\relay\\off\">[OFF]Relay</a> <br>";
  s += "</html>";
server.send(200, "text/html", s);
}
void setup()
{
pinMode(23,OUTPUT);
pinMode(19,OUTPUT);
pinMode(18,OUTPUT);
pinMode(33,OUTPUT);
Serial.begin(115200);
Serial.println();
WiFi.mode(WIFI_AP);
WiFi.softAP("esp32-24", "12345678");
Serial.println();
Serial.print("Connected, IP address: ");
Serial.println(WiFi.localIP());
server.on("/red/on", redON);
server.on("/red/off", redOFF);
server.on("/green/on", greenON);
server.on("/green/off", greenOFF);
server.on("/blue/on", blueON);
server.on("/blue/off", blueOFF);
server.on("/relay/on", relayON);
server.on("/relay/off", relayOFF);
server.on("/", handleRoot);
server.begin();
}
void loop() {
  server.handleClient();
}
