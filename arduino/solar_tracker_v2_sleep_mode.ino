/*
 * Solar Tracker v2.0 - With Adaptive Sleep Mode
 * 
 * Enhanced version with:
 * - Adaptive sleep intervals (more checks when active, less when stable)
 * - Night detection (no movement when dark)
 * - Smooth servo movements
 * - Comprehensive debug output
 */

#include <Servo.h>

// Pin definitions
#define SENSOR_LEFT   A0
#define SENSOR_RIGHT  A2
#define SERVO_PIN     6

// Sensor calibration
#define SENSOR_SCALE        50
#define SENSOR_RIGHT_OFFSET 5
#define MOVEMENT_THRESHOLD  3     // Higher threshold for sleep mode

// Light thresholds
#define MIN_LIGHT_LEVEL    5     // Below this = night time
#define STABLE_LIGHT_DIFF  1     // Difference considered "stable"

// Servo configuration
#define SERVO_MIN   0
#define SERVO_MAX   90
#define SERVO_START 45

// Timing configuration
#define ACTIVE_CHECK_INTERVAL  500    // ms when actively tracking
#define STABLE_CHECK_INTERVAL  5000   // ms when position is stable
#define NIGHT_CHECK_INTERVAL   30000  // ms when in night mode

// States
enum TrackerState {
    NIGHT_MODE,      // Too dark to track
    STABLE_MODE,     // Position stable, check infrequently
    ACTIVE_MODE      // Actively tracking
};

// Global variables
Servo servo;
int current_angle = SERVO_START;
TrackerState state = ACTIVE_MODE;
unsigned long last_check = 0;
int stable_count = 0;  // Consecutive stable readings

// Sensor readings
int prev_left = 0, prev_right = 0;
int curr_left = 0, curr_right = 0;


void setup() {
    Serial.begin(9600);
    Serial.println("=== Solar Tracker v2.0 ===");
    Serial.println("Features: Adaptive Sleep + Night Detection");
    
    pinMode(SENSOR_LEFT, INPUT);
    pinMode(SENSOR_RIGHT, INPUT);
    
    servo.attach(SERVO_PIN);
    calibrateServo();
    
    Serial.println("Ready!\n");
}


void loop() {
    unsigned long now = millis();
    unsigned long check_interval = getCheckInterval();
    
    // Only check sensors at appropriate interval
    if (now - last_check >= check_interval) {
        last_check = now;
        
        readSensors();
        int avg_left = (prev_left + curr_left) / 2;
        int avg_right = (prev_right + curr_right) / 2;
        int total_light = avg_left + avg_right;
        
        // Update state based on light conditions
        updateState(total_light, avg_left, avg_right);
        
        // Debug output
        printStatus(avg_left, avg_right, total_light);
        
        // Act based on current state
        switch(state) {
            case NIGHT_MODE:
                // Do nothing, just wait for sunrise
                break;
                
            case STABLE_MODE:
                // Check if still stable
                if (!isStable(avg_left, avg_right)) {
                    state = ACTIVE_MODE;
                    stable_count = 0;
                }
                break;
                
            case ACTIVE_MODE:
                // Actively track the light
                trackLight(avg_left, avg_right);
                break;
        }
    }
}


/**
 * Read sensors and update reading history
 */
void readSensors() {
    prev_left = curr_left;
    prev_right = curr_right;
    
    curr_left = analogRead(SENSOR_LEFT) / SENSOR_SCALE;
    curr_right = (analogRead(SENSOR_RIGHT) - SENSOR_RIGHT_OFFSET) / SENSOR_SCALE;
}


/**
 * Update tracker state based on light conditions
 */
void updateState(int total_light, int left, int right) {
    // Check for night
    if (total_light < MIN_LIGHT_LEVEL) {
        if (state != NIGHT_MODE) {
            Serial.println("\n>>> Entering NIGHT MODE <<<");
            state = NIGHT_MODE;
        }
        return;
    }
    
    // Exit night mode if light detected
    if (state == NIGHT_MODE && total_light >= MIN_LIGHT_LEVEL) {
        Serial.println("\n>>> Exiting NIGHT MODE -> ACTIVE <<<");
        state = ACTIVE_MODE;
        stable_count = 0;
        return;
    }
    
    // Check for stability (only in active mode)
    if (state == ACTIVE_MODE && isStable(left, right)) {
        stable_count++;
        if (stable_count >= 3) {  // 3 consecutive stable readings
            Serial.println("\n>>> Entering STABLE MODE <<<");
            state = STABLE_MODE;
        }
    } else {
        stable_count = 0;
    }
}


/**
 * Check if current position is stable
 */
bool isStable(int left, int right) {
    int diff = abs(left - right);
    return diff <= STABLE_LIGHT_DIFF;
}


/**
 * Track light by adjusting servo
 */
void trackLight(int left, int right) {
    int difference = left - right;
    
    if (abs(difference) > MOVEMENT_THRESHOLD) {
        int new_angle = current_angle;
        
        if (difference > 0 && current_angle > SERVO_MIN) {
            new_angle = current_angle - 1;
        }
        else if (difference < 0 && current_angle < SERVO_MAX) {
            new_angle = current_angle + 1;
        }
        
        if (new_angle != current_angle) {
            smoothMove(current_angle, new_angle);
            current_angle = new_angle;
            stable_count = 0;  // Reset stability counter
        }
    }
}


/**
 * Smooth servo movement between positions
 */
void smoothMove(int from, int to) {
    int step = (to > from) ? 1 : -1;
    
    for (int pos = from; pos != to; pos += step) {
        servo.write(pos);
        delay(15);  // Small delay for smooth motion
    }
    servo.write(to);
}


/**
 * Get appropriate check interval based on state
 */
unsigned long getCheckInterval() {
    switch(state) {
        case NIGHT_MODE:
            return NIGHT_CHECK_INTERVAL;
        case STABLE_MODE:
            return STABLE_CHECK_INTERVAL;
        case ACTIVE_MODE:
        default:
            return ACTIVE_CHECK_INTERVAL;
    }
}


/**
 * Print current status to serial
 */
void printStatus(int left, int right, int total) {
    const char* state_names[] = {"NIGHT", "STABLE", "ACTIVE"};
    
    Serial.print("[");
    Serial.print(state_names[state]);
    Serial.print("] L:");
    Serial.print(left);
    Serial.print(" R:");
    Serial.print(right);
    Serial.print(" T:");
    Serial.print(total);
    Serial.print(" Angle:");
    Serial.print(current_angle);
    Serial.print(" Stable:");
    Serial.println(stable_count);
}


/**
 * Calibrate servo on startup
 */
void calibrateServo() {
    Serial.println("Calibrating servo...");
    
    servo.write(SERVO_MIN);
    delay(500);
    servo.write(SERVO_MAX);
    delay(500);
    servo.write(SERVO_START);
    delay(500);
    
    Serial.println("Calibration complete");
}
