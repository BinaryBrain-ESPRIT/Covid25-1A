#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"

#define DEBUG

#define CE_PIN 9
#define CSN_PIN 10

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

byte address[][6] = {"pipe1", "pipe2"}; // Set addresses of the 2 pipes for read and write
RF24 radio(CE_PIN, CSN_PIN);
int joystick[9];    // Array holding state of buttons and joystick X- and Y-reading
int received_value; // Value retreived from the other side...

LiquidCrystal_I2C lcd(0x27, 16, 2);
int a = 0;

void setup()
{

  pinMode(LedR, OUTPUT);
  pinMode(LedB, OUTPUT);

  for (int i = 0; i < 7; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
    digitalWrite(buttons[i], HIGH);
  }

#ifdef DEBUG
  Serial.begin(115200);
#endif

  // Setup nRF240...
  radio.begin();
  radio.openWritingPipe(address[0]);    // Open writing pipe to address pipe 1
  radio.openReadingPipe(1, address[1]); // Open reading pipe from address pipe 2
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN); // Set RF power output to minimum: RF24_PA_MIN (change to RF24_PA_MAX if required)
  radio.setRetries(3, 5);        // delay, count
  radio.setChannel(110);         // Set frequency to channel 110

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

  //-----------------------

  // Interact Button With LCD
  if (!joystick[0] && a != 1)
  {
    lcd.init();
    lcd.setCursor(3, 0);
    lcd.print("Interact !");
    a = 1;
  }
  else if (!joystick[1] && a != 2)
  {
    lcd.init();
    lcd.setCursor(4, 0);
    lcd.print("Return ...");
    a = 2;
  }
  else if (!joystick[2] && a != 3)
  {
    lcd.init();
    lcd.setCursor(5, 0);
    lcd.print("Jump !");
    a = 3;
  }
  else if (!joystick[3] && a != 4)
  {
    lcd.init();
    lcd.setCursor(4, 0);
    lcd.print("Attack !");
    a = 4;
  }
  else if (!joystick[4] && a != 5)
  {
    lcd.init();
    lcd.setCursor(4, 0);
    lcd.print("Options !");
    a = 5;
  }
  else if (!joystick[5] && a != 6)
  {
    lcd.init();
    lcd.setCursor(3, 0);
    lcd.print("FullScreen");
    a = 6;
  }

  else if (joystick[7] > 400)
  {
    lcd.init();
    lcd.setCursor(6, 0);
    lcd.print("Right");
  }
  else if (joystick[7] < 200)
  {
    lcd.init();
    lcd.setCursor(6, 0);
    lcd.print("Left");
  }
  else if (joystick[8] > 400)
  {
    lcd.init();
    lcd.setCursor(7, 0);
    lcd.print("UP");
  }
  else if (joystick[8] < 200)
  {
    lcd.init();
    lcd.setCursor(6, 0);
    lcd.print("DOWN");
  }
  // Action While recieving Information from the serial
  if (Serial.available())
  {
    char byte = Serial.read();
    lcd.setCursor(1, 0);
    if (byte == '0')
    {
      lcd.init();
      lcd.print("Starting Game ...");
      digitalWrite(LedR, HIGH);
    }
    else if (byte == '1')
    {
      lcd.init();
      lcd.print("Closing Game ...");
    }
    else if (byte == '2')
    {
      lcd.init();
      lcd.print("Collision Right");
      digitalWrite(LedB, LOW);
      digitalWrite(LedR, HIGH);
    }
    else if (byte == '3')
    {
      lcd.init();
      lcd.print("Collision Left");
      digitalWrite(LedR, LOW);
      digitalWrite(LedB, HIGH);
    }
    else if (byte == '4')
    {
      lcd.init();
      lcd.print("Collision UP");
    }
    else if (byte == '5')
    {
      lcd.init();
      lcd.print("Collision DOWN");
    }
    else if (byte == '6')
    {
      lcd.init();
      lcd.print("You Win !");
      for (int i = 0; i < 10; i++)
      {
        digitalWrite(LedB, LOW);
        delay(100);
        digitalWrite(LedB, HIGH);
        delay(100);
      }
      digitalWrite(LedB, LOW);
    }
    else if (byte == '7')
    {
      lcd.init();
      lcd.print("You Loose !");
      for (int i = 0; i < 10; i++)
      {
        digitalWrite(LedR, LOW);
        delay(100);
        digitalWrite(LedR, HIGH);
        delay(100);
      }
      digitalWrite(LedR, LOW);
    }
    else if (byte == '8')
    {
      lcd.init();
      lcd.print("Ennemy Right");
      for (int i = 0; i < 5; i++)
      {
        digitalWrite(LedR, LOW);
        delay(500);
        digitalWrite(LedR, HIGH);
        delay(500);
      }
      digitalWrite(LedR, LOW);
    }
    else if (byte == '9')
    {
      lcd.init();
      lcd.print("Ennemy Left");
      for (int i = 0; i < 5; i++)
      {
        digitalWrite(LedB, LOW);
        delay(500);
        digitalWrite(LedB, HIGH);
        delay(500);
      }
      digitalWrite(LedB, LOW);
    }
    
  }

  //-----------------------------
  // Write out values array...
  radio.write(joystick, sizeof(joystick));
  delay(20);
#ifdef DEBUG
  // Log...
  // Display Actions Of Shield on the Serial
  
    for (int i = 0; i < 9; i++)
    {
    Serial.print(joystick[i]);
    if (i < 8)
      Serial.print(", ");
    }
    Serial.print("\n");
  

  /*
    char byte = Serial.read();
    if (byte == '2')
    {
      lcd.setCursor(0, 0);
      lcd.print("Collision LEFT");
      digitalWrite(LedB, LOW);
      digitalWrite(LedR, HIGH);
    }
    else if (byte == '1')
    {
      lcd.setCursor(0, 0);
      lcd.print("Collision RIGHT");
      digitalWrite(LedR, LOW);
      digitalWrite(LedB, HIGH);
    }
    else
    {
      digitalWrite(LedR, LOW);
      digitalWrite(LedB, LOW);
      lcd.init();
    }
  */

#endif

  radio.startListening();
  if (radio.available())
  { // Get remote transmission
    radio.read(&received_value, sizeof(received_value));
    Serial.print("received_value=");
    Serial.println(received_value);
    /*
      if (received_value > 10) {
      #ifdef DEBUG
      Serial.print("received_value=");
      Serial.println(received_value);
      #endif

      }*/
  }
  delay(20);
  radio.stopListening();
}
