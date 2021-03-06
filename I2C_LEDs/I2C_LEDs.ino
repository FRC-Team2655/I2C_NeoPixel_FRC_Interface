/*  OctoWS2811 BasicTest.ino - Basic RGB LED Test
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

  This test is useful for checking if your LED strips work, and which
  color config (WS2811_RGB, WS2811_GRB, etc) they require.
*/

#include <OctoWS2811.h>
#include <Wire.h>

const int ledsPerStrip = 100;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  Wire.begin(84);
  Wire.onReceive(receiveEvent);
  leds.begin();
  leds.show();
}

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF

int microsec = 10000 / leds.numPixels();
int lastLevel = 0;
int i2cdata = 71;
void loop() 
{
  writeLevelData(i2cdata);
}

void colorWipe(int color, int wait)
{
  for (int i=0; i < leds.numPixels(); i++) 
  {
    leds.setPixel(i, color);
    leds.show();
    delayMicroseconds(wait);
  }
}

void drawSection(int startPoint, int endPoint, int color, int wait){
  for (int i = startPoint; i < endPoint; i++) 
  {
    leds.setPixel(i, color);
    leds.show();
    delayMicroseconds(wait);
  }
  for (int j = (100 - startPoint); j > (100 - endPoint); j--) 
  {
    leds.setPixel(j, color);
    leds.show();
    delayMicroseconds(wait);
  }
}

void wipeLast()
{
  switch(lastLevel)
  {
  case 70:
    break;
  case 71:
    drawSection(0, 9, BLUE, microsec);
    break;
  case 72:
    drawSection(10, 19, BLUE, microsec);
    break;
  case 73:
    drawSection(20, 29, BLUE, microsec);
    break;
  case 74:
    drawSection(30, 39, BLUE, microsec);
    break;
  case 75:
    drawSection(40, 49, BLUE, microsec);
    break;
  case 80:
    break;
  case 81:
    drawSection(0, 9, RED, microsec);
    break;
  case 82:
    drawSection(10, 19, RED, microsec);
    break;
  case 83:
    drawSection(20, 29, RED, microsec);
    break;
  case 84:
    drawSection(30, 39, RED, microsec);
    break;
  case 85:
    drawSection(40, 49, RED, microsec);
    break;
  default:
    break;
  }
}

void receiveEvent(int howMany)
{
  i2cdata = Wire.read();
}

void writeLevelData(int data)
{
  switch(data)
  {
    case 70:
      colorWipe(BLUE, microsec);
      lastLevel = 70;
      break;
    case 71:
      wipeLast();
      drawSection(0, 9, RED, microsec);
      lastLevel = 71;
      break;
    case 72:
      wipeLast();
      drawSection(10, 19, RED, microsec);
      lastLevel = 72;
      break;
    case 73:
      wipeLast();
      drawSection(20, 29, RED, microsec);
      lastLevel = 73;
      break;
    case 74:
      wipeLast();
      drawSection(30, 39, RED, microsec);
      lastLevel = 74;
      break;
    case 75:
      wipeLast();
      drawSection(40, 49, RED, microsec);
      lastLevel = 75;
      break;
    case 80:
      colorWipe(RED, microsec);
      lastLevel = 80;
      break;
    case 81:
      wipeLast();
      drawSection(0, 9, BLUE, microsec);
      lastLevel = 81;
      break;
    case 82:
      wipeLast();
      drawSection(10, 19, BLUE, microsec);
      lastLevel = 82;
      break;
    case 83:
      wipeLast();
      drawSection(20, 29, BLUE, microsec);
      lastLevel = 83;
      break;
    case 84:
      wipeLast();
      drawSection(30, 39, BLUE, microsec);
      lastLevel = 84;
      break;
    case 85:
      wipeLast();
      drawSection(40, 49, BLUE, microsec);
      lastLevel = 85;
      break;
    default:
      break;
  }
}

