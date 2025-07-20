#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "flight_controller.hpp"

#define SERVOMIN  150 
#define SERVOMAX  600

namespace flight_controller {
    PWMDriver::PWMDriver() : pwm(Adafruit_PWMServoDriver()) {}

    void PWMDriver::begin() {
        pwm.begin();
    }

    void PWMDriver::setPWMFreq(float freq) {
        pwm.setPWMFreq(freq);
    }

    void PWMDriver::setPWM(uint8_t channel, uint16_t on, uint16_t off) {
        pwm.setPWM(channel, on, off);
    }
    Servo::Servo(Channel ch, PWMDriver* driver, Angle min_angle, Angle max_angle)
        : channel(ch), pwm(driver), MIN_ANGLE(min_angle), MAX_ANGLE(max_angle), current_angle(min_angle) {}

    void Servo::setAngle(Angle angle) {
        short deg = angle.getDegree();

        if (deg < MIN_ANGLE.getDegree())
            deg = MIN_ANGLE.getDegree();
        if (deg > MAX_ANGLE.getDegree())
            deg = MAX_ANGLE.getDegree();

        current_angle = Angle(deg);

        uint16_t pulse = map(deg, 0, 180, SERVOMIN, SERVOMAX);
        pwm->setPWM(channel.getId(), 0, pulse);
    }

}
