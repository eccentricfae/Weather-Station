# IoT Weather Station

# TLDR
This project is a simple internet-enabled Weather Station, built using Raspberry Pi Pico W microcontroller. The uC opens up an HTTP server, on port 80, to serve / display a simple web page with data from the temperature sensor.

# Showcase

## Main page / "Home"
TODO Pictures and description

## Details page
TODO Pictures and description

## Debug / Meta info page
TODO Pictures and description

# Detailed description

## Software

### Networking software
Pico W uses the lwIP stack as the networking stack for its CYW43439 chip.<br>
The lwIP stack uses HTTPd daemon to set up an HTTP server on port 80 on the chip's 
network interface. 
The webpage can be just any regular old HTML code with CSS styles and JavaScript 
code, but it's important to remember that everything regarding any given webpage (like 
CSS styles) needs to be embedded into that webpage (html file). That is because the html 
files need to be "transpiled" from human-readable text into C's strings, i.e. char arrays,
put into a special .c source file and included into a project so that the web page's
raw data can be put onto the uC storage. The "makefsdata.py" (in src/helpers/) is the python script 
that transpiles the .html files from the html directory into the html_data.c file (the 
file is supposed to be ignored by .gitignore but was included for demonstration 
purposes).<br>
The HTTPd daemon uses CGI (Common Gate Interface) to process user's requests. In this 
project the CGI is used to display either the default-home page when accessing the 
server with either no tag (just pure address of the uC) or with the "/home" tag. The 
second tag used by the set up CGI is "/debug" tag, that tells the server to return a 
simple web page with debug informations about the device.<br>
There is also a "/details" page w/ summary of the info (temperature readings) that were
taken by the uC.<br>
The HTTPd daemon uses basic SSI (Server-Side Includes) to fill out the HTML pages with 
desired info. In this project the SSI is used to fill out the temperature and humidity 
data from the sensors, as well as the data in the debug page.<br>


### Hardware-side software
The software that manages the "hardware" functionalities can be grouped into different
functionalities: <br>
- reading the temperature from sensor: Reading the temperature is as simple as reading 
an analog voltage value using on-board A/D converter on specific GPIO pin.
- reading the temperature from the on-board thermometer: same as above, but instead of 
using a GPIO pin, an internal connections are used.
- reading the battery voltage level: Also uses A/D converter :)
- singalling LOC (Loss of Connection): When the uC observes that it lost connection
to the Wifi network, it will light up an LED. Simple gpio_put(value) is used for driving
the pin into high / low logical level

## Hardware

### The circuit
TODO Circuit picture
The circuit is a rather simple one. Between the battery and the rest of the circuit is a 
switch that controls the power delivery (ON/ OFF).<br>
The temperature sensor outputs an analog voltage value on its Vout pin that corresponds 
to the read temperature, following this formula: T = (V - 0.5) * 100<br>
The LED is not directly driven by the uC but rather a low-side switch made w/ a simple
NPN BJT, that is controlled by the uC. RPI Pico W is more than capable of delivering 
enough current on its GPIO's output to light an LED, but it's not necesserily the most 
safe nor recommended aproach. Thus: the low-side switch.<br>
RPI Pico's connection are also rather self-explanatory:<br>
- VSYS and GND are just: POWER IN and GND (common) inputs - "power bus" if you will :)<br>
- ADC_REF pin is shorted to 3.3 V output as it is the A/D converters reference voltage 
level. It can't be connected to the "positive terminal" of the battery, because when the
battery's output voltage would drop, the referenced value would also drop, therefore the 
readings regarding battery's voltage output would always equal 3.2 V (nominal value for
 my batteries)
- AGND - A/D converter's GND pin 
- ADC1 / ADC0 - A/D converter's channel 1 and 0 inputs
The circuit draws an average of <// TODO avg current draw> while working. Considering an average AA battery w/
<// TODO AA bat's cap> capacity, the device can work up to <// TODO Total cap / avg current draw>.<br>
The batteries for this device are: two parallel-connected two-slot battery baskets. Therefore 
the device should have total capacity of around 2*<// TODO avg cap> = <// TODO Result> @ 3.2 V.

### Raspberry Pi Pico W
As the "brain" of the project a Raspberry Pi Pico W was chosen. It is a rather inexpensive 
ARM Cortex M0+ microcontrolled with its CYW4339 chip that enables wireless connectivity. 
The uC was chosen over others as it is Raspberry Pi Foundation's device, thus it has a very 
expansive and well-done documentation as well as rather simple and powerful SDK.

### Temperature sensor
For the temperature sensor TMP36 was used as it came with the starting kit that I've 
bought some time ago, and I don't have an oscilloscope at home to play around w/ I2C etc.
devices.
