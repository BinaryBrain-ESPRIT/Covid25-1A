#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LedR 16
#define LedB 17

#define button_A 2        // Button Blue - A
#define button_B 3        // Button Yellow - B
#define button_C 4        // Button Blue - C
#define button_D 5        // Button Yellow - D
#define button_E 7        // SMD button E on pcb
#define button_F 6        // SMD button F on pcb
#define button_joystick 8 // Button in joystick
#define x_axis A0
#define y_axis A1

int buttons[] = {button_A, button_B, button_C, button_D, button_E, button_F, button_joystick};
int a = 0;
byte address[][6] = {"pipe1", "pipe2"}; // Set addresses of the 2 pipes for read and write
int joystick[9];    // Array holding state of buttons and joystick X- and Y-reading
int received_value; // Value retreived from the other side...

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  // put your setup code here, to run once:
  pinMode(LedR, OUTPUT);
  pinMode(LedB, OUTPUT);

  for (int i = 0; i < 7; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
    digitalWrite(buttons[i], HIGH);
  }

  Serial.begin(9600);

  // LCD
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
}

void loop() {
  // Read digital buttons...
  for (int i = 0; i < 7; i++)
    joystick[i] = digitalRead(buttons[i]);

  // Read joystick values...
  joystick[7] = analogRead(x_axis);
  joystick[8] = analogRead(y_axis);

  if (!joystick[0] && a != 1)
  {
    lcd.setCursor(2, 0);
    lcd.print("Button a");
    a = 1;
  }
  if (!joystick[1] && a != 2)
  {
    lcd.setCursor(2, 0);
    lcd.print("Button b");
    a = 2;
  }
  if (!joystick[2] && a != 3)
  {
    lcd.init();
    a = 2;
  }

  for (int i = 0; i < 9; i++)
  {
    Serial.print(joystick[i]);
    if (i < 8)
      Serial.print(", ");
  }
  Serial.print("\n");


  if (Serial.available())
  {
    char byte = Serial.read();
    lcd.setCursor(2, 0);
    if (byte == '1')
      lcd.print("1");
     else if (byte == '2')
      lcd.print("2");
    Serial.println("2");
    /*
    if (byte == '2')
    {
      lcd.setCursor(0, 0);
      lcd.print("Collision LEFT");
      digitalWrite(LedB, LOW);
      digitalWrite(LedR, HIGH);
      Serial.println("2");
    }
    else if (byte == '1')
    {
      lcd.setCursor(0, 0);
      lcd.print("Collision RIGHT");
      digitalWrite(LedR, LOW);
      digitalWrite(LedB, HIGH);
      Serial.println("1");
    }
    else if (byte == '0')
    {
      digitalWrite(LedR, LOW);
      digitalWrite(LedB, LOW);
      lcd.init();
      Serial.println("0");
    }
    */
  }



}
