
#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"


#define WIFI_SSID "Nandadeepa"
#define WIFI_PASSWORD "12345678"
#define API_KEY "AIzaSyADkcqRduF7fqfMe3rtPcN4Op0lKgopHsk"
#define DATABASE_URL "https://alcuinwebapp-default-rtdb.asia-southeast1.firebasedatabase.app"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
int LEDOneState = 0;
int LEDTwoState = 0;
int LEDThreeState = 0;

bool signupOK = false;

void setup() {
  Serial.begin(115200);


  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);

 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(13, HIGH);
    Serial.print(".");
    delay(100);
    digitalWrite(13, LOW);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  digitalWrite(13, HIGH);

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
    digitalWrite(13, HIGH);
  }


  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);

  Firebase.RTDB.setString(&fbdo, "led/one", LEDOneState);
  Firebase.RTDB.setString(&fbdo, "led/two", LEDTwoState);
  Firebase.RTDB.setString(&fbdo, "led/three", LEDThreeState);

  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK  )   {
   
 
    if (Firebase.RTDB.getInt(&fbdo, "led/one")) {
      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
        LEDOneState = fbdo.to<int>();
      }
      else {
        Serial.println(fbdo.errorReason());
      }
    }
    if (LEDOneState == 0) {
      digitalWrite(26, LOW);

    }
    else {
      digitalWrite(26, HIGH);

    }
    if (Firebase.RTDB.getInt(&fbdo, "led/two")) {
      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
        LEDTwoState = fbdo.to<int>();
      }
      else {
        Serial.println(fbdo.errorReason());
      }
    }
    if (LEDTwoState == 0) {
      digitalWrite(25, LOW);

    }
    else {
      digitalWrite(25, HIGH);

    }
    if (Firebase.RTDB.getInt(&fbdo, "led/three")) {
      if (fbdo.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
        LEDThreeState = fbdo.to<int>();
      }

      else {
        Serial.println(fbdo.errorReason());
      }
    }


    if (LEDThreeState == 0) {
      digitalWrite(27, LOW);

    }
    else {
      digitalWrite(27, HIGH);

    }

  }

}
