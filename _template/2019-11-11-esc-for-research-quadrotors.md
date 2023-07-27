---
layout: post
category: blog
title: Comparison of Quadrotor ESCs for autonomous flight
snippet: A comparison of ESC firmware, communication protocols and available models for building a quadrotor for precise motor control
tags: [robotics, hardware]
---
This work was done in collaboration with [Alex Spitzer](http://alexspitzer.com), who co-wrote this post.

-------------

There are a lot of available quadrotor ESCs available on the market.
However, when building your own quadrotor, you have to choose your ESCs carefully depending on if you're planning to fly RC or autonomously.
Many of the ESCs on the market are for RC hobbyists, which means that their functionality is limited when it comes to needs for autonomous flight.

In this post, we discuss different types of communication protocols, firmware, and some available ESCs.

### Communication Protocol

| Protocol | Digital/Serial | Latency                     | Discretization                              | Connector                                      | How to wire with ESCs                                       | How to wire with Flight Controller (FC)   |
|----------|----------------|-----------------------------|---------------------------------------------|------------------------------------------------|-------------------------------------------------------------|-----------------------|
| PWM      | Digital        |                             | 1000 possible throttle values (DShot: 2000) |                                                | Ground, signal, and 5 V to each ESC from FC                 |                       |
| CAN      | Digital        | Typical speed is 1 Mbit/s   | typically, 16bit integers or 32bit floats   | 3 pin: CANL, CANH, ground                      | CAN buses to each ESC in series with a terminating resistor | CANH and CANL to FC   |
| UART     | Serial        | fastest baud rate is 921600 |                                             | 6 FTDI pin (3 pins: TX, RX, GND actually used) | Individual TX, RX, GND to each ESC                          | TX, RX, and GND to FC |
| USB      | Digital        | fast?                       |                                             | Typically Micro USB                            |                                                             |                       |
| SPI      | Serial        | ?                           |                                             |                                                |                                                             |                       |
| I2C      | Serial         | ?                           |                                             |                                                |                                                             |                       |


Traditionally, ESCs receive input via [Pulse Width Modulation (PWM)](https://en.wikipedia.org/wiki/Pulse-width_modulation). PWM is a technique to vary the voltage from full power to zero continuously. The idea is that if you switch really quickly between full voltage and zero voltage, say given equal time to each, the receiving device will see that as "half voltage".

The switching frequency is typically every 2000 us (500 Hz) or 2500 us (400 Hz) for most quadrotor ESCs. Most modern ESCs however, take in the PWM signal and compute the length of the high pulse (STM32 Timers for PWM Output), in units of (integer) number of microseconds. ESCs (for a reason not entirely clear to me ATM - Alex) typically accept pulses between 900 us and 2000 us. This leaves about 1000 possible throttle values for the motor.

DShot attempts to remove the limitations of the above described PWM communication strategy (namely resolution and latency) by sending a number encoded as a digitial signal on the PWM line. AFAIK, DShot dedicates 11 bits to the throttle value, which results in 2048 possible throttle values. That's only* about a factor of 2 improvement on the original PWM strategy. Ideally, if the FC and ESC are connected via a UART (serial), USB, CAN, etc (any standard digital communication line), the FC can send e.g. 16 bit values (64K possible throttles) indicating the throttle value. The ESC will then ideally, read in this 16 bit value, and drive the throttle appropriately.

### Firmware

| Firmware | Open-source? | RPM mode? | Digital Interface? | Boards supporting                               | Developer              |
|----------|--------------|-----------|--------------------|-------------------------------------------------|------------------------|
| BLHeli32 | NO           | NO        | NO (DShot)         | Many FPV-geared ESCs                            | Steffen Skaug (sskaug) |
| Sapog    | YES          | YES       | YES                | Zubax Orel 20, Holybro Kotleta20                | PX4 / Zubax           |
| ESC32v3  | NO           | YES       | YES                | ESC32v3                                         | AutoQuad               |
| ESC32v2  | YES          | YES       | YES                | ESC32v2                                         | AutoQuad               |
| SimonK   | YES          | NO        | NO                 | ATMEL-based boards                              | SimonK                |
| KISS     | NO           | NO        | DShot 2000         | KISS                                            | Flyduino               |


If you're interested in directly modifying settings, you may be interested in one of the firmware that is open source. Since ESC32's have become less reliable to find, we are interested in the open source Sapog firmware.

### ESC comparison

| ESC                | Firmware          | Connection to FC        | Battery Eliminating Circuit (BEC) | Power (Continuous / Burst) | Current (C / B)    | Weight                              | Features|
|--------------------|-------------------|-------------------------|-----------------------------------|----------------------------|--------------------|-------------------------------------|---------------------------------------------------------------------------------|
| ESC32v2            | ESC32v2           | PWM, UART, CAN, SWD     | No                                |                            | 20 A / 50 A        |                                     | closed loop RPM                                                                       |
| ESC32v3            | ESC32v3           | PWM, UART, CAN          | No                                | 750 W / 1000 W             | 20 A (40 A) / 50 A | 5.7 g (single) 22.8 g (quad)        | closed loop RPM                                                                  |
| Zubax Orel 20      | Sapog             | PWM, CAN, debug / UART? | No                                | 350 W / 1000 W             | 20 A / 55 A        | 10 g (single) 40.0 g (quad)         | Regenerative braking*|
| Kotleta 20         | Sapog             | PWM, CAN, debug / UART? | No                                | 500 W / 1000 W             | 20 A / 55 A        | 8.8 g (single) 35.2 g (quad)        | Regenerative braking*, closed loop RPM|
| Lumenier BLHeli_32 | BLHeli32          | PWM                     | 2 A / 5 V                         |                            | 50 A / 55 A        | 20 g (quad channel)                 | Four channels in one                                                          |
| Aikon AK32         | BLHeli32          | PWM                     | ?                                 |                            | 35 A / 45 A        | 20 g (quad channel)                 | Four channels in one                                                             |
| Zubax Myxa         | Zubax proprietary | PWM, CAN, UART, USB     | Myxa B only                       | 850 W                      | 30 A / 50 A        | 26 g (single) 104.0 g (quad)        |                                                                                 |
| KISS 32A           | KISS proprietary  | PWM                     |                                   |                            | 32 A / 45 A        | 3.3 g (single) 13.2 g (quad)        | Regenerative braking|

*regenerative braking is when the ESC sends energy / current back to the battery when it needs to stop or slow down the motors. This has implications on electrical design / wiring because some components, power dist. boards cannot accept this reverse current. If an ESC uses regen. braking, it needs to have a direct connection to the LiPo battery and ONLY uses LiPo batteries, otherwise a power supply might get damaged when braking. 

## RC vs. Autonomous flight

For autonomous flight, the RPM commands can be exactly computed if the thrust-to-RPM curve is known.
However, many ESC firmware doesn't allow direct sending of RPM commands, which could affect the thrust output.
The ESCs for RC flights are less concerned about this, since the pilot is able to adjust the knobs as required to compensate.

The downside with any BLHeli32-based ESC, which is made for the RC hobbyists, is that it does not have closed loop RPM mode, nor does it support a digital control interface (only DShot).
