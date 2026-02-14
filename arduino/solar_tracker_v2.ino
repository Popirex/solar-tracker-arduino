/*
 * Solar Tracker - Single Axis
 * 
 * Automatically adjusts solar panel angle to follow the sun using light sensors.
 * Uses two photoresistors to detect light intensity difference and moves
 * a servo motor to maximize panel exposure.
 * 
 * Hardware:
 * - Arduino Uno
 * - 2x Photoresistors (LDR)
 * - 1x Servo motor (0-90 degrees)
 * - 2x 10kΩ resistors (voltage divider for sensors)
 * 
 * Pin Configuration:
 * - A0: Left photoresistor
 * - A2: Right photoresistor
 * - D6: Servo control
 */

#include <Servo.h>

// Pin definitions
#define SENSOR_LEFT   A0
#define SENSOR_RIGHT  A2
#define SERVO_PIN     6

// Sensor calibration
#define SENSOR_SCALE       50    // Reduce ADC resolution (1024 -> ~20)
#define SENSOR_RIGHT_OFFSET 5    // Calibration offset for right sensor
#define MOVEMENT_THRESHOLD  2    // Minimum difference to trigger movement

// Servo limits
#define SERVO_MIN  0
#define SERVO_MAX  90
#define SERVO_START 45   // Starting position (center)

// Timing
#define CHECK_INTERVAL 100  // ms between sensor checks

// Global variables
Servo servo;
int current_angle = SERVO_START;

// Sensor readings (for averaging)
int prev_left = 0, prev_right = 0;
int curr_left = 0, curr_right = 0;


void setup() {
    // Initialize serial for debugging
    Serial.begin(9600);
    Serial.println("Solar Tracker Initializing...");
    
    // Configure pins
    pinMode(SENSOR_LEFT, INPUT);
    pinMode(SENSOR_RIGHT, INPUT);
    
    // Attach and calibrate servo
    servo.attach(SERVO_PIN);
    calibrateServo();
    
    Serial.println("Ready!");
}


void loop() {
    // Read and average sensor values
    readSensors();
    int avg_left = (prev_left + curr_left) / 2;
    int avg_right = (prev_right + curr_right) / 2;
    
    // Calculate difference
    int difference = avg_left - avg_right;
    
    // Debug output
    Serial.print("Left: ");
    Serial.print(avg_left);
    Serial.print(" | Right: ");
    Serial.print(avg_right);
    Serial.print(" | Angle: ");
    Serial.print(current_angle);
    Serial.print(" | Diff: ");
    Serial.println(difference);
    
    // Only move if difference exceeds threshold
    if (abs(difference) > MOVEMENT_THRESHOLD) {
        adjustAngle(difference);
    }
    
    delay(CHECK_INTERVAL);
}


/**
 * Read sensor values and update history
 */
void readSensors() {
    // Store previous readings
    prev_left = curr_left;
    prev_right = curr_right;
    
    // Read new values with scaling
    curr_left = analogRead(SENSOR_LEFT) / SENSOR_SCALE;
    curr_right = (analogRead(SENSOR_RIGHT) - SENSOR_RIGHT_OFFSET) / SENSOR_SCALE;
}


/**
 * Adjust servo angle based on light difference
 * @param difference: positive = left brighter, negative = right brighter
 */
void adjustAngle(int difference) {
    if (difference > 0 && current_angle > SERVO_MIN) {
        // Left sensor brighter -> rotate left (decrease angle)
        current_angle--;
        servo.write(current_angle);
    }
    else if (difference < 0 && current_angle < SERVO_MAX) {
        // Right sensor brighter -> rotate right (increase angle)
        current_angle++;
        servo.write(current_angle);
    }
}


/**
 * Calibrate servo on startup
 * Sweeps through full range to verify functionality
 */
void calibrateServo() {
    Serial.println("Calibrating servo...");
    
    // Test minimum position
    servo.write(SERVO_MIN);
    delay(500);
    
    // Test maximum position
    servo.write(SERVO_MAX);
    delay(500);
    
    // Return to starting position
    servo.write(SERVO_START);
    delay(500);
    
    Serial.println("Calibration complete");
}
