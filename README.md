# arduino-police-car
Arduino sketch made as a school project for programming in Arduino. This library is controlling Arduino robotic car.

Here's what it looks like:

![police_car](police_car.JPG)

Here are the schematics:

![fritzing](arduino-police-car.png)

Unfortunately the schematics for car have different H-bridge, than we used in this project. The correct one should be: `L9110` but I did not found Fritzing part for this particular one.
So the corrections have to ba made in order for motors to work correctly:

The YELLOW wire now connected to IN1 should be connected to A1-B
The GREEN wire now connected to IN2 should be connected to A1-A
The ORANGE wire now connected to IN3 should be connected to B1-B
The BLUE wire now connected to IN4 should be connected to - B1-A

If the motors polarity isn't working correctly for you, try switching the wires controlloing the motors as well.

If someone has the fritzing part for L9110 H-bridge, pull requests are welcome.
