# Pajero Temp Guard
This is an Arduino based OBD reader solution that incorporates standard PID commands AND custom PID commands for non standard data. <BR><BR>
This code and library is based on the Freematics OBD reader and libraries written by Stanley Huang - all copyright on the libraries etc... to him - his GIT is here: https://github.com/stanleyhuangyc/ArduinoOBD<BR><BR>
Using this library and working through the AT Command sets, we are able to call custom PID commands once we know what we are looking for.<BR><BR>

To get this up and running you will need....

## Hardware

* Freematics OBDUART reader - https://freematics.com/store/index.php?route=product/product&path=20&product_id=30 - Note I'm using V1 but V2.1 should work fine as well.<BR>
* 0.91" 128x32 OLED with I2C connection - something like this - https://wiki.52pi.com/index.php/0.91_Inch_OLED_Module_SKU:_S-0006 or https://tinyurl.com/y6jb9kw3<BR>
* Arduino MEGA 2560 - note that the libraries are fairly heavy which is why I've gone with the Mega at this stage. You can slim this down by dropping out the Adafruit GFX functions, LED/Buzzer alarms and library and it will fit on an UNO - only just though.<BR>
* 2 x 3MM LEDs with resistors<BR>
* Arduino Buzzer Module (2pin version or 3 pin will work if you ground it seperately)
* Various hookup wire<BR>

<BR>

## Software

* Freematics library - https://github.com/stanleyhuangyc/ArduinoOBD
* Adafruit GFX library - https://learn.adafruit.com/adafruit-gfx-graphics-library
* Adafruit BUSIO (required for GFX library but not called directly, later IDE versions should self install this)
* Adafruit OLED SSD1306 library - https://github.com/adafruit/Adafruit_SSD1306


<BR>
  
## 3D Designs
  
Available on thingiverse - https://www.thingiverse.com/thing:4753375
  
<BR>
  

