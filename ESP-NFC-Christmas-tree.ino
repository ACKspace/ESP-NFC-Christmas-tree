#define NEOPIXELS
#define NFC
#define SERIAL_DEBUG
//#define WIFI

#ifdef WIFI
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
// Note: they're not const since we might want to change it realtime
char *ssid = "ACKspaceWifi";
char *password = "HAHAHAH-NEVAH!!!11one";

ESP8266WebServer server( 80 );

////////////////////////////////////////////////////////////////////////////d////
// 
////////////////////////////////////////////////////////////////////////////////
bool connectWifi()
{
  // Try and connect to the wifi
  WiFi.begin( ssid, password );

  uint8_t nFail = 0;

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED && nFail < 20 )
  {
    nFail++;
    delay( 500 );
  }

  // If we've succeded, we're done
  if ( WiFi.status() == WL_CONNECTED )
    return true;

  // Failed to connect Set-up our own AP
  // TODO: check if there is already an AP with the same name: this means our password was invalid!

  WiFi.softAP( ssid, password );
  IPAddress myIP = WiFi.softAPIP();
  
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot()
{
  server.send(200, "text/html", "<h1>You are connected</h1>");
}
#endif

#ifdef NEOPIXELS
#include <Adafruit_NeoPixel.h>

// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

// GPIO0=FLASH
#define PIN 0
#define NUM_PIXELS 198

// xopr
Adafruit_NeoPixel pixels = Adafruit_NeoPixel( NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800 );

// vicarious
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel( NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ400 );
////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
// Helper functions
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
#endif

#ifdef NFC
// Don't know why, but apparently these libraries fail to be included
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK  (16)
#define PN532_MISO (14)
#define PN532_MOSI (12)
#define PN532_SS   (13)

// Use this line for a breakout with a SPI connection:
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
#endif

//
uint8_t knownIds[][7] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // xopr's entry key

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // Vicarious! mifare ultralight
  /*{ 0x00, 0x00, 0x00, 0x00, 0, 0, 0 }, // Vicarious! mifare classic 1k*/
  /*{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // Vicarious door entry Mifare DESfire*/

  { 0x6B, 0x47, 0xD9, 0x2E, 0, 0, 0 }, // Freenom2464.ml Melons & Meatloaf

  { 0x04, 0x23, 0x67, 0xB2, 0xCA, 0x3E, 0x81 }, // disposable 0107
  { 0x04, 0xB8, 0x12, 0x3A, 0x9C, 0x35, 0x80 }, // disposable 0151
  { 0x04, 0xA3, 0xF0, 0xEA, 0x3C, 0x3C, 0x80 }, // disposable 0157
  { 0x04, 0xC2, 0x0E, 0x6A, 0x72, 0x36, 0x80 }, // disposable 0263
  { 0x04, 0xC6, 0x6F, 0x12, 0x47, 0x3C, 0x80 }, // disposable 0419
  { 0x04, 0x6C, 0xA4, 0x5A, 0x98, 0x36, 0x80 }, // disposable 0762
  { 0x04, 0x54, 0xF0, 0x6A, 0x01, 0x3E, 0x80 }, // disposable 1070
  { 0x04, 0x5F, 0xEF, 0xEA, 0x3E, 0x3C, 0x80 }, // disposable 1217
  { 0x04, 0x87, 0x99, 0xFA, 0x5E, 0x48, 0x80 }, // disposable 3845
  { 0x04, 0x93, 0x3A, 0x8A, 0xF5, 0x33, 0x80 }, // disposable 4801
  { 0x04, 0xAF, 0x15, 0xF2, 0x7D, 0x3F, 0x84 }, // disposable 5134
  { 0x04, 0x2A, 0x8F, 0xE2, 0x3B, 0x36, 0x81 }, // disposable 5914
  { 0x04, 0x1A, 0x9D, 0x3A, 0x77, 0x43, 0x81 }, // disposable 5998
  { 0x04, 0xAD, 0x2D, 0x6A, 0x5C, 0x48, 0x80 }, // disposable 6190
  { 0x04, 0xCB, 0x67, 0x32, 0x7B, 0x3F, 0x80 }, // disposable 7430
  { 0x04, 0xF3, 0x65, 0x32, 0x7B, 0x3F, 0x80 }, // disposable 7509
  { 0x04, 0xE7, 0x65, 0x32, 0x7B, 0x3F, 0x80 }, // disposable 7511

  { 0x04, 0x46, 0x93, 0x62, 0xEB, 0x2B, 0x80 }, // TOH Snow White
  { 0x04, 0xD3, 0x8F, 0x0A, 0x7A, 0x2B, 0x80 }, // TOHKBD

  
  { 0xCD, 0x8C, 0x0D, 0xE6, 0, 0, 0 }, // PT 1 (16,50)
  { 0x3D, 0x9D, 0x9B, 0xEB, 0, 0, 0 }, // PT 2 (9,27)
  { 0x53, 0xA7, 0xA0, 0x6C, 0, 0, 0 }, // PT 3 (7,25)

  { 0x03, 0xD9, 0x06, 0xCD, 0, 0, 0 }, // Long blue key
  { 0x33, 0x5F, 0xCC, 0xDE, 0, 0, 0 }, // Short blue key
  { 0x7F, 0xA6, 0xCE, 0x00, 0, 0, 0 }, // Blank key card

  { 0x00, 0x00, 0x00, 0x00, 0, 0, 0 }, // xopr's badge
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // xopr's Elektor card
  { 0x00, 0x00, 0x00, 0x00, 0, 0, 0 }, // xopr's dumpster card
  { 0x00, 0x00, 0x00, 0x00, 0, 0, 0 } // xopr's public transport card
};

