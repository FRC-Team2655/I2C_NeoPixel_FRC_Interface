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
#include <Wire.h>

const int ledsPerStrip = 83;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

int PlatypiColors[180];
int PulseRed[180];
int PulseBlue[180];
int j = 0;

void setup() {
  Wire.begin(84);
  Wire.onReceive(receiveEvent);
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  
  // Create Array for Loiter Pattern
  for (int i=0; i<45; i++) {
    j++;
    int hue = 280;
    int saturation = 100;
    int lightness = j + 5;
    // Pre-compute "45 degrees" of the Platypi Colors
    PlatypiColors[i] = makeColor(hue, saturation, lightness);
  }
  j = 0;
  for (int i=45; i<90; i++) {
    j++;
    int hue = 280;
    int saturation = 100;
    int lightness = 50 - j;
    // Pre-compute "45 degrees" of the Platypi Colors
    PlatypiColors[i] = makeColor(hue, saturation, lightness);
  }
  j = 0;
  for (int i=90; i<135; i++) {
    j++;
    int hue = 50;
    int saturation = 100;
    int lightness = j + 5;
    // Pre-compute "45 degrees" of the Platypi Colors
    PlatypiColors[i] = makeColor(hue, saturation, lightness);
  }
  j = 0;
  for (int i=135; i<180; i++) {
    j++;
    int hue = 50;
    int saturation = 100;
    int lightness = 50 - j;
    // Pre-compute "45 degrees" of the Platypi Colors
    PlatypiColors[i] = makeColor(hue, saturation, lightness);
  }
  
  j = 0;
  // Create Array for Loiter Pattern
  for (int i=0; i<45; i++) {
    j++;
    int hue = 360;
    int saturation = 100;
    int lightness = j + 5;
    // Pre-compute "45 degrees" of the Platypi Colors
    PulseRed[i] = makeColor(hue, saturation, lightness);
  }
  j = 0;
  for (int i=45; i<90; i++) {
    j++;
    int hue = 360;
    int saturation = 100;
    int lightness = 50 - j;
    // Pre-compute "45 degrees" of the Platypi Colors
    PulseRed[i] = makeColor(hue, saturation, lightness);
  }
  j = 0;
  for (int i=90; i<135; i++) {
    j++;
    int hue = 50;
    int saturation = 100;
    int lightness = j + 5;
    // Pre-compute "45 degrees" of the Platypi Colors
    PulseRed[i] = makeColor(hue, saturation, lightness);
  }
  j = 0;
  for (int i=135; i<180; i++) {
    j++;
    int hue = 50;
    int saturation = 100;
    int lightness = 50 - j;
    // Pre-compute "45 degrees" of the Platypi Colors
    PulseRed[i] = makeColor(hue, saturation, lightness);
  }
  
  j = 0;
  // Create Array for Loiter Pattern
  for (int i=0; i<45; i++) {
    j++;
    int hue = 240;
    int saturation = 100;
    int lightness = j + 5;
    // Pre-compute "45 degrees" of the Platypi Colors
    PulseBlue[i] = makeColor(hue, saturation, lightness);
  }
  j = 0;
  for (int i=45; i<90; i++) {
    j++;
    int hue = 240;
    int saturation = 100;
    int lightness = 50 - j;
    // Pre-compute "45 degrees" of the Platypi Colors
    PulseBlue[i] = makeColor(hue, saturation, lightness);
  }
  j = 0;
  for (int i=90; i<135; i++) {
    j++;
    int hue = 50;
    int saturation = 100;
    int lightness = j + 5;
    // Pre-compute "45 degrees" of the Platypi Colors
    PulseBlue[i] = makeColor(hue, saturation, lightness);
  }
  j = 0;
  for (int i=135; i<180; i++) {
    j++;
    int hue = 50;
    int saturation = 100;
    int lightness = 50 - j;
    // Pre-compute "45 degrees" of the Platypi Colors
    PulseBlue[i] = makeColor(hue, saturation, lightness);
  }
  
  digitalWrite(1, LOW);
  leds.begin();
}

int i2clight = 72;
int* LEDData;

void loop() 
{
  rainbow(20, 1800, LEDData);
}


// phaseShift is the shift between each row.  phaseShift=0
// causes all rows to show the same colors moving together.
// phaseShift=180 causes each row to be the opposite colors
// as the previous.
//
// cycleTime is the number of milliseconds to shift through
// the entire 360 degrees of the color wheel:
// Red -> Orange -> Yellow -> Green -> Blue -> Violet -> Red


// This function writes the pre-generated pattern to the LEDs
void rainbow(int phaseShift, int cycleTime, int data[180])
{
  int color, x, y, offset, wait;

  wait = cycleTime * 1000 / ledsPerStrip;
  for (color=0; color < 180; color++) {
    digitalWrite(1, HIGH);
    for (x=0; x < ledsPerStrip; x++) {
      for (y=0; y < 8; y++) {
        int index = (color + x + y*phaseShift/2) % 180;
        leds.setPixel(x + y*ledsPerStrip, data[index]);
      }
    }
    leds.show();
    digitalWrite(1, LOW);
    delayMicroseconds(wait);
  }
}

void receiveEvent(int data)
{
  while (Wire.available())
  {
    i2clight = Wire.read();
    if (i2clight == 72)
    {
      LEDData = PlatypiColors;
    }
    else if (i2clight == 74)
    {
      LEDData = PulseRed;
    }
    else if (i2clight == 76)
    {
      LEDData = PulseBlue;
    }
  }
}
