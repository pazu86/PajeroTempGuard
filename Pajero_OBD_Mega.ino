/*************************************************************************

OBD Data Display for Gen 4 Pajeros

*************************************************************************/

//Include Libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OBD2UART.h>


//Define alarm levels - there are two red LEDs, one for each measurement and a buzzer for secondary alarm.
int AT_Temp_Warn    = 110;    //C degrees
int AT_Temp_Alarm   = 120;    //C degrees
int ENG_Temp_Warn   = 110;    //C degrees
int ENG_Temp_Alarm  = 120;    //C degrees



//Define Serial Output for debugging
//#define mySerial Serial

//Setup OBD Processor
COBD obd;


// Define LCD
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//define logo
#define LOGO_HEIGHT   32
#define LOGO_WIDTH    128
const unsigned char myBitmapBitmap [] PROGMEM = {
  // 'Mitsubishi_black_logo-700x602, 126x32px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfd, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfd, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xe0, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xe0, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x80, 0x0f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};




void setup()
{

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    //Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  //Setup LED pin outs and Buzzer

  //ENG Temp LED
  pinMode(8, OUTPUT); //Positive
  pinMode(9, OUTPUT); //Negative
  digitalWrite(9, LOW); //Pull Negative Low to GND
  //digitalWrite(8, HIGH); //Turns on LED (Debug)

  //AT Temp LED
  pinMode(10, OUTPUT); //Positive
  pinMode(11, OUTPUT); //Negative
  digitalWrite(11, LOW); //Pull Negative Low to GND
  //digitalWrite(10, HIGH); //Turns on LED (Debug)

  //Buzzer
  pinMode(6, OUTPUT); //Positive
  pinMode(7, OUTPUT); //Negative
  digitalWrite(7, LOW); //Pull Negative Low to GND

  //Set rotation for LCD 180 degrees
  display.setRotation(2);
  //Reset/Clear display for use
  display.clearDisplay();

  //Display Logo
  drawbitmap();    // Draw a small bitmap image

  //Display Name
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("  PAJERO"));
  display.setCursor(0, 16);            // Start at top-left corner
  display.println(F("TEMP GUARD"));
  display.display();



  //Display Version
  delay(2000);
  display.clearDisplay();
  display.setCursor(0, 10);            // Start at top-left corner
  display.println(F("   V1.2"));
  display.display();

  delay(1000);

  //Start OBD Connection
  obd.begin();

  digitalWrite(8, HIGH); //Turns on ENG Warning LED
  digitalWrite(10, HIGH); //Turns on AT Warning LED

  display.clearDisplay();
  display.setCursor(0, 6);            // Start at top-left corner
  display.setTextSize(1.5);             // Normal 1:1 pixel scale
  display.println(F("    Connecting"));
  display.setCursor(0, 16);            // Start at top-left corner
  display.println(F("    to vehicle..."));
  display.display();

  while (!obd.init());

  delay(1000);
  display.clearDisplay();
  display.setCursor(0, 6);            // Start at top-left corner
  display.setTextSize(1.5);             // Normal 1:1 pixel scale
  display.println(F("    Connected!"));
  display.display();
  delay(1000);


  digitalWrite(8, LOW); //Turns off ENG Warning LED
  digitalWrite(10, LOW); //Turns off AT Warning LED



  //Launch main screen
  initScreen();

}

void loop()
{

  // Read Default Pids
  static byte pids[] = {PID_COOLANT_TEMP};
  static byte index = 0;
  byte pid = pids[index];
  int value;
  // send a query to OBD adapter for specified OBD-II pid
  if (obd.readPID(pid, value)) {
    showData(pid, value);
  }
  index = (index + 1) % sizeof(pids);


  // Read Direct ELM Codes
  RunATcommands();

  if (obd.errors >= 2) {
    reconnect();
    setup();
  }
}

void drawbitmap(void) {
  display.clearDisplay();
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    myBitmapBitmap, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(2000);
}


//This function works - don't change it!