#ifdef NFC
int8_t nCurrentProgram = -1; // Wait for program
#else
int8_t nCurrentProgram = 1; // Rainbow
#endif


// Loops
////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
#ifdef NEOPIXELS
void loop_waiting_for_program()
{
  for( uint16_t i = 0; i< pixels.numPixels(); i++ )
  {
    pixels.setPixelColor( i, pixels.Color( 200, 100, 20 ) );
  }
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void loop_free_program_slot()
{
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void loop_0()
{
}

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void loop_1( )
{
byte brightness;
  // First 28 leds always red
  for (byte i = 0; i < 27; i++) {
    brightness = random(1,3);
    if (random(100) <= 100) {
      pixels.setPixelColor(i,100 / brightness,0,0);
    } else {
      pixels.setPixelColor(i,0,0,0);
    }
  }
  
  // Next 28 leds darker reddish
  for (byte i = 27; i < 55; i++) {
    brightness = random(1,3);
    if (random(100) <= 95) {
      pixels.setPixelColor(i,random(80,100)/brightness,random(10,20)/brightness,0);
    } else {
      pixels.setPixelColor(i,0,0,0);
    }
  }  

  // Next 28 leds darker reddish
  for (byte i = 55; i < 83; i++) {
     brightness = random(1,4);
     if (random(100) <= 90) {
      pixels.setPixelColor(i,random(80,90)/brightness,random(20,45)/brightness,0);
    } else {
      pixels.setPixelColor(i,0,0,0);
    }
  }
  
  // Next 28 leds orange
  for (byte i = 83; i < 111; i++) {
     brightness = random(1,4);
     if (random(100) <= 80) {
      pixels.setPixelColor(i,random(70,90)/ brightness ,random(20,45) / brightness,0);
     } else {
      pixels.setPixelColor(i,0,0,0);
     }
  }
  
  // Next 28 leds yellow
  for (byte i = 111; i < 139; i++) {
     brightness = random(1,4);
     if (random(100) <= 40) {
      pixels.setPixelColor(i,random(40,50)/ brightness,random(10,30)/ brightness,0);
     } else {
      pixels.setPixelColor(i,0,0,0);
     }
  }
  
  // Next 28 leds yellow
  for (byte i = 139; i < 167; i++) {
      brightness = random(1,4);
      if (random(100) <= 20) {
      pixels.setPixelColor(i,random(40,50)/ brightness,random(10,30)/ brightness,0);
      } else {
      pixels.setPixelColor(i,0,0,0);
    }
  }

  // Next 13 leds yellow
  for (byte i = 167; i < 180; i++) {
      brightness = random(1,4);
      if (random(100) <= 10) {
      pixels.setPixelColor(i,random(40,50)/ brightness,random(10,30)/ brightness,0);
      } else {
      pixels.setPixelColor(i,0,0,0);
      }
    }
    
  // Next 18 leds yellow
  for (byte i = 180; i < 198; i++) {
      brightness = random(1,4);
      if (random(100) <= 5) {
      pixels.setPixelColor(i,random(40,50)/ brightness,random(10,30)/ brightness,0);
      } else {
      pixels.setPixelColor(i,0,0,0);
      }
    }
}

void loop_3( uint8_t _nDelay = 7 )
{
  uint16_t i, j;
  j = (millis( ) >> _nDelay );

  for( i = 0; i< pixels.numPixels(); i++ )
  {
    pixels.setPixelColor( i, Wheel( ((i * 256 / pixels.numPixels()) + j) & 255) );
  }
  
}


////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void allPixels( uint32_t _color )
{
  for( uint16_t i = 0; i< pixels.numPixels(); i++ )
    pixels.setPixelColor( i, _color );
}

#endif

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin( 115200 );
  Serial.println( "\n\nInitializing.." );  
#endif

#ifdef NEOPIXELS
  pinMode( PIN, OUTPUT );     // Initialize the BUILTIN_LED pin as an output
#ifdef SERIAL_DEBUG
  Serial.println( "NeoPixels...ok" );
#endif
#endif

  // Connect wifi or setup an accesspoint
  //Serial.println( "Connecting" );

#ifdef NFC
#ifdef SERIAL_DEBUG
  Serial.print( "NFC........." );
#endif
  // Initialize RFID
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
#ifdef SERIAL_DEBUG
    Serial.print("Didn't find PN53x board");
#endif
    while (1); // halt
  }

#ifdef SERIAL_DEBUG
  // Got ok data, print it out!
  Serial.print( "Found chip PN5" );
  Serial.print( (versiondata>>24) & 0xFF, HEX );
  Serial.print( ", Firmware ver. " );
  Serial.print((versiondata>>16) & 0xFF, DEC);
  Serial.print( '.' );
  Serial.print((versiondata>>8) & 0xFF, DEC);
#endif

  // configure board to read RFID tags
  nfc.SAMConfig();

#ifdef SERIAL_DEBUG
  Serial.println( "...ok" );
#endif
#endif

#ifdef WIFI
#ifdef SERIAL_DEBUG
  Serial.print( "WiFi........" );
#endif

  // Connect to AP or create one
  connectWifi();

  // Handle HTTP requests
  server.on("/", handleRoot);
  //server.onNotFound(handleNotFound);

#ifdef SERIAL_DEBUG
  Serial.println( "ok" );
#endif

#endif
}


