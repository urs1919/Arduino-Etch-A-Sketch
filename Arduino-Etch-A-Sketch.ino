#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 

const int potXPin = A0;
const int potYPin = A2;
int potX = 0;
int potY = 0;

int screenX = 0;
int screenY = 0;
int previousPositionX = 0;
int previousPositionY = 0;

const int clearScreenPin = 7;
int buttonState;


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

  display.clearDisplay();
  display.display();

  pinMode(clearScreenPin, INPUT_PULLUP);
  
  potX = analogRead(potXPin);
  potY = analogRead(potYPin);
  previousPositionX = map(potX, 0, 1024, 0, 128);
  previousPositionY = map(potY, 0, 1024, 0, 64);
}

void loop() {
  clearScreen();
  movement();
  
  display.display();
  delay(10);
}

inline void draw(int x, int y, int prevX, int prevY) {
  display.drawLine(prevX, prevY, x, y, SSD1306_WHITE);
}

void movement() {
  potX = analogRead(potXPin);
  potY = analogRead(potYPin);

  screenX = map(potX, 0, 1024, 0, 128);
  screenY = map(potY, 0, 1024, 0, 64);

  draw(screenX, screenY, previousPositionX, previousPositionY);

  previousPositionX = screenX;
  previousPositionY = screenY;
}

void clearScreen() {
  buttonState = digitalRead(clearScreenPin);
  if(buttonState == 0) {
    display.clearDisplay();
    display.display();
  }
}
