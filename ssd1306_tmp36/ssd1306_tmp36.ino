#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
#define BAUD 9600
#define SENSOR_PIN A3
#define VCC 5.0
#define ADC_MAX 1024.0
#define SAMPLE_DELAY 2500

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(BAUD);

  // Initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  init_anim();
  delay(800);
  display.clearDisplay();
}

void init_anim() {
  // Initialization with animation
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  String text1 = "Temperature Monitor";
  String baseText = "Initializing";

  int16_t x1, y1;
  uint16_t w1, h1, w2, h2;

  display.getTextBounds(text1, 0, 0, &x1, &y1, &w1, &h1);
  display.setCursor((SCREEN_WIDTH - w1) / 2, (SCREEN_HEIGHT / 2) - 10);
  display.println(text1);
  display.display();

  for (int dots = 1; dots <= 3; dots++) {
    String animatedText = baseText;
    for (int i = 0; i < dots; i++) {
      animatedText += ".";
    }

    display.fillRect(0, (SCREEN_HEIGHT / 2) + 2, SCREEN_WIDTH, 10, SSD1306_BLACK);
    display.getTextBounds(animatedText, 0, 0, &x1, &y1, &w2, &h2);
    display.setCursor((SCREEN_WIDTH - w2) / 2, (SCREEN_HEIGHT / 2) + 2);
    display.println(animatedText);
    display.display();
    delay(600);
  }
}

void loop() {
  int input = analogRead(SENSOR_PIN);
  float voltage = input * (VCC / ADC_MAX);
  float temp = (voltage - 0.5) * 100;

  Serial.print("Raw ADC: ");
  Serial.print(input);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 2);
  Serial.print("V | Temperature: ");
  Serial.print(temp, 1);
  Serial.println("°C");

  draw(temp);
  delay(SAMPLE_DELAY);
}

void draw(float t) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor((SCREEN_HEIGHT / 2.0), (SCREEN_WIDTH / 2.0));

  String tempLabel = "Temperature:";
  String tempValue = String(t, 1) + " C";

  int16_t x1, y1;
  uint16_t w1, h1, w2, h2;

  display.setTextSize(1);
  display.getTextBounds(tempLabel, 0, 0, &x1, &y1, &w1, &h1);
  display.setCursor((SCREEN_WIDTH - w1) / 2, 15);
  display.println(tempLabel);
  display.display();

  display.setTextSize(2);
  display.getTextBounds(tempValue, 0, 0, &x1, &y1, &w2, &h2);
  display.setCursor((SCREEN_WIDTH - w2) / 2, (SCREEN_HEIGHT / 2) - (h2 / 2));
  display.println(tempValue);

  display.display();
}