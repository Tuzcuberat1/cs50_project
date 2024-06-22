# YOUR PROJECT TITLE
#### Video Demo:  <https://youtu.be/7lMznUrV37k>
#### Description:

This Arduino sketch enables a gas monitoring system with a menu interface using an LCD and joystick. It includes features like setting sensitivity thresholds via a potentiometer, displaying gas levels on an LCD, and sending data over Bluetooth.

## Components Used
- Arduino board (Uno)
- Gas sensor (MQ-2)
- Joystick module
- Potentiometer
- Bluetooth module (HC-06)
- LiquidCrystal_I2C library for LCD display
- SoftwareSerial library for Bluetooth communication

## Features
- **Menu System:** Navigate through settings and notifications menus using a joystick.
- **Gas Sensitivity Adjustment:** Adjust gas detection sensitivity using a potentiometer.
- **Real-time Monitoring:** Display current gas levels on an LCD screen.
- **Alert System:** Activate buzzer and LEDs based on predefined gas threshold levels.
- **Bluetooth Connectivity:** Send gas level data wirelessly over Bluetooth for remote monitoring.

## Setup Instructions
1. **Hardware Setup:**
   - Connect all components as per the defined pin configurations in the code.
   - Ensure the gas sensor, joystick, potentiometer, and LCD are correctly wired to the Arduino board.

2. **Software Setup:**
   - Install the required libraries (`Wire.h`, `LiquidCrystal_I2C.h`, `SoftwareSerial.h`) in your Arduino IDE.
   - Upload the provided sketch (`gas_monitor.ino`) to your Arduino board.

3. **Operation:**
   - Power on the Arduino board.
   - Use the joystick to navigate between menu options and adjust settings.
   - Monitor gas levels on the LCD screen.
   - Receive gas level notifications via the buzzer and LEDs.

## Usage
- **Menu Navigation:**
  - Use the joystick's X-axis for vertical navigation in the menu.
  - Press the joystick button (SW pin) to select a menu option.
  - Navigate between "Settings" and "Notifications" menus to adjust settings or monitor gas levels.

- **Adjusting Gas Sensitivity:**
  - Enter the "Settings" menu to adjust the gas sensitivity threshold.
  - Turn the potentiometer to set a new threshold value displayed on the LCD.

- **Monitoring Gas Levels:**
  - Enter the "Notifications" menu to continuously monitor current gas levels.
  - Gas levels are displayed on the LCD and sent over Bluetooth.

## Notes
- Ensure the Bluetooth module is paired with a receiving device (e.g., smartphone, PC) to view gas level data remotely.
- Customize the threshold values and menu options as per specific application requirements by modifying the code.
