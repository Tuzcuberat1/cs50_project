# MY CS50 Project - Gas Detector using Arduino
#### Video Demo:  <https://youtu.be/7lMznUrV37k>
#### Description:

This Arduino-based project focuses on a gas monitoring system with an interactive menu interface through LCD and joystick. Setting sensitivity threshold by potentiometer, showing gas levels on the LCD, and being able to send data via Bluetooth for remote monitoring are offered. The project offers a solution for the detection of gases. It would be useful in home safety and industrial monitoring.

## Components Used
- **Arduino board Uno:** This is for connecting my code to the arduino project/components.
- **Gas Sensor MQ-2:** This detects the gases in the environment. It detects LPG, methane, carbondioxide and many more.
- **Joystick module:** This component helps in navigation in the menu.
- **Potentiometer:** This unit is used to change the threshold level for detecting the gases.
- **Bluetooth module HC-06:** The module provides wireless communication with any Bluetooth device, and in this system, it sends the information about gas level information to the app designed with MIT App Inventor.
- **LiquidCrystal_I2C library:** This manages the LCD display.
- **SoftwareSerial library:** Communication with the Bluetooth module.

## Features
- **Menu System:** Interactive menu for user interaction via joystick.
- **Gas sensitivity adjustment**: The user can adjust the threshold of sensitivity to gas using a potentiometer.
- **Real-time Monitoring**: Keeps showing current gas levels through the LCD screen.
- **Alert system:** Buzzers and LEDs will sound and turn on when the gas levels exceed predefined thresholds.
- **Bluetooth Connectivity:** Transmits the data on gas levels by using Bluetooth connectivity of the app designed with MIT App Inventor to enable remote monitoring. This feature would allow the user to monitor the gas level from a distance.

## Setup Instructions
1. **Hardware Setup:**
   - **Connecting Components:** Connect the gas sensor, joystick, potentiometer, LCD and Bluetooth module according to the configuration of pins in the code below with respect to the Arduino board.
- **Checking the Connections:** All the connections should be checked for working preoperly. If the wiring is incorrect, the system will malfunction and not work.
   - **Power Supply:** The Arduino board should be provided with adequate power either through a USB connection with a computer or by an external power supply. It is not working with batteries.

2. **Software Setup:**
- **Libraries Installation:** You have to install all the libraries, viz. `Wire.h`, `LiquidCrystal_I2C.h`, `SoftwareSerial.h` in Arduino IDE. All these libraries are primarily used to handle the LCD display and Bluetooth communication.
- **Upload the Sketch:** Open the `CS50GasDetector.ino` file in Arduino IDE and upload the same to the Arduino board. This sketch is shared with the code that drives the entire gas monitoring system.

3. **Operation:**
- **Power On:** The system will start and then it will go to the main menu on the LCD screen.
- **Joystick Use:** As visible in the menu, all its options can be scrolled using the joystick. The joystick works on its X-axis to scroll vertically. Pressing the joystick button connected to the SW pin selects the highlighted option in the menu.
- **Monitoring and Alerts:** The gas levels can be displayed on the LCD screen. The system will automatically turn on the buzzer and the LEDs once the threshold setting has been exceeded.
- **Bluetooth Communication:** Connect to a Bluetooth module paired with the device that has Bluetooth, and has the application designed with MIT App Inventor which reads the gas level values.

## Usage
- **Menu Navigation:**
Use the X-axis of the joystick to navigate through menus.
 Press the joystick button—SW pin—to select menu options.
 Scroll between "Settings" and "Notifications" menus, either to change the settings or monitor the gas levels.

Adjust Gas Sensitivity
 Go into the "Settings" menu and adjust the threshold of gas sensitivity with potentiometer.
Now, using the potentiometer, turn it to set a new threshold value that will appear on the LCD.

- **Level Monitoring for Gases:**
  - "Notifications" menu: current gas levels will be constantly displayed.
  - Gas levels are displayed both on the LCD and over Bluetooth.

## Challenges and Solutions
- **Sensor Calibration:** The calibration of the gas sensor to obtain correct readings was a bit challenging. This was resolved by running several tests and fine-tuning the settings in terms of sensitivity until reliable readings were obtained. Better components can be used in the next projects.
- **Bluetooth Connectivity:** Having stable Bluetooth communication called for troubleshooting connection problems. This involved pairing the module with several devices and trying different apps to identify and solve the problems.
**Menu Interface Design:** The menu interface design was properly planned and done with the help of user feedback with limited space availability on an LCD and joystick controls. Iterative testing and refinements have resulted in a user-friendly interface.

## Further Improvements
- **Extra Gas Sensors:** More gas sensors would increase the capability of this device in detecting a wider variety of gases, like CO2 and CO.
- **Mobile App Integration:** A dedicated mobile app for remote monitoring with more options for control.
- **Data Logging:** Add the ability to log data of the gas level over time for historical analysis of trends.

## Notes
- **Bluetooth Pairing**: Ensure that the Bluetooth module is paired with any device that can receive data, for example a phone, with an appropriate app installed - like MIT App Inventor - to monitor the gas levels remotely.
- **Customization**: Threshold values and menu options can be edited as per need, to customize the application.

##
The following instructions will help you set up and work with the gas monitoring system. In this project, you are going to see how the different components and libraries are assimilated to get a functioning interactive gas detection system. Do not forget to stream the video demo for proper visualization of the setup and running of the system.

##
The following detailed README.md provides all information on understanding, setting up, and using the gas detector project. It shares details of the components used, features, setup and usage instructions, challenges faced, solutions implemented, and possible future improvements.
