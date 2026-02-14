# Bill of Materials (BOM)

Complete list of components needed to build the solar tracker project.

**Total Estimated Cost: ~€43**  
**Build Time: 4-5 hours** (including 3D printing)

---

##  Electronics Components

### Tracking System (Arduino-powered)

+---------------------------+----------+-----------------------------------+-------------------------------+----------+
| Component                 | Quantity | Specifications                    | Notes                         | Est. Cost|
+---------------------------+----------+-----------------------------------+-------------------------------+----------+
| **Arduino Uno Rev3**      | 1        | ATmega328P, 16MHz                 | Official or compatible        | €20.00   |
| **Prototype Shield**      | 1        | Compatible with Arduino Uno       | For clean PCB assembly        | €5.00    |
| **Servo Motor**           | 1        | SG90, 180° rotation, 5V           | Standard hobby servo          | €3.00    |
| **Photoresistor (LDR)**   | 2        | 5mm, light range 5-10kΩ           | GL5528 or similar             | €1.00    |
| **Resistor 10kΩ**         | 2        | 1/4W, ±5% tolerance               | For voltage dividers          | €0.50    |
| **USB Cable Type A-B**    | 1        | Standard Arduino cable            | Power + programming           | €3.00    |
| **Jumper Wires**          | ~15-20   | Male-Male / Male-Female           | Various colors                | €2.00    |
+---------------------------+----------+-----------------------------------+-------------------------------+----------+

**Subtotal: €34.50**

### Solar Panel Demonstration Circuit (Independent)

+---------------------------+----------+-----------------------------------+-------------------------------+----------+
| Component                 | Quantity | Specifications                    | Notes                         | Est. Cost|
+---------------------------+----------+-----------------------------------+-------------------------------+----------+
| **Small Solar Panel**     | 1        | 5V output, 100-200mA              | ~60x60mm size                 | €10.00   |
| **LED**                   | 1        | Red, 5mm, standard brightness     | Any red LED                  | €0.20    |
|**Resistor(current-limit)**| 1        | 220Ω, 1/4W                        | Protects LED                  | €0.10    |
| **Wire**                  | ~30cm    | 22-24 AWG                         | Panel → LED connection        | €0.50    |
+---------------------------+----------+-----------------------------------+-------------------------------+----------+

**Subtotal: €10.80**


---

## 3D Printed Components

+-------------------+---------------------------+----------+--------+------------+--------+----------+
| Part Name         | File                      | Material | Infill | Print Time | Weight | Est. Cost|
+-------------------+---------------------------+----------+--------+------------+--------+----------+
| **Base Platform** | Base-solare.stl           | PLA      | 20%    | ~2h        | 50g    | €1.00    |
| **Panel Support** | Supporto-pannello.stl     | PLA      | 20%    | ~1.5h      | 30g    | €0.60    |
+-------------------+---------------------------+----------+--------+------------+--------+----------+


**Print Settings:**
- Layer height: 0.2mm
- Nozzle temperature: 200-210°C (PLA)
- Bed temperature: 50-60°C
- Print speed: 50mm/s

**Subtotal: €1.60**

**Total filament needed: ~80g PLA**

---

##  Tools & Equipment Required

These tools are needed for assembly but not included in project cost:

### Essential Tools
-  **Soldering iron** (25-40W recommended)
-  **Solder** (lead-free or 60/40 tin-lead)
-  **Wire strippers**
-  **Diagonal cutters** (for trimming component leads)
-  **Screwdriver set** (Phillips and flat-head)
-  **Multimeter** (for testing connections)

### Nice to Have
- 🔹 **Helping hands** or PCB holder
- 🔹 **Hot glue gun** (for cable management)
- 🔹 **Flush cutters** (cleaner cuts on component leads)
- 🔹 **Tweezers** (handling small components)
- 🔹 **Desoldering pump** (fixing mistakes)

### 3D Printing
-  **3D Printer** (FDM type, 200x200mm min. build area)
-  **PLA Filament** (any color, ~80g needed)

---


## Shopping List Summary

**For quick ordering, here's a consolidated list:**

### From Electronics Supplier
- [ ] 1× Arduino Uno
- [ ] 1× Prototype shield for Uno
- [ ] 1× SG90 servo motor (or equivalent)
- [ ] 2× Photoresistor 5mm (LDR)
- [ ] 2× Resistor 10kΩ 1/4W
- [ ] 1× Resistor 220Ω 1/4W
- [ ] 1× Red LED 5mm
- [ ] 1× USB cable Type A-B
- [ ] 1× Pack of jumper wires

### From Solar/Hobby Supplier
- [ ] 1× Small solar panel (5V, 100-200mA)

### 3D Printing
- [ ] 80g PLA filament (any color)
- [ ] Print Base-solare.stl
- [ ] Print Supporto-pannello.stl

---

##  Important Notes

### Power Supply
The Arduino is powered via USB from a computer or 5V USB power adapter. The servo motor draws power from Arduino's 5V pin.

**Power consumption estimate:**
- Arduino Uno: ~50mA
- SG90 Servo (idle): ~10mA
- SG90 Servo (moving): ~100-200mA peak
- Total: **~250mA maximum**

Any USB port or 5V/1A USB adapter can handle this comfortably.

### Solar Panel Sizing
The solar panel size is not critical—it only powers the demonstration LED. Any small 5V panel (50-500mA rating) will work. Larger panels will make the LED brighter but won't affect tracking functionality.

### LDR Sensitivity
Photoresistors work well with both artificial light (desk lamps) and sunlight. For outdoor use in direct sunlight, you may need to increase the `SENSOR_SCALE` constant in the code to reduce sensitivity.

---

