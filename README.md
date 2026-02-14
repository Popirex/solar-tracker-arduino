# Solar Tracker Arduino

A single-axis solar tracker that automatically follows the sun using photoresistors and a servo motor. Features real-time visual efficiency demonstration through an LED brightness indicator powered directly by the solar panel.

![Solar Tracker](media/photos/second-foto.jpeg)

---

## Demo Videos

Watch the tracker in action:
- **[Tracking Demonstration](media/videos/big-light-video.mp4)** - See how the system follows light sources

**Key observation:** The red LED brightness directly correlates with solar panel power output, providing immediate visual proof of tracking effectiveness.

---

## Project Overview

This project emerged from a simple question: *"Why do solar panels stay fixed when the sun moves across the sky?"*

I built this tracker to explore and demonstrate solar panel efficiency optimization through active sun tracking. The system continuously adjusts the panel angle to maintain optimal positioning as the light source moves.

### Why This Matters

Fixed solar panels lose significant efficiency throughout the day. Studies show that single-axis trackers can increase energy capture by:
- **25-35%** in mid-latitude regions  
- Up to **45%** near the equator

This project doesn't just track the sun—it **visually demonstrates** the efficiency gain through an LED powered directly by the solar panel.

---

## Key Features

-  **Automatic sun tracking** using dual photoresistor light detection
-  **Single-axis movement** (horizontal/azimuth tracking)  
-  **Real-time efficiency visualization** via solar-powered LED indicator
-  **Custom 3D-printed mounting structure** designed from scratch
-  **Three code versions** showing iterative improvements from prototype to production-ready

---

## How It Works

### Tracking System

The tracker uses a simple but effective algorithm:

1. **Two photoresistors** continuously compare light intensity (left vs right)
2. **Arduino** calculates which direction receives more light
3. **Servo motor** adjusts panel angle toward the brighter side
4. **Process repeats** until panel directly faces the light source

The system uses a moving average filter to reduce sensor noise and prevent jittery movements.

### Efficiency Demonstration

This is where the project gets interesting: the solar panel is connected directly to a **red LED** (with current-limiting resistor), creating a completely isolated circuit from the Arduino.

**LED brightness = Real-time power generation indicator**

- Misaligned panel → Dim LED (poor efficiency)
- Optimal alignment → Bright LED (maximum efficiency)

This provides immediate, visual proof of how much tracking improves energy capture. Anyone watching can instantly see the benefit—no graphs or data loggers needed.

---

## Hardware Components

### Tracking System
|     Component    | Quantity |      Specifications     | Est. Cost |
|------------------|----------|-------------------------|-----------|
| Arduino Uno      |     1    | ATmega328P              | €20       |
| Prototype Shield |     1    | For Arduino Uno         | €5        |
| Servo Motor      |     1    | SG90 (0-90° rotation)   | €3        |
| Photoresistor    |     2    | 5mm, 5-10kΩ range       | €1        |
| Resistor 10kΩ    |     2    | 1/4W (voltage dividers) | €0.50     |
| USB Cable        |     1    | Type A to B             | €3        |

### Solar Demonstration Circuit  
| Component   | Quantity |       Specifications     | Est. Cost |
|-------------|----------|--------------------------|-----------|
| Solar Panel | 1        | 5V, ~100mA (small)       | €10       |
| Red LED     | 1        | 5mm                      | €0.20     |
| Resistor    | 1        | ~220Ω (current limiting) | €0.10     |

### Mechanical Structure
|   Component   | Material | Print Time | Filament |
|---------------|----------|------------|----------|
| Base platform | PLA      | ~2h        | 50g      |
| Panel support | PLA      | ~1.5h      | 30g      |

**Total Project Cost: ~€43**  
**Build Time: 4-5 hours** (including 3D printing)

**Full component details:** [Bill of Materials](hardware/pcb/bill_of_materials.md)

---

## Code Versions

This repository includes **three versions** of the tracking code, documenting the evolution from working prototype to production-ready system.

### Original Prototype (v1.0)
`arduino/solar_tracker_original.ino`

The initial working code that successfully proved the concept.

**Characteristics:**
- Simple light comparison algorithm
- Two-sample moving average for noise reduction  
- Continuous sensor polling
- Functional and effective for proof-of-concept

