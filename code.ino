#include <Wire.h>
#include <TEA5767Radio.h>
#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
 
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); 
TEA5767Radio radio = TEA5767Radio();
int analogPin = A0; // Pin connected to the analog input
int analogValue = 0; // Variable to store the analog value
float mappedValue = 0.; // Variable to store the mapped value

void setup() {
  Wire.begin();
  u8g2.begin();
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  analogValue = analogRead(analogPin); // Read the analog input
  // Map the analog value (0-1023) to the desired range (e.g., 0.0 to 5.0)
  float rawMappedValue = map(analogValue, 0, 1023, 900, 1000) / 10.;
  // Round the value to the nearest 0.5 increment
  mappedValue = round(rawMappedValue*10)/10.;
   radio.setFrequency(mappedValue);
  // Print the mapped value
  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print(" -> Mapped Value: ");
  Serial.println(mappedValue);
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_lubB08_tf );
  u8g2.setCursor(70, 25);
  u8g2.print("FM RADIO");
  u8g2.setFont(u8g2_font_fub35_tn);
  u8g2.setCursor(30, 64);
  u8g2.print(mappedValue);
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(10); 

}
