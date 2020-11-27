#include <Arduino.h>
#include "ArduinoJson.h"
#include "LittleFS.h"

#include "WiFiManager.h"
#include "webServer.h"
#include "updater.h"
#include "fetch.h"
#include "configManager.h"
#include "timeSync.h"
#include "dashboard.h"

struct task
{    
    unsigned long rate;
    unsigned long previous;
};

task taskA = { .rate = 5, .previous = 0 };
bool setupRan = true;

void setup()
{
    Serial.begin(115200);

    LittleFS.begin();
    GUI.begin();
    configManager.begin();
    WiFiManager.begin(configManager.data.projectName);
    timeSync.begin();

    // try to get new firmware/configuration update and push current configuration
    if(configManager.data.setupRan) {
        String JSON;
        serializeJson(configManager.data, JSON);

        fetch.begin(std::format("https://{}/firmware", configManager.data.backendUrl));
        fetch.POST(JSON);

        // process answer
    }
    
}

void loop()
{
    if(configManager.data.setupRan) {
        // do stuff
    } else {
        WiFiManager.loop();
        updater.loop();
        dash.loop();
    }





    if (taskA.previous == 0 || (millis() - taskA.previous > taskA.rate))
    {
        taskA.previous = millis();

        uint16_t val = analogRead(A0);
        //Serial.println(val);
        dash.data.mariosNummer = val;
    }
}
