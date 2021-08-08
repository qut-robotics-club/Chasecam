# QUT Robotics Club
This is the code and graphics for the **QUT Robotics Club** Chasecam Project created in 2021.

# Who Are We 
The **QUT Robotics Club** is a student run organisation dedicated to promoting robotics within the QUT community and supporting QUT students’ future in Robotics.

## Contributing to the Codebase
If you wish to change code and contribute to the website please use git properly.
 - Create a branch
 - Write code and comment properly
 - Commit code to your branch with a clear description as the commit message
 - Create a pull request with Ryan(bb3b191) as reviewer
 - If comments are made to be changed please ask how to rebase your commits to keep issues to a minimum

## To Do
 - [ ] Serial Communication for controller.ino
 - [ ] Create rccar.ino for control of the car via onboard teensy
 - [ ] Serial communication for visionservo.py (receiving commands from controller)
 - [ ] Incorporate manual mode into visionservo.py

 ## Other Files
- servorccar.ino: Shows how you can hard code a brushless motor RC car to move using an Arduino Uno
- servotestrccar.ino: Shows how you can control a brushless motor RC car to move using an Arduino Uno and two potentiometers
- xbeeblinktest.ino: Testing if teensy can receive serial commmands through an xbee
- xbeeblinktestsend.ino: Testing if teensy can send serial commmands through an xbee

## Hardware
On Car
- Chassis: https://bit.ly/3buwlee
- Brushless Motor and ESC Combo: https://bit.ly/3kYLCau 
- Car Servo: https://bit.ly/2PKVuZL  
- Battery: https://bit.ly/3ry7CLz 
- Pan Tilt Servo Rig: https://bit.ly/3ivr6P9
- Raspberry Pi 3b
- Teensy 3.2
- XBEE PRO S1
- Plus consumables
- Custom Power and Data PCB

On Controller:
- Teensy 3.2
- XBEE PRO S1
- Plus consumables
- Custom PCB

Controller for testing
- Off the shelf controller and receiver: https://bit.ly/2PKVuZL