#ifdef NFC
////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
int8_t findCard( uint8_t* _uid, uint8_t _uidLength )
{
  bool bMatch;
  uint8_t IdCount = sizeof( knownIds ) / 7;
  for ( int8_t nCard = 0; nCard < IdCount; nCard++ )
  {
    bMatch = true;
    for ( uint8_t nId = 0; nId < _uidLength && bMatch; nId++ )
      if ( knownIds[ nCard ][ nId ] != _uid[ nId ] )
        bMatch = false;

      // All bytes match
      if ( bMatch )
        return nCard;
  }
  
  // Nothing found
  return -1;
}
#endif




////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void loop()
{
#ifdef WIFI
  // Handle requests
  server.handleClient();
#endif

#ifdef NFC
  uint8_t success = 0;                      // Flag to check if there was an error with the PN532
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  // Read RFID card
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 40 );
  if ( success )
  {
    /*
    // Display some basic information about the card
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println( "" );
    */
    // Identify the card
    nCurrentProgram = findCard( uid, uidLength );

#ifdef SERIAL_DEBUG
    //Serial.begin( 115200 );
    if ( nCurrentProgram == -1 )
    {
      Serial.println( "Card not identified: " );
      nfc.PrintHex(uid, uidLength);
    }
    else
    {
      Serial.print( "Card number:" );
      Serial.println( nCurrentProgram, DEC );
    }
    Serial.flush( );
#endif
#ifdef SERIAL_DEBUG
    //Serial.end( );
#endif
  }
#endif

#ifdef NEOPIXELS
  switch ( nCurrentProgram )
  {
    // Unknown card
    case -1:
      loop_waiting_for_program();
      
      break;
    case 0:
      loop_0();
      break;
      
    case 1:
    case 2:
      loop_1();
      break;
      
    case 3:
    case 4:
    case 5:
      loop_3( 4 * ( nCurrentProgram - 2 ) );
      break;

    case 6:
      allPixels( pixels.Color( 255, 0, 0 ) );
      break;
    case 7:
      allPixels( pixels.Color( 0, 255, 0 ) );
      break;
    case 8:
      allPixels( pixels.Color( 0, 0, 255 ) );
      break;

    case 9:
      allPixels( pixels.Color( 255, 255, 255 ) );
      break;

    case 10:
      loop_waiting_for_program();
      break;

    // Registered card, but no program
    default:    
      loop_free_program_slot();
      break;
  }

  pixels.show( );
#endif
  //ESP.deepSleep( 100 );
}

