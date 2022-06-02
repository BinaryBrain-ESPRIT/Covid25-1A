#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LedR 16
#define LedB 17

#define button_A 2        // Button Blue - A
#define button_B 3        // Button Yellow - B
#define button_C 4        // Button Blue - C
#define button_D 5        // Button Yellow - D
#define button_E 6        // SMD button E on pcb
#define button_F 7        // SMD button F on pcb
#define button_joystick 8 // Button in joystick
#define x_axis A0
#define y_axis A1

int buttons[] = {button_A, button_B, button_C, button_D, button_E, button_F, button_joystick};
int a = 0;
byte address[][6] = {"pipe1", "pipe2"}; // Set addresses of the 2 pipes for read and write
int joystick[9];                        // Array holding state of buttons and joystick X- and Y-reading
int received_value;                     // Value retreived from the other side...

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup()
{
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

void loop()
{
  // Read digital buttons...
  for (int i = 0; i < 7; i++)
    joystick[i] = digitalRead(buttons[i]);

  // Read joystick values...
  joystick[7] = analogRead(x_axis);
  joystick[8] = analogRead(y_axis);

  // Interact Button With LCD

  /*
  if (!joystick[0] && a != 1)
  {
    lcd.init();
    lcd.setCursor(3, 0);
    lcd.print("Interact !");
    a = 1;
  }
  if (!joystick[1] && a != 2)
  {
    lcd.init();
    lcd.setCursor(4, 0);
    lcd.print("Return ...");
    a = 2;
  }
  if (!joystick[2] && a != 3)
  {
    lcd.init();
    lcd.setCursor(5, 0);
    lcd.print("Jump !");
    a = 3;
  }
  if (!joystick[3] && a != 4)
  {
    lcd.init();
    lcd.setCursor(4, 0);
    lcd.print("Attack !");
    a = 4;
  }
  if (!joystick[4] && a != 5)
  {
    lcd.init();
    lcd.setCursor(4, 0);
    lcd.print("Options !");
    a = 5;
  }
  if (!joystick[5] && a != 6)
  {
    lcd.init();
    lcd.setCursor(3, 0);
    lcd.print("FullScreen");
    a = 6;
  }

  if (joystick[7] > 400)
  {
    lcd.init();
    lcd.setCursor(5, 0);
    lcd.print("Right");
  }
  else if (joystick[7] < 200)
  {
    lcd.init();
    lcd.setCursor(5, 0);
    lcd.print("Left");
  }
  if (joystick[8] > 400)
  {
    lcd.init();
    lcd.setCursor(5, 0);
    lcd.print("UP");
  }
  else if (joystick[8] < 200)
  {
    lcd.init();
    lcd.setCursor(5, 0);
    lcd.print("DOWN");
  }
*/
  // Display Actions Of Shield on the Serial
  for (int i = 0; i < 9; i++)
  {
    Serial.print(joystick[i]);
    if (i < 8)
      Serial.print(", ");
  }
  Serial.print("\n");

  // Action While recieving Information from the serial
  if (Serial.available())
  {
    char byte = Serial.read();
     if (byte == '2')
      digitalWrite(LedR,HIGH);
     else if (byte == '0')
      digitalWrite(LedR,LOW);
     /*
    
    lcd.init();
    lcd.setCursor(1, 0);
    if (byte == '2')
      lcd.print("Collision Right");
    else if (byte == '3')
      lcd.print("Collision Left");
    else if (byte == '4')
      lcd.print("Collision UP");
    else if (byte == '5')
      lcd.print("Collision DOWN");
    else if (byte == '6')
      lcd.print("You Win !");
    else if (byte == '7')
      lcd.print("You Loose !");
    else if (byte == '0')
      lcd.print("Starting Game ...");
    else if (byte == '1')  
      lcd.print("Closing Game ...");
  
   // delay(2000);

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
