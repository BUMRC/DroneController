#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Initialize motor control hardware (pins, PWM, etc.)
void initMotors();

// Set the speed for a given motor (motor id and speed value)
void setMotorSpeed(uint8_t motor, int speed);

#endif // MOTOR_CONTROL_H
