/**
 *
 *
 *  Created on: 05.03.2018
 * author: João Campos
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

const String Bearer_TOKEN = "1234567890";
const String serverIp = "192.168.1.12";
const String serverPort = "3000";

void openGate();
String readingRfid();

void setup() {

    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("MS NET", "internet2018");

}

void loop() {

    string code = readingRfid();

      // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url

        String request = "http://" + serverIp +":"+ serverPort;
        http.begin(request);
        String authorization = "Bearer "+ Bearer_TOKEN;

        http.addHeader("Authorization", authorization);
        /*
          // or
          http.begin("http://192.168.1.12/test.html");
          http.setAuthorization("user", "password");
          // or
          http.begin("http://192.168.1.12/test.html");
          http.setAuthorization("dXNlcjpwYXN3b3Jk");
         */


        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        // send payload as json
        String postPayload = "{rfidcode:" + code+"}";


        int httpCode = http.Post(postPayload);

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                openGate();

                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(10000);
}
/**
*
* Function for reading RFID
*/
String readingRfid(){

  return "1234";
}

/**
*
* Function for open Gate
*/
void openGate(){
  USE_SERIAL.println("Gate opened");

}
