# HMC5883l-based joint orientation

For VR, having small elbow-bands and wristbands for rotation sensing is enough to determine basicorientation.

Magnetometers are low-power, low-drift, and have the precision and accuracy needed for arm orientation.

This plan is to use these concurrently with visual methods, so they can step in, in situations where obstacles prevent direct visual determination of body-orientation.

# Materials

* magnetometer
* mcu bluetooth enabled
* basic pcb and energy source

# Code

this repo contains simple Arduino-AVR code for prototyping the device.
