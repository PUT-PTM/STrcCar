# Overview 
STrcCar is a project of remote controlled car, that uses sensor and bluetooth comunication to control direction and speed movements. It is built on STM32F407G microprocessor and smartphone application.
# Description 
We can remotedly control the car thanks to the application and via Bluetooth connection (USART). We can change speed and driving direction. We have 8 driving direction and hard stop button. The power supply  of STM32 board and engine is from powerbank. 
</br></br>
<b>Projects components:</b></br>
- STM32F407G DISCOVERY
- Pololu TB6612FNG
- Bluetooth 2.1 XM-15B 
- HC-SR04
- 2x engine

# Tools 
- CooCox 1.7.8, C </br>
- App Inventor 2, Scratch
# How to run 
 <b><i> Connection:</i></b> </br>
- <b>Pololu TB6612FNG</b> </br>
  VCC -> VDD </br>
  GND -> GND </br>
  STBY -> PA3 </br>
  PWMA -> PE5 </br>
  PWMB -> PE6 </br>
  AIN1 -> PA12 </br>
  AIN2 -> PA13 </br>
  BIN1 -> PA14 </br>
  BIN2 -> PA15 </br>
  VMOT -> USB </br>
  GND -> USB </br>
  AO1 -> e1 </br>
  AO2 -> e1 </br>
  BO1 -> e2 </br>
  BO2 -> e2 </br>
- <b>Bluetooth 2.1 XM-15B </b></br>
  VCC -> VDD </br>
  GND -> GND </br>
  TXD -> PC10 </br>
  RXD -> PC11 </br>
- <b>HC-SR04 </b></br>
  VCC -> 5V </br>
  GND -> GND </br>
  Echo -> PD0 </br>
  Trig -> PC1 </br>
# How to compile 
Clone project from repository, compile program and send to your board.
# Attributions 
https://stm32f4-discovery.net/2014/08/library-30-measure-distance-hc-sr04-stm32f4xx/
# License 
<a href="License">MIT</a> License
# Credits 
Bartosz Tyczyński</br>
The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.</br>
<b>Supervisor:</b> Tomasz Mańkowski
