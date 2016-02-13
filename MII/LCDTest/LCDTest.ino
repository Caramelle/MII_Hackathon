/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

// include the LCD library code:
#include <LiquidCrystal.h>
#define GREEN 8
#define BLUE 9
#define RED 10

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char inData[20]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // set up the serial connection.
  Serial.begin(9600);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
  // whenever a new value is sent
  int redVal = 255;
  int blueVal = 255;
  int greenVal = 255;

  analogWrite( GREEN, 255 - greenVal );
  analogWrite( RED, 255 - redVal );
  analogWrite( BLUE, 255 - blueVal );

  if (Serial.available()) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("AC System");
    delay(100);
    lcd.setCursor(0, 1);
    while (Serial.available() > 0) {
      if(index < 19) // One less than the size of the array
      {
          inChar = Serial.read(); // Read a character
          inData[index] = inChar; // Store it
          index++; // Increment where to write next
          inData[index] = '\0'; // Null terminate the string
      }
    }

    if (inData[0] == 'T') {
      lcd.print(strcpy(inData, inData + 1));
    }
    lcd.print(" Degrees C");
  }
}
