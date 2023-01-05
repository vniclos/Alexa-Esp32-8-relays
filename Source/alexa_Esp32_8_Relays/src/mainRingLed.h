#ifndef MAINRINGLED_H
#define MAINRINGLED_H
#include "mainDefines.h"
#include <Adafruit_NeoPixel.h>






void fncLedsRingIdleChristmas() {
    uint16_t newR, newG, newB, startR, startG, startB, endR, endG, endB;
    uint32_t color = fncLedsRingwheelColor(g_RingLedFadeColor, g_RingLedLampBrightness);
    endR = (uint16_t)((color >> 16) & 0xff); // Splits out new color into separate R, G, B
    endG = (uint16_t)((color >> 8) & 0xff);
    endB = (uint16_t)(color & 0xff);
    for (uint16_t j = 0; j < g_RingLedActivePixels; j++) {
        long startRGB = g_LedsRing.getPixelColor(j); // Get pixel's current color
        startR = (uint16_t)((startRGB >> 16) & 0xff); // Splits out current color into separate R, G, B
        startG = (uint16_t)((startRGB >> 8) & 0xff);
        startB = (uint16_t)(startRGB & 0xff);
        if ( startR > endR ) {
            newR = startR - 1;
        } else if ( startR < endR ) {
            newR = startR + 1;
        } else {
            newR = endR;
        }
        if ( startG > endG ) {
            newG = startG - 1;
        } else if ( startG < endG ) {
            newG = startG + 1;
        } else {
            newG = endG;
        }
        if ( startB > endB ) {
            newB = startB - 1;
        } else if ( startB < endB ) {
            newB = startB + 1;
        } else {
            newB = endB;
        }
        
        //Catch overflows
        newR %= 255;
        newG %= 255;
        newB %= 255;
        
        //newR = startR + (endR - startR) * fade / 255;// / strip.numPixels();// Color mixer
        //newG = startG + (endG - startG) * fade / 255;// / strip.numPixels();
        //newB = startB + (endB - startB) * fade / 255;// / strip.numPixels();
        g_LedsRing.setPixelColor(j, newR, newG, newB);
        if ( j >= g_LedsRing.numPixels() - 1 && endR == startR && endG == startG && endB == startB) {
            if ( g_RingLedFadeColor == 0 ) {
                g_RingLedFadeColor = 85;
            } else {
                g_RingLedFadeColor = 0;
            }
            g_RingLedActivePixels = 0;
        }
    }
    g_LedsRing.show();
    if ( g_RingLedActivePixels < g_LedsRing.numPixels() ) g_RingLedActivePixels++;
}

uint32_t fncLedsRingwheelColor(uint16_t WheelPos, uint16_t iBrightness) {
	float R, G, B;
	float brightness = iBrightness / 255.0;

	if (WheelPos < 85) {
		R = WheelPos * 3;
		G = 255 - WheelPos * 3;
		B = 0;
	} else if (WheelPos < 170) {
		WheelPos -= 85;
		R = 255 - WheelPos * 3;
		G = 0;
		B = WheelPos * 3;
	} else {
		WheelPos -= 170;
		R = 0;
		G = WheelPos * 3;
		B = 255 - WheelPos * 3;
	}
	g_RingLedActiveR = R * brightness;// + .5;
	g_RingLedActiveG = G * brightness;// + .5;
	g_RingLedActiveB = B * brightness;// + .5;
	return g_LedsRing.Color((byte) g_RingLedActiveR,(byte) g_RingLedActiveG,(byte) g_RingLedActiveB);
}

void fncLedsRingColorFade(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  for(uint16_t i = 0; i < g_LedsRing.numPixels(); i++) {
      uint8_t startR, startG, startB;
      uint32_t startColor = g_LedsRing.getPixelColor(i); // get the current colour
      startB = startColor & 0xFF;
      startG = (startColor >> 8) & 0xFF;
      startR = (startColor >> 16) & 0xFF;  // separate into RGB components

      if ((startR != r) || (startG != g) || (startB != b)){  // while the curr color is not yet the target color
        if (startR < r) startR++; else if (startR > r) startR--;  // increment or decrement the old color values
        if (startG < g) startG++; else if (startG > g) startG--;
        if (startB < b) startB++; else if (startB > b) startB--;
        g_LedsRing.setPixelColor(i, startR, startG, startB);  // set the color
        g_LedsRing.show();
       vTaskDelay(10 / portTICK_RATE_MS);
      }
      //delay(1000);
        vTaskDelay(g_LedsRingFadeDelay / portTICK_RATE_MS);
  }
}
#endif