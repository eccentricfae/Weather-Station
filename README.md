# IoT Weather Station

# TLDR
This project is a simple internet-enabled Weather Station, built using Raspberry Pi Pico W microcontroller. The uC opens up an HTTP server, on port 80, to serve / display a simple web page with data from the sensors: temperature and humidity.
TODO Picutres: webpage-phone, webpage-desktop, the device, circuit

# Detailed description

## Software

### Networking software
Pico W uses the lwIP stack as the networking stack for its CYW43439 chip.<br>
The lwIP stack uses HTTPd daemon to set up an HTTP server on port 80 on the chip's 
network interface. 
The webpage can be just any regular old HTML code with CSS styles and JavaScript 
code, but it's important to remember that everything regarding any given webpage 
needs to be embedded into that webpage (html file). That is because the html files
need to be "transpiled" from human-readable text into C's strings, i.e. char arrays,
put into a speical .c source file and included into a project so that the web page's
raw data can be put onto the uC storage.<br>
The HTTPd daemon uses CGI (Common Gate Interface) to process user's requests. In this 
project the CGI is used to display either the default-home page when accessing the 
server with either no tag (just pure address of the uC) or with the "/home" tag. The 
second tag used by the set up CGI is "/debug" tag, that tells the server to return a 
simple web page with debug informations about the device.<br>
The HTTPd daemon uses basic SSI (Server-Side Includes) to fill out the HTML pages with 
desired info. In this project the SSI is used to fill out the temperature and humidity 
data from the sensors, as well as the data in the debug page.<br>
TODO Add info about mDNS if using


### Hardware-side software
TODO

## Hardware

### The circuit
TODO Describe the circuit, power draw, picutres, etc?

### Raspberry Pi Pico W
As the "brain" of the project a Raspberry Pi Pico W was chosen. It is a rather inexpensive 
ARM Cortex M0+ microcontrolled with its CYW4339 chip that enables wireless connectivity. 
The uC was chosen over others as it is Raspberry Pi Foundation's device, thus it has a very 
expansive and well-done documentation as well as rather simple and powerful SDK.

### Temperature and humidity sensor
For the temperature and humidity sensor "AM2320" was chosen. No really any particular reason why, 
it was on sale and had good reviews :) It uses I2C for communication.