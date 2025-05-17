# 🔊 Voice-Controlled LED Automation
A basic voice-controlled home automation system to turn ON or OFF up to four LEDs using voice commands. This project is ideal for beginners learning about speech recognition and microcontroller integration.

# 🎯 Features
Voice commands to control 4 LEDs

Simple and beginner-friendly C++ + Arduino setup

Offline speech recognition (optional)

communication between WEB Page and microcontroller (using IP Adderss of microcontroller)


🧰 Tech Stack
Creat a WEB Page for Speech Recognition and Command Processing

Arduino UNO / ESP32 (for LED control)/Raspberry Pi Picow W
In my case I use Raspberry Pi Pico W

Connect the Web Page created to the Server of microcontroller   (using IP Adderss of microcontroller)
connect the microcontroller and the device(from which  thw web page is running) with a common WIFI connection
Device should have a stable internet connectivity

# 📦 Installation

Upload the code in your Device (HTML file)

Download Arduino IDE (for .ino file)

Connect LEDs
connectv the LED pins with the microcontroller GPIO pins
remember to update the code as per connections

Use 220Ω resistors for each LED.

🎤 Voice Commands
Voice Command	Action
Turn on LED 1	Turns on LED1
Turn off LED 1	Turns off LED1
Turn on LED 2	Turns on LED2
Turn off LED 2	Turns off LED2
Turn on LED 3	Turns on LED3
Turn off LED 3	Turns off LED3
Turn on LED 4	Turns on LED4
Turn off LED 4	Turns off LED4

🚀 How to Run
Plug in your Microcontroller
upload the  .ino file in your microcontroller

Run the HTML file:

connect the microcontroller and the device(from which  thw web page is running) with a common wifi connection
Device should have a stable internet connectivity

give the voice commad through the Web Page
example voice command:
"Turn on LED 3"
The system recognizes your speech and sends a command to the Microcontroller to toggle the correct pin.