**Known limitations:**
- Can appear jittery in rapidly changing light conditions
- No power optimization (constantly active)
- Hard-coded "magic numbers" without documentation ( helped stabilize the sensors readings, fuond in testing)

### Refactored Version (v2.0)
`arduino/solar_tracker_v2.ino`

Improved version maintaining the same functionality with professional code structure.

**Improvements over original:**
-  Clear variable naming and comprehensive comments
-  Configurable constants (no magic numbers)
-  Movement threshold to prevent micro-adjustments
-  100ms delay between sensor checks (reduces jitter)
-  Serial debug output for monitoring
-  Function-based structure for easier maintenance

**Use this if:** You want reliable tracking with clean, understandable code.

### Advanced with Sleep Mode (v2.0+)
`arduino/solar_tracker_v2_sleep_mode.ino`

Production-ready version with adaptive behavior and power optimization.

**New features:**
- **Three operating modes:**
  - `NIGHT_MODE` - Too dark to track (checks every 30s)
  - `STABLE_MODE` - Position optimal (checks every 5s)  
  - `ACTIVE_MODE` - Actively tracking (checks every 500ms)
- **Adaptive check intervals** - More responsive when needed, power-efficient when stable
- **Automatic night detection** - Stops tracking when ambient light drops below threshold
- **Smooth servo movements** - Gradual position changes reduce mechanical stress
- **Comprehensive monitoring** - Detailed serial output with state transitions

**Use this if:** You want professional-grade tracking with intelligent power management.

 **Detailed improvement analysis:** [docs/improvements.md](docs/improvements.md)

---

## Circuit Design

The system consists of two electrically isolated circuits:

**Circuit A: Arduino Control System** (USB powered)
- Two photoresistor voltage dividers → A0, A2
- Servo motor control → D6

**Circuit B: Solar Panel + LED** (Independent)
- Solar panel → Current-limiting resistor → LED
- Completely isolated from Arduino

**Full schematic:** [hardware/pcb/circuit-scheme.png](hardware/pcb/circuit-scheme.png)

### Circuit Assembly

The circuit was hand-soldered on an Arduino prototype shield without formal PCB design. This approach allowed for:
- Rapid prototyping and iterative testing
- Easy debugging and modifications during development  
- Short wire runs and minimal electromagnetic interference

Components were placed and connected based on the circuit schematic, with practical considerations for:
- Accessibility during troubleshooting
- Clean power distribution
- Proper sensor positioning

---

## 3D Printed Parts

All mechanical components were designed from scratch using CAD software on iPad with Apple Pencil.

 **STL files:** [hardware/3d-models/](hardware/3d-models/)

**Parts included:**
- `Base-solare.stl` - Main platform for Arduino and electronics mounting
- `Supporto-pannello.stl` - Panel bracket that attaches to servo

**Recommended print settings:**
- Material: PLA  
- Layer height: 0.2mm
- Infill: 20%
- Total print time: ~3.5 hours
- Total filament: ~80g

The design uses a simple single-axis gimbal mechanism, allowing smooth horizontal rotation while maintaining structural stability.

---

## Getting Started

### 1. Gather Components
Order or source all components listed in the [Bill of Materials](hardware/pcb/bill_of_materials.md).

### 2. 3D Print Mechanical Parts  
Print both STL files. Standard PLA settings work well.

### 3. Assemble Electronics
Follow the [circuit schematic](hardware/pcb/circuit-scheme.png) to wire components:
- Solder photoresistors with 10kΩ pull-down resistors to A0 and A2
- Connect servo signal wire to D6, power to 5V, ground to GND
- Solder LED with current-limiting resistor directly to solar panel wires

### 4. Mechanical Assembly
- Mount Arduino to base platform
- Attach servo motor securely to base
- Connect panel support to servo horn
- Mount solar panel to support bracket
- Position photoresistors to face the same direction as panel

### 5. Upload Code
1. Open `arduino/solar_tracker_v2.ino` (recommended for first use)
2. Select **Tools → Board → Arduino Uno**
3. Select correct COM port
4. Click **Upload**
5. Open **Serial Monitor** (9600 baud) to view tracking status

### 6. Calibration

The servo automatically calibrates on startup, sweeping through its range (0° → 90° → 45°).

If tracking seems too sensitive or too sluggish, adjust these constants:

