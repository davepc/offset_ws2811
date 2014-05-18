/*  OctoWS2811 Rainbow.ino - Rainbow Shifting Test
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
    Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.


  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.
    pin 1 - Output indicating CPU usage, monitor with an oscilloscope,
            logic analyzer or even an LED (brighter = CPU busier)
*/

#include <OctoWS2811.h>

#define RED    0x0F0000
#define GREEN  0x000F00
#define BLUE   0x00000F
#define BLACK  0x000000
#define WHITE  0xFFFFE0
#define switching_delay 25000

const int ledsPerStrip = 40;
const int strips = 4;
const int nLeds = ledsPerStrip * strips;
const int LPS = ledsPerStrip;


static unsigned long switching_time;

const int lightness = 50;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_RGB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

int rainbowColors[180];

int mode = 0;
int timet = millis();


void setup() {
  Serial.begin(9600);
  pinMode(1, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(1, HIGH);
  for (int i=0; i<180; i++){
    int hue = i * 2;
    int saturation = 100;
    int lightness = 50;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, 30);
  }
  digitalWrite(1, LOW);
  leds.begin();
  switching_time = millis();  // initial setup
}

int ind = 0;

void loop() {
  keyboard();
  ind = (ind == 0) ? 1 : 0;
  digitalWrite(13, ind);
    set_all(0xFFFFFF);
    leds.show();
    dm(1000);

    /*int wait = 3000;
    set_all(RED);
    dm(wait);
    set_all(BLUE);
    dm(wait);
    set_all(GREEN);
    dm(wait);
    */
}


static int c_mode = 1;
int posible_modes[] = {1, 2, 3, 4, 11, 12, 13, 14};
int rotate_random(){
    if ((long)( millis() - switching_time ) >= 0) {
        switching_time += switching_delay;  
        c_mode = posible_modes[random(8)];
    }
    return c_mode;
}


// phaseShift is the shift between each row.  phaseShift=0
// causes all rows to show the same colors moving together.
// phaseShift=180 causes each row to be the opposite colors
// as the previous.
//
// cycleTime is the number of milliseconds to shift through
// the entire 360 degrees of the color wheel:
// Red -> Orange -> Yellow -> Green -> Blue -> Violet -> Red
//
//

int rainbow_mode_color = 0;
void rainbow(int phaseShift, int cycleTime) {
  int x, y, offset, wait;
  int color = rainbow_mode_color;
  wait = cycleTime * 1000 / ledsPerStrip;
 // for (color=0; color < 180; color++) {
    digitalWrite(1, HIGH);
    for (x=0; x < ledsPerStrip; x++) {
      for (y=0; y < 8; y++) {
        int index = (color + x + y*phaseShift/2) % 180;
        leds.setPixel(x + y*ledsPerStrip, rainbowColors[index]);
      }
    }
    leds.show();
    digitalWrite(1, LOW);
    delayMicroseconds(100000);
    rainbow_mode_color++;
    if (rainbow_mode_color > 180)
      rainbow_mode_color = 0;
  
}
