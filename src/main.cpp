#include <gpio_viewer.h> // Must me the first include in your project
#include <WiFi.h>
#include <SPI.h>
#include <Update.h>
#include <ArduinoOTA.h>

GPIOViewer gpio_viewer;
char ssid1[] = "JBPhadtare"; // WIFI NETWORKS NAME
char password1[] = "9773829430"; // PASSWORD 

void initWifi(char ssid[], char password[]) {
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    pinMode(LED_BUILTIN, OUTPUT);
    byte number_of_available_networks = WiFi.scanNetworks();

    unsigned long scanStartTime = millis(); // Record the start time of the scan

    while (WiFi.scanComplete() == WIFI_SCAN_RUNNING) {
    // Wait for the scan to complete
    if (millis() - scanStartTime >= 20000) { // Timeout after 20 seconds
        Serial.println("WiFi scan timeout");
        break;
    }
    delay(100); // Adjust delay time as needed
    }


    if (WiFi.scanComplete() == WIFI_SCAN_FAILED) {
        Serial.println("WiFi scan failed");
    } else if (WiFi.scanComplete() == 0) {
        Serial.println("There are no available networks right now");
    } else {
        Serial.println("The scan was successful.\nHere are the available WiFi networks in your proximity.");
        for (int i = 0; i < number_of_available_networks; i++) {
            Serial.print(i + 1);
            Serial.print(". ");
            Serial.print(WiFi.SSID(i));
            Serial.print("\n");
    }
    Serial.println("Connecting to predefined target...");
    }

    WiFi.begin(ssid, password);
    unsigned long connectionTime = millis();

    while (WiFi.status() != WL_CONNECTED ) {
        // Wait for the scan to complete
            if (millis() - connectionTime >= 20000) { // Timeout after 20 seconds
            break;
        }
    delay(100); // Adjust delay time as needed
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("Successfully connected to predefined target ");
        Serial.print(ssid);
        for (int i = 0 ; i < 6 ; i++) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(300);
            digitalWrite(LED_BUILTIN, LOW);
            delay(300);
        }
    } else {
        Serial.println("Failed to connect to desired network");
    }
}

void setup() {
    Serial.begin(115200);
    initWifi(ssid1, password1);
    gpio_viewer.begin(); //publish the data to monitor the micro controller
    ArduinoOTA.begin(WiFi.localIP(), "aditya_ka_esp", "mini-pekka" , InternalStorage); 
    //begin the OTA protocal 
}

void loop() {
    ArduinoOTA.handle(); // always check for an update 
    // Your code here
}
