# Mood-Lamp
Brighten up your room with your own Arduino Mood Lamp! :smile:
* Switch between different moods/colors 
* Adjust brightness 
* Get temperature-based colors 
* Have the light sync with the environment

### Parts needed:
* Arduino UNO
* [Neopixel Ring - 16 x 5050 RGB LED with integrated drivers](https://www.adafruit.com/product/1463)
* [LCD Shield Kit w/ 16x2 Character Display - BLUE AND WHITE](https://www.adafruit.com/product/772)
* [Electret Microphone Amplifier-MAX4466 with Adjustable Gain](https://www.adafruit.com/products/1063)
* Temperature Sensor
* 1000µF capacitor (can use 6.3V or higher capacitor)
* 430 Ohm (can use 300-500 Ohm resistor)
* 5V DC Battery
* 9 jumper wires
* Soldering kit
* One-sided copper-clad Perfboard (can use two sided perfboard) 

### Libraries used:
To install these libraries, on your Arduino IDE, go to Sketch > Include Library > Manage LIbraries... then search for the libraries below (other libraries will be included with them)
* Adafruit_NeoPixel.h (*for Neopixel*)
* Adafruit_RGBLCDShield.h (*for I2C LCD*)

### Assemble Parts:
__Test each part as you successfully attach them so you know they work!!__
1. To assemble the LCD Shield Kit, follow [Lady Ada's guide for assembling the kit](https://learn.adafruit.com/rgb-lcd-shield/assembly).
2. Before assembling the Neopixel, read [this guide](https://learn.adafruit.com/adafruit-neopixel-uberguide/basic-connections) so you'll understand what not to do and why we need the 300-500 Ohm resistor and 1000µF capacitor. 
3. To assemble the Neopixel, you'll need **3 wires**, **1000µF capacitor** and **430 Ohm resistor**. Solder the wires from the back of the Neopixels (because space is limited between pixels in the front) relative to the markings in the front, G(Ground) and V+(5V). 
4. For IN(Data In), solder the 430 Ohm resistor to it, and the wire to the other end of the resistor. Use nail polish to coat where you connected the resistor and wire which acts as an insulator. 
5. Solder the 1000µF capacitor from an available G(ground) to V+(5V). Your Neopixel should look something like this: ![Alt text](https://github.com/jurddle/Mood-Lamp/blob/master/images/neopixel.jpg)
6. Solder **2 wires** to GND and 5V on the I2C shield, strip the unsoldered ends and insert them onto the perfboard(you can insert them to the middle of the board). __Don't solder them yet as they will be soldered with the Neopixel's GND and 5V.__ 
7. Strip the wire ends for the Neopixel and solder the GND and 5V wire along the same column as the Arduino's GND and 5V. __Make sure to leave enough space for the temperature sensor and other wires. If not the wires for the Arduino's GND/5V are not long enough to touch the Neopixel's GND/5V, then solder in a small lead rod to connect the two.__
8. After you connected the Neopixel's GND and 5V, solder the other wire (which should be Data In) onto **Digital Pin 6** on the I2C shield. 
9. For the Electret Microphone, strip and solder **3 wires** to its marked area. Solder the GND near the Arduino's GND on the perfboard; make sure they connect. Solder the OUT wire to **Analog Pin 1** and the VCC wire to **3.3V** on the I2C shield.
10. Lastly, you'll have to solder the temperature sensor; make sure you solder the correct ends of the sensor to GND and 5V; use [this](https://learn.adafruit.com/tmp36-temperature-sensor).
11. Strip **1 wire** end and solder it to the Analog Out (middle pin) of the sensor and solder the end to **Analog Pin 2** on the I2C shield.

Download the code, and if you've tested each part, then everything should work. Here is the schematic for how it should look: ![Alt text](https://github.com/jurddle/Mood-Lamp/blob/master/images/breadboard.jpg)
