#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define Xvalue A0
#define Yvalue A1
int Xval, Yval;
void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { 
    Serial.println(F("SSD1306 init failed"));
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);      
  pinMode(Xvalue, INPUT);
  pinMode(Yvalue, INPUT);
}
void loop() {
  Xval = analogRead(Xvalue);
  Yval = analogRead(Yvalue);
  if (Xval < 100 || Xval > 780 || Yval < 100 || Yval > 780) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Wiring Issue");
    display.display();
    delay(3000);  
  }
    int centerX = 64;
    int centerY = 32;
    int radius = 25;
    int dotX = map(Xval, 256, 768, -radius, radius);
    int dotY = map(Yval, 256, 766, radius, -radius);
    float distance = sqrt(dotX * dotX + dotY * dotY);
    if (distance > radius) {
      float scale = (float)radius / distance;
      dotX *= scale;
      dotY *= scale;
    }
     int X = map(Xval,256,767,-50,50);
     int Y = map(Yval,256,769,-50,50);
    display.clearDisplay();
    display.drawCircle(centerX, centerY, radius, SSD1306_WHITE);
    display.drawLine(centerX - radius, centerY, centerX + radius, centerY, SSD1306_WHITE);
    display.drawLine(centerX, centerY - radius, centerX, centerY + radius, SSD1306_WHITE);
    display.fillCircle(centerX + dotX, centerY + dotY, 2, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 56);
    if (Xval > 520){
      display.print("Right ");
    }
    else if (Xval < 480){
      display.print("Left ");
    }
    else if (Yval > 520){
      display.print("Up ");
    }
    else if (Yval < 480){
      display.print("Down ");
    }
    else{
      display.print("Center");
      display.setTextSize(1);
    }
    display.setCursor(0, 48);
    if (Xval > 520){
      display.print("X ");
      display.print(X);
    }
    else if (Xval < 480){
      display.print("X ");
      display.print(X);
    }
    else if (Yval > 520){
      display.print("Y ");
      display.print(Y);
    }
    else if (Yval < 480){
      display.print("Y ");
      display.print(Y);
    }
    display.display();
    delay(200);
  }

