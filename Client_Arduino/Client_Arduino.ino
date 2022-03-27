#include <WiFi.h>
#include <WebSocketClient.h>
#include <ESP32Servo.h>
#include "config.h"
const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* ip = SECRET_IP;
const int port = SECRET_PORT;

char path[] = "/";
char host[] = "echo.websocket.org";
Servo servo;
WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections
WiFiClient client;

void setup() {
  
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
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
  

  // Connect to the websocket server
  if (client.connect(ip, port)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
    while(1) {
      // Hang on failure
    }
  }

  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
    while(1) {
      // Hang on failure
    }  
  }

}


void loop() {
  String data;

  if (client.connected()) {
    
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
    if(data=="begin"){

      Serial.print("Start process");
    }
     if(data=="open"){
      //servo open
      Open(5);
      //servo.detach();
      Serial.print("opening claw");
     }
     if(data=="close"){
      //servo close
      Close(10);
      //servo.detach();
      Serial.print("closing claw");
     }
    
  } else {
    Serial.println("Client disconnected.");
    while (1) {
      // Hang on disconnect.
    }
  }
  
  // wait to fully let the client disconnect
  delay(3000);
  
}

void Open(int spd){
  servo.attach(ServoPin);
  for (int pos = 85; pos > 15; pos -= 1) { 
    servo.write(pos);              
    delay(spd);                       
  }
  servo.detach();
  
}
void Close(int spd){
  servo.attach(ServoPin);
  for (int pos = 15; pos < 85; pos += 1) { 
    servo.write(pos);              
    delay(spd);                       
  }
  servo.detach();
  
}
