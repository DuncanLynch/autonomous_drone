#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define PWM_FREQUENCY 50

namespace flight_controller {
    class Channel {
    private:
        uint8_t id;
    public:
        explicit Channel(uint8_t channel_id) : id(channel_id) {}
        uint8_t getId() const { return id; }
    };

    class Angle {
        private:
            short degree;
        public:
            explicit Angle(short deg) : degree(deg) {}

            short getDegree() const { return degree; }

            bool operator<(const Angle& other) const { return degree < other.degree; }
            bool operator>(const Angle& other) const { return degree > other.degree; }
    };

    class PWMDriver {
        private:
            Adafruit_PWMServoDriver pwm;
        public:
            PWMDriver();
            void begin();
            void setPWMFreq(float freq);
            void setPWM(uint8_t channel, uint16_t on, uint16_t off);
    };

    class Servo {
        private:
            Channel channel;
            PWMDriver* pwm;
            Angle current_angle;
            Angle MAX_ANGLE;
            Angle MIN_ANGLE;
        public:
            Servo(Channel ch, PWMDriver* driver, Angle min_angle = Angle(0), Angle max_angle = Angle(180));

            void setAngle(Angle angle);
            Angle getAngle() const { return current_angle; }
            bool operator<(const Servo& other) const { return current_angle < other.current_angle; }
            bool operator>(const Servo& other) const { return current_angle > other.current_angle; }
    };

} 
