/*
  Example usage of esp32 http request on BMKG API (no key requiered as of August 2024)
  
  This example use builtin led and (optional) buzzer for earthquake warning

  An (optional) led is used for the recording date, place and other usefull information of the earthquake
  

  Muhammad Nur Ilmih (with the help of awesome community and a lot of library)
  https://github.com/ilmihgila/esp32-eq-warning
*/

// Library bois!
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

char ssid[] = "{your ssid}"; // Wifi ssid
char password[] = "{your password}"; // Wifi password
const int buzzer = 19; // Optional buzzer 
const int LED = 2; // Builtin led 
#define SCREEN_WIDTH 128 // Display width
#define SCREEN_HEIGHT 64 // Display height
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Idk what this is, but do not change this

// Use whatever data that u need (this example use BMKG API), dont forget to change the JSON parsing if u change this
String serverData = "https://data.bmkg.go.id/DataMKG/TEWS/autogempa.json";
String waktuLama = ""; // Set to empty for the first iteration

void setup() {
  Serial.begin(115200); // Set baud rate on serial monitor
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.println("");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("INI PUNYA ILMIH! :)");
  display.display();


  // wait for wifi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient https;
    https.begin(serverData);
    int httpCode = https.GET();
    if (httpCode <= 0) {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpCode);
    }

    // Json parsing (adjusted to the current BMKG API)
    String payload = https.getString();
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);
    String waktu = doc["Infogempa"]["gempa"]["Jam"];
    String magnitude = doc["Infogempa"]["gempa"]["Magnitude"];
    String lokasi = doc["Infogempa"]["gempa"]["Wilayah"];
    Serial.println("GEMPA TERKINI");
    Serial.println("Waktu: " + waktu);
    Serial.println("Magnitudo: " + magnitude);
    Serial.println("Lokasi: " + lokasi);

    if (waktuLama != waktu){
      Serial.println("GEMPA TERKINI");
      Serial.println("Waktu: " + waktu);
      Serial.println("Magnitudo: " + magnitude);
      Serial.println("Lokasi: " + lokasi);     
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("GEMPA TERKINI");
      display.println("Waktu: " + waktu);
      display.println("Magnitudo: " + magnitude);
      display.println("Lokasi: " + lokasi);
      display.display();

      // Buzz when magnitude >= 5
      if(magnitude.toFloat() >= 5){
        for(int j = 0; j < 5; j++){
          digitalWrite(LED, HIGH);
          for(int i = 200; i < 5000; i += 20){
            tone(buzzer, i); // Send iKHz sound signal...
            delay(25);
          }
          digitalWrite(LED,LOW);
          for(int i = 5000; i > 200; i -= 20){
            tone(buzzer, i); // Send iKHz sound signal...
            delay(25);
          }
        }
        noTone(buzzer);
      }
    }
    
    waktuLama = waktu; // current is always be past! (Time indicator to make sure the received data is unique)
    https.end();
  }
  delay(50000);
}
