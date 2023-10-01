The function of each sensor module and it's relation to the program
====

Ultrasonic Sensor Module: Interfaces with the front ultrasonic sensors to detect obstacles and determine distances from the front.

Side Ultrasonic Sensor Module: Interfaces with ultrasonic sensors on the left and right sides to measure distances from walls and avoid collisions.

Gyro Sensor Module: Interfaces with the gyro sensor to ensure accurate movement, enabling straight-line motion or specific angular adjustments.

Motor Control Module: Controls the movement and steering motors based on inputs from the ultrasonic and gyro sensor modules.

Camera: The HuskyLens AI camera module, integral to the robot's navigation system, discerns two specific obstacles: a red pillar and a green pillar. The identification of the red pillar prompts a right turn, while detection of the green pillar results in a left turn. This procedure, enabled by the HuskyLens' advanced color recognition algorithm, ensures efficient navigation through the operational environment, illustrating the camera's critical role in the robot's decision-making process.

To build/compile/upload the code to the vehicle's controllers:

Compilation: Use a suitable integrated development environment (IDE) or toolchain compatible with the microcontroller onboard the vehicle. Compile the code, ensuring it's free of errors and optimized for the platform.

Upload: Utilize the appropriate communication protocol (e.g., UART, USB, Bluetooth) to upload the compiled code to the vehicle's microcontroller, ensuring a secure and reliable transfer.

Execution: Once uploaded, initiate the execution of the code on the vehicle's controllers, enabling the electromechanical components to function as intended based on the sensor inputs and programmed logic.
