#include <Adafruit_NeoPixel.h>

#define PIN 11

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  80 0 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);
    
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
void loop() {
  // put your main code here, to run repeatedly:
  int red,green,blue;

     green = 0;


  for(green = 10; green < 256; green++){
     strip.setPixelColor(0, 0, green, 0 );
     strip.setPixelColor(1, 0, green, 0 );
     strip.setPixelColor(2, 0, green, 0 );
     strip.setPixelColor(3, 0, green, 0 );
     strip.setPixelColor(4, 0, green, 0 );
     delay(10);
        strip.show();
    }
  for(green = 255; green >10 ;green --){
          strip.setPixelColor(0, 0, green, 0 );
     strip.setPixelColor(1, 0, green, 0 );
     strip.setPixelColor(2, 0, green, 0 );
     strip.setPixelColor(3, 0, green, 0 );
     strip.setPixelColor(4, 0, green, 0 );
     delay(25);
        strip.show();
  }
}