```cpp
#define SENSOR_SCALE 50        // Lower = more sensitive
#define MOVEMENT_THRESHOLD 2   // Higher = less movement
```

For outdoor use with real sunlight, you may want to increase `SENSOR_SCALE` to 80-100 as direct sunlight is much brighter than indoor lamps.

---

## Performance & Results

### Observed Behavior
- LED brightness increases approximately **40%** when panel moves from misaligned to optimal position
- Smooth, stable tracking in consistent light conditions  
- Responsive to light source movement (tracks desk lamp or flashlight effectively)
- System finds optimal angle within 5-10 seconds after light source changes

### Testing Notes
Testing was primarily done indoors with desk lamps and flashlights. The photoresistors respond well to artificial light, making the system ideal for demonstrations and prototyping.

For outdoor deployment with actual sunlight, some parameter tuning may be necessary due to the much higher light intensity.

---

## Future Improvements

This project works well as a single-axis tracker, but there's room for enhancement:

### Short Term
- [ ] **Dual-axis tracking** - Add second servo for vertical (altitude) movement
- [ ] **Data logging** - Record panel position and light intensity over time  
- [ ] **Battery backup** - Add rechargeable battery for autonomous operation
- [ ] **Weatherproof enclosure** - Design for outdoor deployment

### Long Term  
- [ ] **GPS/RTC-based tracking** - Calculate sun position mathematically instead of using sensors
- [ ] **MPPT circuit integration** - Maximum Power Point Tracking for actual power generation
- [ ] **Scaled-up version** - Build full-size tracker for real energy production
- [ ] **Current/voltage sensing** - Quantify efficiency gains with precise measurements

 **Detailed enhancement plans:** [docs/improvements.md](docs/improvements.md)

---

## What I Learned

Building this project taught me valuable lessons across multiple domains:

### Technical Skills
- **Sensor integration and calibration** - Working with analog sensors, voltage dividers, and noise filtering
- **Servo motor control** - PWM signals, positioning, and mechanical constraints
- **3D CAD design** - Creating functional parts that integrate electronics and mechanics
- **Embedded programming** - State machines, timing, and real-time control systems

### Problem-Solving Approach
- **Iterative development** - Start simple, test, improve, repeat
- **Visual debugging** - Using the LED as both demo and diagnostic tool

### Most Important Lesson
How to identify problems in working systems and systematically improve them. The journey from v1.0 (jittery but functional) to v2.0+ (smooth and intelligent) taught me more than building it right the first time ever could.

---

## Why Document Three Code Versions?

You might wonder why I'm showing the "imperfect" original code alongside the improved versions.

**Because that's how real development works.**

The original code was good enough to prove the concept. It worked. It demonstrated the tracking principle and LED efficiency visualization effectively.

But looking back at it months later, I could see the limitations:
- Unclear variable names
- No documentation  
- Jittery movement
- Wasted power

Rather than hide the original and pretend I wrote perfect code from the start, I'm documenting the evolution.

If you're a student or beginner seeing this: your first version doesn't need to be perfect. It needs to **work**. Then you make it **better**.

---

## License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

**In short:** Feel free to use, modify, and share this design. If you build your own version, I'd love to see it! Credit appreciated but not required.

---

## Author

**Alessandro (Popirex)**  
Computer Science Student | Maker | Hardware + Software Enthusiast

I love building things that exist in the real world, not just on screens. From Arduino robots to web applications, I believe the best way to learn is by creating.

**Connect with me:**
-  Website: [popirex.github.io](https://popirex.github.io)
-  GitHub: [@Popirex](https://github.com/Popirex)  
-  Email: rossi04alessandro@gmail.com

---

## Acknowledgments

This project was inspired by curiosity about renewable energy and a desire to understand efficiency optimization through hands-on experimentation.

Thanks to the Arduino and maker communities for excellent documentation and support. Special appreciation to everyone who builds things and shares their knowledge online — you make learning accessible to everyone.

---

## Like This Project?

If you found this interesting, useful, or inspiring:
- **Star this repository** to show support
- **Share it** with others who might enjoy it  
- **Build your own version** and let me know how it goes!

Questions, suggestions, or just want to chat about Arduino projects? Open an issue or reach out directly. I'm always happy to discuss and help where I can.

---

**Built with curiosity, iteration, and a bit of trial and error.**
