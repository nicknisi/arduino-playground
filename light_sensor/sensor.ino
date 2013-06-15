int ledPins[] = {2,3,4,5,6,7,8,9};
int sensorPin = 0;
int lightLevel, high = 0, low = 1023;

void setup() {
    int index;

    // set all pins to output for the LEDs
    for (index = 0; index <= 7; ++index) {
        pinMode(ledPins[index], OUTPUT);
    }
}

void loop() {
    detectLights();
}

void detectLights() {
    int i;
    lightLevel = analogRead(sensorPin);
    autoTune();
    lightLevel = map(lightLevel, 0, 255, 0, 7);
    clearLights();
    for (i = 0; i <= lightLevel; ++i) {
        digitalWrite(ledPins[i], HIGH);
    }
}

void clearLights() {
    int i;

    for (i = 0; i < 8; ++i) {
        digitalWrite(ledPins[i], LOW);
    }
}

void autoTune() {
    if (lightLevel < low)
    {
        low = lightLevel;
    }


    if (lightLevel > high)
    {
        high = lightLevel;
    }

    lightLevel = map(lightLevel, low+30, high-30, 0, 255);
    lightLevel = constrain(lightLevel, 0, 255);
}
