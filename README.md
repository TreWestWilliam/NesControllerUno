# NesControllerUno
A demo project for controlling a lightstrip using a NES (Nintendo Entertainment System) Controller + Arduino Uno
I am unsure if this works with the Famicom, those might use different pinouts.  
Uses PlatformIO, compiling for Arduino Uno / Uno Clones
Utilizes the FastLED library for controlling the light strip.
The FastLED stuff can be torn out if you want to use the serial output to demonstrate something.

The setup is a little complicated.  I'd advise you to google the NES controller pinout, hooking up 5v and Ground to the respective pins.
clk latch and data are all defined in the program and should be fine to switch between any pin, though I might be wrong since I did this project a few months ago.
Otherwise, there shouldn't be any issue.

In the future I might code something similar to this for the ESP12e+8266 development board to utilize factory NES controllers as bluetooth controllers.  This might even involve hooking up to an NES completely wirelessly, or utilization with a Raspberry Pi for Retropie.  
