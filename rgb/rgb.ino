const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN=  11;
const int LED_PIN = 13;

int DISPLAY_TIME = 100;

void setup() {
	Serial.begin(9600);
	pinMode(RED_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);
	pinMode(BLUE_PIN, OUTPUT);
	pinMode(LED_PIN, OUTPUT);
}

void loop() {
	if (Serial.available() > 0) {
		int value = serialReadInt();
		if (value == -1) {
			digitalWrite(LED_PIN, LOW);
		} else {
			digitalWrite(LED_PIN, HIGH);
		}
		Serial.println(value);
		showRGB(value);
	}
	/* delay(1000); */
}

int serialReadInt() {
	unsigned char MSB = 0; // 1 byte in arduino
	unsigned char LSB = 0; // 1 byte in arduino
	unsigned int MSBLSB = 0; // 2 bytes in arduino

	if (Serial.available() >= 2) {
		MSB = Serial.read();
		LSB = Serial.read();
		MSBLSB = word(MSB, LSB);
	}

	return MSBLSB;
}

void showRGB(int color) {
	int redIntensity;
	int greenIntensity;
	int blueIntensity;

	if (color <= 255) {
		redIntensity = 255 - color;
		greenIntensity = color;
		blueIntensity = 0;
	} else if (color <= 511) {
		redIntensity = 0;
		greenIntensity = 255 - (color - 256);
		blueIntensity = (color - 256);
	} else {
		redIntensity = (color - 512);
		greenIntensity = 0;
		blueIntensity = 255 - (color - 512);
	}

	analogWrite(RED_PIN, redIntensity);
	analogWrite(BLUE_PIN, blueIntensity);
	analogWrite(GREEN_PIN, greenIntensity);
}
