 //******************************************************************************
 // NodeESP Firmware
 // Version 1.5 28.02.2019
 // Copyright 2019 Fabian Kainka
 // Licensed under GNU GPL 3.0 and later, under this license absolutely no warranty given
 //
 // // See www.iot.fkainka.de for documentation
 //
 // Changelog:
 // Updated Framework (1.7) + Libraries (TCPAsync)
 //
 // FIX for error: C99 in esp_wps.cpp:
 // https://github.com/espressif/esp-idf/pull/2869/files
 // change file .platformio/packages/framework-arduinoespressif32/tools/sdk/include/esp32/esp_wps.h
 // line 81ff:
 // {.manufacturer = "ESPRESSIF"},
 // {.model_number = "ESP32"},  \
 // {.model_name = "ESPRESSIF IOT"},  \
 // {.device_name = "ESP STATION"},  \

 //******************************************************************************


//Current Version of APP, Spiff version is also saved in config file
#define VERSION "v1.5_28022019"
#define SPIFFS_VERSION "v1.2_16122018"

#include <SPIFFS.h>

#include "StatusLed.hpp"    //Status LED functions
#include "Config.hpp"       //configuration loading, saving and changing
#include "Commands.hpp"     //handles most commands
#include "Apps.hpp"         //handles execution of "apps"

void setup() {
        Serial.begin(115200);
        Serial.setDebugOutput(true);
        Serial.println("\n\nRUN\n");

        #ifdef AUTHORMODE
          Serial.println("Author Mode!");
        #endif

        //initialise the RGB LED to show status
        statusLedInit();

        //Spiffs is the file system on the Board. It includes every file from the onboard website and the config
        if (!SPIFFS.begin()) {
                Serial.println("SPIFFS Mount Failed!");
                statusLed(blink_red);      //Blink red on fatal error and stop everything
                while(1);
        }

        //Loads the configuration from the file system and sets parameter
        if (!loadConfiguration()) {
                Serial.println("Error Loading Configuration");
                statusLed(blink_red);    //Blink red on fatal error and stop everything
                while(1);
        }

        //Print out the current APP- and Spiffs-Version
        Serial.printf("APP Version: %s \nSPIFFS Version: %s\n\n", ota_set.app_version, ota_set.spiffs_version);

        //Execute selected app. Function in Apps.hpp
        exec_app(app_set.app_exec);
}

void loop() {
//Nothing happens in the Loop, main programm is in seperated processes
}