#include <Wire.h>
#include "flight_controller.hpp"

flight_controller::PWMDriver pwm;
flight_controller::Servo aileron_left(flight_controller::Channel(4), &pwm);
flight_controller::Servo aileron_right(flight_controller::Channel(5), &pwm);

void setup() {
    Wire.begin();
    pwm.begin();
    pwm.setPWMFreq(PWM_FREQUENCY);

    aileron_left.setAngle(flight_controller::Angle(90));
    aileron_right.setAngle(flight_controller::Angle(90));
}

void loop() {
    for (int angle = 0; angle <= 180; angle += 5) {
        aileron_left.setAngle(flight_controller::Angle(angle));
        aileron_right.setAngle(flight_controller::Angle(angle));
        delay(20);
    }
    for (int angle = 180; angle >= 0; angle -= 5) {
        aileron_left.setAngle(flight_controller::Angle(angle));
        aileron_right.setAngle(flight_controller::Angle(angle));
        delay(20);
    }
}
