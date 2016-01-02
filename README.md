# Magnometer-based joint orientation

For VR, having small elbow-bands and wristbands for rotation sensing is enough to determine basicorientation.

Magnetometers are low-power, low-drift, and have the precision and accuracy needed for arm orientation.

This plan is to use these concurrently with visual methods, so they can step in for situations where obstacles prevent direct visual determination of body-orientation.

# Materials

* magnetometer - HMC5883L via a GY271 module
* mcu - bluetooth enabled
* basic pcb and energy source

# Code

This repo contains some simple .ino code for prototyping the device.
