
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define PIN        6
#define NUMPIXELS 8 // Popular NeoPixel ring size
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#include "RTClib.h"
RTC_DS1307 rtc;

void setup() {
  Serial.begin(57600);
  pixels.begin();


#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop() {
  DateTime now = rtc.now();

  uint8_t hr = now.hour();
  uint8_t mn = now.minute();
  uint8_t se = now.second();
  float i = mn / 7.5 ;
  int r = -1.771 * ((hr * hr) - (24 * hr));
  int b = 1.771 * (hr - 12) * (hr - 12);
  int g = -7.083 * (hr - 6) * (hr - 18);
  if (g < 0) {
    g = 0;
  }

  if (mn == 0) {
    pixels.clear();
  }
  pixels.setPixelColor(i, pixels.Color(r, g, b));
  pixels.show();




  // Serial.print(r);
  // Serial.print(",");
  // Serial.print(g);
  // Serial.print(",");
  // Serial.print(b);
  // Serial.print(":");
  Serial.print(hr);
  Serial.print(":");
  Serial.print(mn);
  Serial.print(":");
  Serial.println(se);

  //  Serial.println(con);
  delay(1000);


}

// put your main code here, to run repeatedly:
