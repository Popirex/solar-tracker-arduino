# Solar Tracker - Improvements & Future Development

Technical improvements and planned enhancements for the solar tracker project.

---

## Code Evolution

**v1.0 - Original Prototype**
- Basic light comparison algorithm
- Two-sample moving average for noise reduction
- Continuous operation
- Successfully proved tracking concept

**v2.0 - Refactored**
- Clear variable naming and documentation
- Configurable constants (no magic numbers)
- Movement threshold to reduce jitter
- 100ms delay between checks
- Function-based structure

**v2.0+ Sleep Mode**
- Three operating states (NIGHT/STABLE/ACTIVE)
- Adaptive check intervals (30s to 500ms)
- Night detection for power savings
- Smooth servo movements
- Comprehensive debug output

---

## Problems Identified in v1.0

**Jittery Movement**
No delay between checks caused servo to react to every minor fluctuation, creating rapid jerky movements.

Solution: Added movement threshold and 100ms delay between sensor readings.

**Magic Numbers**
Hard-coded values like `/50` and `-5` weren't documented, I added them because it made the sensors reading more accurate.

Solution: Defined constants with clear names and comments explaining purpose.

**Poor Variable Names**
Variables like `val_1_sens_1` were confusing.

Solution: Changed to descriptive names like `prev_left`, `curr_right`, `avg_left`.

**No Power Optimization**
System ran continuously regardless of conditions.

Solution: Implemented state machine with adaptive check intervals based on conditions.

---

## Key Improvements Implemented

**Movement Threshold**
Only adjusts position if light difference exceeds minimum threshold, eliminating micro-movements.

**Adaptive Sleep**
- Active mode: Check every 500ms when tracking
- Stable mode: Check every 5s when position is good
- Night mode: Check every 30s when dark

**Smooth Movements**
Gradual position changes instead of instant jumps reduce mechanical stress and look more natural.

**Night Detection**
Automatically stops tracking when ambient light drops below threshold, saving power.


---

## Design Notes

**Why Photoresistors?**
Simple, self-correcting, and perfect for demonstration. Calculated tracking would be better for production but less engaging educationally.

**Why State Machine?**
Clear behavior definition, easy debugging, extensible for new features.

**Mechanical Lessons**
3D printed parts work well for small panels. Scaled version would need metal frame and linear actuators.

---

## Conclusion

The evolution from v1.0 to v2.0+ demonstrates iterative development: start simple, identify limitations, improve systematically. The working prototype proved the concept; the refined versions make it reliable, efficient, and production-ready.

---

**Last Updated:** February 2026