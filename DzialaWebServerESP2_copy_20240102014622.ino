#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//klasa od kolorow
class Colors {
public:
  uint32_t color;
  uint32_t color2;
  int wait;

  Colors(uint32_t c1, uint32_t c2, int w) : color(c1), color2(c2), wait(w) {}
};

#define PIN_NEOPIXEL 2
#define NUMPIXELS    300

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

//definiowanie kombinacji kolorow wraz z czasem:
Colors colors1(strip.Color(108, 0, 108), strip.Color(100, 90, 0), 1);
Colors colors2(strip.Color(108, 0, 108), strip.Color(100, 90, 0), 5);
Colors colors3(strip.Color(150, 0, 150), strip.Color(0, 150, 190), 5);

/* Put WiFi SSID & Password */
const char* ssid = "PrincessLuna";   // Enter SSID here
const char* password = "Purpl3R@inbow0192"; // Enter Password here

ESP8266WebServer server(80);

bool wlaczenieKolorow = true;
int trybKolorow = 0;

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(D4, OUTPUT);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  // Connect to your local Wi-Fi network
  WiFi.begin(ssid, password);

  // Check if NodeMCU is connected to Wi-Fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP().toString());

  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/setmode", HTTP_GET, handle_setmode);  // Endpoint do zmiany trybu
  server.on("/togglecolors", HTTP_GET, handle_togglecolors);  // Endpoint do włączania/wyłączania kolorów

  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient();
  runColorMode();
}

void runColorMode() {
  if (wlaczenieKolorow) {
    switch (trybKolorow) {
      case 1:
        colorWipe(colors1.color, colors1.wait);
        break;
      case 2:
        secondColorWipe(colors2.color, colors2.color2, colors2.wait);        
        break;
      case 3:
        thirdColorWipe(colors3.color, colors3.color2,colors3.color2, colors3.wait);
        break;
      default:
        break;
    }
  } else {
    colorWipe(strip.Color(0, 0, 0), 5);
  }
}

void handle_OnConnect() {
  server.send(200, "text/html", updateWebpage(trybKolorow, wlaczenieKolorow));
}

void handle_setmode() {
  String value = server.arg("value");
  trybKolorow = value.toInt();
  Serial.println("Set mode: " + String(trybKolorow));
  server.send(200, "text/html", updateWebpage(trybKolorow, wlaczenieKolorow));
}

void handle_togglecolors() {
  wlaczenieKolorow = !wlaczenieKolorow;
  Serial.println("Toggle Colors: " + String(wlaczenieKolorow));
  server.send(200, "text/html", updateWebpage(trybKolorow, wlaczenieKolorow));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}


void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void secondColorWipe(uint32_t color, uint32_t color2, int wait) {
for(int j = 0; j < strip.numPixels(); j++) {
  for(int k = -6; k <= 6; k++) {
    int pixelIndex = j + k;
    if (k < 0) {
      strip.setPixelColor(pixelIndex, color);
    } else {
      strip.setPixelColor(pixelIndex, color2);
    }
  }
  strip.show();
  delay(wait);
  }
}

void thirdColorWipe(uint32_t color, uint32_t color2, int wait) {
for(int j = 0; j < strip.numPixels(); j++) {
  for(int k = -6; k <= 6; k++) {
    int pixelIndex = j + k;
    if (k < 0) {
      strip.setPixelColor(pixelIndex, color);
    } else {
      strip.setPixelColor(pixelIndex, color2);
    }
    
  }
  strip.show();
  delay(wait);
  }
}

void thirdColorWipe(uint32_t color, uint32_t color2, uint32_t color3, int wait) {
for(int j = 0; j < strip.numPixels(); j++) {
  for(int k = -6; k <= 6; k++) {
    int pixelIndex = j + k;
    int XpixelIndex = -j - k + 300;
    if (k < 0) {
      strip.setPixelColor(pixelIndex, color);
      strip.setPixelColor(XpixelIndex, color);
    } else {
      strip.setPixelColor(pixelIndex, color2);
      strip.setPixelColor(XpixelIndex, color3);
    }
    
  }
  strip.show();
  delay(wait);
  }
}

String updateWebpage(int trybKolorow, bool wlaczenieKolorow) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: rgb(0, 204, 0);margin: 50px auto 30px;} h3 {color: rgb(204, 0, 0);margin-bottom: 50px;}\n";
  ptr += "p {font-size: 14px;color: rgb(0, 0, 100);margin-bottom: 10px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";

  // Dodaj guziki do zmiany trybu
  ptr += "<p>Wybierz sobie tryb kolorow:</p>\n";
  ptr += "<a class=\"button\" href=\"/setmode?value=1\">Pierwszy</a>\n";
  ptr += "<a class=\"button\" href=\"/setmode?value=2\">Drugi</a>\n";
  ptr += "<a class=\"button\" href=\"/setmode?value=3\">Trzeci</a>\n";

  // Dodaj guzik do włączania/wyłączania kolorów
  ptr += "<p>Wlacznik:</p>\n";
  if (wlaczenieKolorow) {
    ptr += "<a class=\"button button-on\" href=\"/togglecolors\">Wylacz</a>\n";
  } else {
    ptr += "<a class=\"button button-off\" href=\"/togglecolors\">Wlacz</a>\n";
  }



  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