//Custom AT Commands to pull OBD data - magic sauce for custom PIDs
void RunATcommands()
{
  //Setup AT Commands to sent
  //ATZ - soft reset
  //ATH1 - Show headers
  //ATS1 - Show Spaces between bytes
  //0100 - test PID code (Quirk in library - if you don't call this, every other command fails - not actually used anywhere
  //ATSH7E - Switch header to Trans Module (Equivalent of TCM header for Pajeros)
  //2102 - Call Trans Temp PID

  //For other AT Commands and to understand the commands being made - see Spec sheet here: https://www.elmelectronics.com/wp-content/uploads/2016/07/ELM327DS.pdf
  
  static const char cmds[][9] = {"ATZ\r", "ATH1\r", "ATS1\r", "0100\r", "ATSH7E1\r", "2102\r"};
  char buf[128];

  for (byte i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++) {
    const char *cmd = cmds[i];
    //mySerial.print("Sending ");
    //mySerial.println(cmd);

    //Send Serial command
    if (obd.sendCommand(cmd, buf, sizeof(buf))) {
      char *p = strstr(buf, cmd);
      if (p)
        p += strlen(cmd);
      else
        p = buf;

      //Take buffer and pull characters 39 and 40 - combined gives AT Temp
      //The If statement is a check digit to make sure we pull correct PID response from multiple lines
      //For reference, a typical response including header from the 2102 command is:
      //
      //7E9100C6102FF059A00
      //7E92100555500FF85FF
      //
      // The AT Temp is buried in this code - specifically 7E92100  55   5500FF85FF these two characters (55). 
      //They are written in Hexadecimal - so in the example here, 55 in hexadecimal. 
      //If you convert that to Decimal, it is 85. Apply the equation (F-50), 85 - 50 = 35 Degrees)
      //
      //You have to treat the two lines as a single line and access the relevant character numbers (39 and 40)
      //
      //Putting that into practice you get the following
      
      //Check digit to confirm correct response
      if (buf[4] == '1') {
        //Debug - print full Buffer
        //mySerial.println(buf);

        //Debug - print Char 39 and 40 seperately
        //mySerial.print(buf[39]);
        //mySerial.println(buf[40]);

        //Combine char 39 and 40 to create Hex number for conversion
        //char output1 = buf[39]; //Debug
        //char output2 = buf[40]; //Debug
        char output3[3] = {buf[39], buf[40]};

        //Debug - test combined output
        //mySerial.println("HEX Number");
        //mySerial.println(output3);

        //Convert HEX Number to DEC number
        long output4 = strtol(output3, NULL, 16);

        //Temp equation to correct output - in this case F-50
        output4 = output4 - 50;

        //Print Trans Temp to serial
        //mySerial.println("Corrected DEC number");
        //mySerial.println(output4);

        //Display output on LCD
        display.fillRect(72, 8, 58, 26, BLACK);
        display.setCursor(80, 16);
        display.setTextSize(2);
        display.print(output4);
        display.println('C');
        display.display();

        //Warning LED Check
        if (output4 > AT_Temp_Warn) {
          digitalWrite(10, HIGH); //Turns on LED


          //Alarm Buzzer Check
          if (output4 > AT_Temp_Alarm) {
            digitalWrite(6, HIGH); //Turn Buzzer On
          }
          else {
            digitalWrite(6, LOW); //Turn Buzzer On
          }

        }
        else {
          //Turn Warning and buzzer off
          digitalWrite(10, LOW); //Turns off LED
          digitalWrite(6, LOW); //Turn Buzzer On
        }



      }

      while (*p == '\r') p++;
      while (*p) {
        Serial.write(*p);
        if (*p == '\r' && *(p + 1) != '\r')
          Serial.write('\n');
        p++;
      }
      //mySerial.println();

    } else {
      //mySerial.println("Timeout");
    }
    delay(1000);
  }
  //mySerial.println();
}




//Reconnect if disconnected, also used for sleeping
void reconnect()
{

  display.clearDisplay();
  // display.setCursor(0, 6);            // Start at top-left corner
  // display.setTextSize(1.5);             // Normal 1:1 pixel scale
  // display.println(F("   Reconnecting"));
  // display.setCursor(0, 16);            // Start at top-left corner
  //  display.println(F("    to vehicle..."));
  display.display();

  for (uint16_t i = 0; !obd.init(); i++) {
    if (i == 5) {
      display.clearDisplay();
    }
    delay(3000);
  }
}


//Show standard PID data
void showData(byte pid, int value)
{
  switch (pid) {
    case PID_COOLANT_TEMP:
      display.fillRect(7, 8, 58, 26, BLACK);
      display.setCursor(7, 16);
      display.setTextSize(2);
      display.print(value);
      display.println('C');
      display.display();

      //Warning LED Check
      if (value > ENG_Temp_Warn) {
        digitalWrite(8, HIGH); //Turns on LED


        //Alarm Buzzer Check
        if (value > ENG_Temp_Alarm) {
          digitalWrite(6, HIGH); //Turn Buzzer On
        }
        else {
          digitalWrite(6, LOW); //Turn Buzzer On
        }

      }
      else {
        //Turn Warning and buzzer off
        digitalWrite(8, LOW); //Turns off LED
        digitalWrite(6, LOW); //Turn Buzzer On
      }

      break;
  }
}


//Setup screen for use
void initScreen()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(64, 0);
  display.println(F("|"));
  display.setCursor(64, 16);
  display.println(F("|"));
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(F("  ENG TMP"));
  display.setCursor(65, 0);
  display.setTextSize(1);
  display.println(F("    AT TMP"));
  display.setTextSize(2);
  //Engine Temp Display
  display.setCursor(7, 16);
  display.println(F("---"));
  //Trans Temp Display
  display.setCursor(80, 16);
  display.println(F("---"));

}
