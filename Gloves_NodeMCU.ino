




#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


byte msg [2];


const char* ssid = "kasda-C38861";
const char* password = "Your password";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.1.15:3000/api/convert";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;


void sendWordToServer(String word) {
  // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName;

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());

      http.addHeader("Content-Type", "application/json");

      // Data to send with HTTP POST

      int httpResponseCode = http.POST("{\"api_key\":\"" + word + """\"}");

      Serial.println(httpResponseCode);

      // Free resources
      http.end();

      lastTime = millis();
    }
  }

}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  WiFi.begin(ssid, password);
  //Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  String abd = "كيفك يا زلمة";

  //sendWordToServer(abd);
}



void loop() {
  if (Serial.available()) {

    // Send an HTTP POST request depending on timerDelay
    if ((millis() - lastTime) > timerDelay) {
      //Check WiFi connection status
      if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        String serverPath = serverName;

        // Your Domain name with URL path or IP address with path
        http.begin(client, serverPath.c_str());

        http.addHeader("Content-Type", "application/json");

        // Data to send with HTTP POST
        msg[0] = Serial.read();
        msg[1] = Serial.read();
        
        Serial.write(msg,2);

        int httpResponseCode = http.POST("{\"api_key\":\"" + String((char*)msg) + """\"}");

        //Serial.println(httpResponseCode);

        // Free resources
        http.end();

        lastTime = millis();
      }
    }
  }
}
