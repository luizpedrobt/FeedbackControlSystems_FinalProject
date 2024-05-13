This project was developed as part of the Feedback Control Systems Lab course during my undergraduate studies. It was a collaborative effort, carried out in pairs (@github/fcarvalhop), with the objective of designing a digital PID controller to regulate temperature within a controlled environment.

<div style="text-align: center;">
    <img src="https://github.com/luizpedrobt/FeedbackControlSystems_FinalProject/blob/main/images/8ec62bac-992b-421e-b064-076684428e57.jpeg" width="500">
</div>


The project entailed designing a PCB to integrate all the necessary circuits, which was accomplished using KiCad 7.0 software.

The core concept of the project was to utilize a diode as a temperature sensor. To achieve this, the diode was biased with a constant current source, allowing it to vary its voltage linearly in response to changes in ambient temperature. An analog-to-digital converter was then employed to sample the diode's voltage, with the sampled signal undergoing conditioning and filtering for accurate measurement.

We had the flexibility to choose any microcontroller unit (MCU) for implementing the controller. Therefore, my partner and I selected the STM32F411CEU6 blackpill development board. Initially, the project's prototype was developed using an Arduino UNO board.

The project's concept is straightforward: the MCU measures the temperature, compares it with a setpoint (default at 50°C but user-adjustable via Arduino serial communication), and generates a pulse-width modulation (PWM) signal with a duty cycle that varies based on the temperature-setpoint difference.

Both the heating and cooling systems are controlled by the MCU using a BJT (bipolar junction transistor), although alternative drivers like MOSFETs can also be used. For heating, we used three 33-ohm resistors in parallel (10 W each), resulting in an equivalent resistance of 11 ohms. The project operates at a current close to 1.1 A, assuming a 12 V power supply. A LM7805 regulator was used to power both the Arduino board and other low-power circuits on the PCB.

In conclusion, the project is perfectly working with the arduino, but it'll be implemented in the STM32 lately, star this repository if you don't want do lose any updates!😘
