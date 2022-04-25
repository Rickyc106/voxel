# Welcome to Voxel!

If you arrived here expecting to see something related to computer graphics, then sorry to disappoint...

...But in the off chance you're intrigued by balancing cubes, you're in the right place!

# Background

A while back I stumbled across this research project video, dubbed Cubli:

[![Cubli Project](http://img.youtube.com/vi/n_6p-1J551Y/hqdefault.jpg)](https://www.youtube.com/watch?v=n_6p-1J551Y)

Now while this robot isn't exactly _new_ by any means...
* [Cubli original design](https://www.wevolver.com/wevolver.staff/cubli#:~:text=The%20Cubli%20is%20a%20one,the%20Cubli%20to%20jump%20up)
* [Cubli using quaternions](https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=9524577)

I did want to see if I could recreate such a robot with relatively inexpensive off-the-shelf components and more importantly, simple controllers.

Do you really need fancy quaternion math to keep a cube stable on its vertex? Can this project be built with a basic PID controller and a bunch of "BS" gains? That's what we're here to find out!

# Project Goals

:grey_exclamation: **Low Cost:** 3D printed frame, gimbal motors (maybe?), steel rings as reaction wheels, etc.

:grey_exclamation: **Basic Math:** Since I was never good at it to begin with :P

:heavy_check_mark: **Open Source:** In case anyone else wanted to contribute

:heavy_check_mark: **Looks DANK:** A must for any robot these days

# Hardware Overview

<img src=https://user-images.githubusercontent.com/15114673/165002022-69e958a0-5319-45f0-a082-ec386f60e09a.png width="698" height="720"/>

Shown above is a current prototype CAD model, excluding batteries, sensors, MCU and a LOT more but gives a rough approximation for what an end product may look like at the moment.

Dimensions: 150mm x 150mm x 150mm

Mass: TBD

Total Cost: TBD

### Hardware To-Do

- [ ] CAD models for missing components
- [ ] Reaction wheel braking mechanism
- [ ] Mounting hardware for electronics
- [ ] NRF24L01 transceiver
- [ ] Dead man switch / Safety On-Off switch

# Software Overview

This project heavily relies on [platformIO](https://platformio.org/) to compile, build and flash Arduino-like microprocessor boards. Personally I will be testing [ESP32 Dev Boards](https://www.espressif.com/en/products/socs/esp32) and [Adafruit Feather M4 CAN Express](https://www.adafruit.com/product/4759) as that is what I have on hand but support for other boards may be added in the future.

### Library Dependencies
* Adafruit_BuisIO
* Adafruit_FXAS21002C
* Adafruit_FXOS8700
* Adafruit_Sensor

### Software To-Do

- [ ] IMU sensor fusion testing / tuning
- [ ] Single-axis motor + reaction wheel testing
- [ ] NRF24L01 transceiver drivers
- [ ] Steady-state torque control analysis
