#include <ESP8266WiFi.h>

const char* ssid = "(wifi name)"; const char* password = "(wifi password)";

int red = D5; int yellow = D6; int green = D7;

bool turniton = false; const unsigned long eventInterval = 3000; unsigned long previousTime = 0; int countme = 0;

WiFiServer server(80);

void setup() { Serial.begin(115200); delay(10);

pinMode(red, OUTPUT); pinMode(yellow, OUTPUT); pinMode(green, OUTPUT);

digitalWrite(red, LOW); digitalWrite(yellow, LOW); digitalWrite(green, LOW);

// Connect to WiFi network Serial.println(); Serial.println(); Serial.print("Connecting to "); Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); } Serial.println(""); Serial.println("WiFi connected");

// Start the server server.begin(); Serial.println("Server started");

// Print the IP address Serial.print("Use this URL : "); Serial.print("http://"); Serial.print(WiFi.localIP()); Serial.println("/");

}

void loop() { //cycle code unsigned long currentTime = millis(); if(turniton == true){ if(currentTime - previousTime >= eventInterval){ if(countme % 3 == 0){

      digitalWrite(red, HIGH);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
    }
    if(countme % 3 == 1){

      digitalWrite(red, LOW);
      digitalWrite(yellow, HIGH);
      digitalWrite(green, LOW);
    }
    if(countme % 3 == 2){

      digitalWrite(red, LOW);
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
    }
  
  countme++;
  previousTime = currentTime;
}
}

// Check if a client has connected WiFiClient client = server.available(); if (!client) { return; }

// Wait until the client sends some data Serial.println("new client"); while(!client.available() && turniton == true){ delay(1);

}

// Read the first line of the request String request = client.readStringUntil('\r'); Serial.println(request); client.flush();

// Match the request

if (request.indexOf("/RED") != -1) { digitalWrite(yellow, LOW); digitalWrite(green, LOW); digitalWrite(red, HIGH); } if (request.indexOf("/YELLOW") != -1){ digitalWrite(red, LOW); digitalWrite(green, LOW); digitalWrite(yellow, HIGH); } if (request.indexOf("/GREEN") != -1){ digitalWrite(red, LOW); digitalWrite(yellow, LOW); digitalWrite(green, HIGH); } if (request.indexOf("/OFF") != -1){ turniton = false; digitalWrite(red, LOW); digitalWrite(yellow, LOW); digitalWrite(green, LOW); }

if (request.indexOf("/CYCLE") != -1){
turniton = true; }

// Return the response client.println("HTTP/1.1 200 OK"); client.println("Content-Type: text/html"); client.println(""); // do not forget this one

//webpage client.println(""); client.println(""); client.println(""); client.println("<style>"); client.println(".redbtn {height: 20px; width: 90px; background: #FCCBC7; border-radius: 10px; padding-top:10px; padding-bottom:10px; padding-left: 60px; font-size: 20px; color: black;}"); client.println(".yellowbtn {height: 20px; width: 100px; background: #FFF5C6; border-radius: 10px; padding-top:10px; padding-bottom:10px; padding-left: 50px; font-size: 20px; color: black;}"); client.println(".greenbtn {height: 20px; width: 100px; background: #C9E2C2; border-radius: 10px; padding-top:10px; padding-bottom:10px; padding-left: 50px; font-size: 20px; color: black;}"); client.println(".offbtn {height: 20px; width: 90px; background: #DAD4D4; border-radius: 10px; padding-top:10px; padding-bottom:10px; padding-left: 60px; font-size: 20px; color: black;}"); client.println(".cyclebtn {height: 20px; width: 100px; background: #DAD4D4; border-radius: 10px; padding-top:10px; padding-bottom:10px; padding-left: 50px; font-size: 20px; color: black;}"); client.println("a {text-decoration: none;}"); client.println("</style>"); client.println("");

client.println("
");

client.println("<a href="/RED"><div class="redbtn"> Red

"); client.println("<a href="/YELLOW"><div class="yellowbtn"> Yellow

"); client.println("<a href="/GREEN"><div class="greenbtn"> Green

"); client.println("<a href="/OFF"><div class="offbtn"> Off

"); client.println("<a href="/CYCLE"><div class="cyclebtn"> Cycle
"); client.println("");

delay(1); Serial.println("Client disconnected"); Serial.println("");

}
