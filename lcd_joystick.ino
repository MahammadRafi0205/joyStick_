#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); 
#define Xvalue A0
#define Yvalue A1
int Xval, Yval;
void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.clear(); 
}
void loop() {
  Xval = analogRead(Xvalue);
  Yval = analogRead(Yvalue);
  if (Xval < 100 || Xval > 780 || Yval < 100 || Yval > 780) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wiring issue...!");
      lcd.setCursor(0, 1);
      lcd.print("Please Check");
      lcd.setCursor(0, 2);
      lcd.print("Connections ");
      delay(10000);
    }
    lcd.setCursor(0, 0);
    lcd.print("Joystick Status");
     int X = map(Xval,254,767,-50,50);
     int Y = map(Yval,256,769,-50,50);
    
    if (X > -4 && X < 2) X = 0;
    if (Y > -3 && Y < 2) Y = 0;
    lcd.setCursor(0, 1);
    lcd.print("X: ");
    lcd.print(X);
    lcd.print("       ");
    lcd.setCursor(10, 1);
    lcd.print("Y: ");
    lcd.print(Y);
    lcd.print("      ");
    lcd.setCursor(0, 2);
    if (Xval > 520)
      lcd.print("Dir: Right ");
    else if (Xval < 480)
      lcd.print("Dir: Left  ");
    else if (Yval > 520)
      lcd.print("Dir: Up    ");
    else if (Yval < 480)
      lcd.print("Dir: Down  ");
    else
      lcd.print("Dir: Center");
    delay(300);
}

