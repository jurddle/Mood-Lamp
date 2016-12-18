#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6 // pin Neopixels are connected to on Arduino
#define NUMPIXELS 16 // Number of Neopixels
#define NOISE 50 // Noise/hum/interference in mic signal

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

uint8_t i = 0;
uint16_t start = 125; // default brightness
const int 
  temp_pin = 2, // digital pin for temperature
  mic_pin = 1; // analog pin for microphone
float 
  reading, // reading for temperature sensor
  temperature;
int frequency; 
char* menu[] = { "Red             ", "Blue            ", "Green           ", "Yellow          ",
                 "Orange          ", "Purple          ", "White           ", "Temperature     ",
                 "Party           ", "Rainbow         " };

void setup(){
  // Debugging start output
  Serial.begin(9600); 
  Serial.println("Start setup");
  //Initialize a 2x16 type LCD
  lcd.begin(16,2);  
  lcd.setCursor(0,0);
  lcd.print("Choose an option");
  pixels.begin(); // Initialize the NeoPixel library
  // Debugging end output
  Serial.println("End setup");
  delay(1000);
}

void loop(){
  //menuDisplay();
   uint8_t button = lcd.readButtons();
  lcd.setCursor(0,1);
  lcd.print(menu[i]);
  switch(button){
    case BUTTON_UP: // 8
      // if press UP and at start of menu, loop to end of menu
      lcd.setCursor(0,1);
      if(i == 0){
        i = 9;
        lcd.print(menu[i]);
      }else{
        i--;
        lcd.print(menu[i]);
      }
      break;
        
    case BUTTON_DOWN: // 4
      // if press DOWN and at end of menu, loop to start of menu
      lcd.setCursor(0,1);
      if(i == 9){
        i = 0;
        lcd.print(menu[i]);
      }else{
        i++;
        lcd.print(menu[i]);
      }
      break;
        
    case BUTTON_SELECT: // 1
      // Red
      if(i == 0){
        for(uint16_t i = 0; i < NUMPIXELS; ++i){
          pixels.setPixelColor(i, pixels.Color(125,0,0)); 
          pixels.show();
        }
      }
      
      // Blue
      if(i == 1){
        for(uint16_t i = 0; i < NUMPIXELS; ++i){
          pixels.setPixelColor(i, pixels.Color(0,0,125)); 
          pixels.show();
        }
      }
      
      // Green
      if(i == 2){
        for(uint16_t i = 0; i < NUMPIXELS; ++i){
          pixels.setPixelColor(i, pixels.Color(0,125,0)); 
          pixels.show();
        }
      }
      
      // Yellow
      if(i == 3){
        for(uint16_t i = 0; i < NUMPIXELS; ++i){
          pixels.setPixelColor(i, pixels.Color(125,100,0)); 
          pixels.show();
        }
      }
      
      // Orange
      if(i == 4){
        for(uint16_t i = 0; i < NUMPIXELS; ++i){
          pixels.setPixelColor(i, pixels.Color(125,20,0)); 
          pixels.show();
        }
      }
      
      // Purple
      if(i == 5){
        for(uint16_t i = 0; i < NUMPIXELS; ++i){
          pixels.setPixelColor(i, pixels.Color(125,0,125)); 
          pixels.show();
        }
      }
      
      // White
      if(i == 6){
        for(uint16_t i = 0; i < NUMPIXELS; ++i){
          pixels.setPixelColor(i, pixels.Color(100,100,100)); 
          pixels.show();
        }
      }
      
      // Temperature
      if(i == 7){
        while(!(lcd.readButtons() == 4 || lcd.readButtons() == 8)){
          reading = analogRead(temp_pin);
          float voltage = (reading * 5.0) / 1024.0;
          temperature = (voltage - 0.5) * 100; // convert to in Celcius
          // temperature = (temperature * 9.0 / 5.0) + 32.0; // convert to Fahrenheit
          Serial.println(temperature);
          // if above 31 Celcius, red
          if(temperature > 31.0){
            for(uint16_t i = 0; i < NUMPIXELS; ++i){
              pixels.setBrightness(start);
              pixels.setPixelColor(i, pixels.Color(125,0,0)); 
              pixels.show();
            }
          }
          // if between 20 & 31 Celcius, orange
          else if(temperature < 31.0 && temperature > 20.0){
            for(uint16_t i = 0; i < NUMPIXELS; ++i){
              pixels.setBrightness(start);
              pixels.setPixelColor(i, pixels.Color(125,20,0)); 
              pixels.show();
            }
          }
          else{
            // if below 20 Celcius, blue
            for(uint16_t i = 0; i < NUMPIXELS; ++i){
              pixels.setBrightness(start);
              pixels.setPixelColor(i, pixels.Color(0,0,125)); 
              pixels.show();
            }
          }
        }
        delay(500);
      }
      
      // Party
      if(i == 8){
        while(!(lcd.readButtons() == 4 || lcd.readButtons() == 8)){
          frequency = analogRead(mic_pin); // Raw reading from mic 
          float voltage = frequency * (5.0 / 1023.0);
          Serial.println(voltage);
          if(voltage > 1.74){
            for(uint16_t i = 0; i < NUMPIXELS; ++i){
              pixels.setPixelColor(i,0,0,0);
              pixels.show();
            }
          }
          else{
            uint32_t color = Random();
            for(uint16_t i = 0; i < NUMPIXELS; ++i){
              pixels.setBrightness(start);
              pixels.setPixelColor(i, color);
              pixels.show();
            }
          }
        }
      }

      // Rainbow
      if(i == 9){
        while(!(lcd.readButtons() == 4 || lcd.readButtons() == 8)){
          for(uint16_t i = 0; i < 256; ++i){
            for(uint16_t j = 0; j < NUMPIXELS; ++j){
              pixels.setBrightness(start);
              pixels.setPixelColor(j, Wheel((j * 256 / NUMPIXELS + i) & 255));
            }
            pixels.show();
            delay(1);
          }
        }
      }

    case BUTTON_LEFT: // 16
      start = start-20;
      if(start < 6){
        start += 20; 
        break;
      }
      else{
        pixels.setBrightness(start);
        delay(50);
        pixels.show();
        break;
      }

    case BUTTON_RIGHT: // 2
      start = start+20;
      if(start > 245){
        start -= 20;
        break;
      }
      else{
        pixels.setBrightness(start);
        delay(50);
        pixels.show();
        break;
      }
  }
  delay(50);
}

uint32_t Random(){
  return pixels.Color(random(255),random(255),random(255));
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos){
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85){
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170){
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

