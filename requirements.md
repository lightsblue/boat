## ⚙️ Design Principles

- **Simplicity First**: Favor simple solutions over complex ones. Avoid unnecessary subsystems.
- **Time to build should be fast**: Favor simplicity also to optimize for time to build this out.
- **Reliable Commodity Parts**: Choose widely available, well-supported components with a track record of durability.
- **Cost Conscious**: Keep the overall cost low; consider creative materials (e.g. PVC pontoons for the hull).
- **Software-Leveraged**: Where possible, use software to reduce hardware complexity. Custom code is preferred over over-engineered hardware solutions.
- **Engineer-Friendly**: The project should be approachable and debuggable for a generalist software engineer comfortable in Python, Node.js, or similar.

## 🛥️ Self-Guided RC Boat — Requirements

### 1. Mission
- Autonomously travel a predefined GPS route of up to 10 miles
- Furthest point will be 5 miles away. From where I will be on the lake, at some points land that's up to 100ft in elevation off the surface of the lake will be in the way.
- No need for obstacle avoidance or real-time course corrections beyond GPS navigation
- Failsafe behavior - stop if GPS lost
- it will operate on a lake that's about 7mi long overall and has some islands
- max budget should be $100
- LATER possible additions - it should be possible to add a camera later if I decided to

### 2. Navigation
- Follow a sequence of GPS waypoints
- Maintain reasonable heading accuracy between points
- Basic manual operation should be possible when i'm in close proximity (can be sloppy - only for simple testing)
- There should be basic high latency communication between me and the boat - e.g. 30s ping of gps and battery level back to me
- Within 5m of waypoint is acceptable

### 3. Propulsion
- Use two independent motors for differential thrust steering
- Maintain consistent forward motion over long distance

### 4. Power
- Carry onboard power sufficient for at least 5 miles of operation
- Support for multi-hour continuous runtime

### 5. Telemetry (Optional)
- Low-bandwidth, long-range (≥10 miles) connection for:
  - Location updates
  - Basic system health (e.g. battery level)
  - Simple remote commands (e.g. stop/return)

### 6. Form Factor
- Parts of hull(s) or electronics enclosure, or other parts may be be custom 3D printed
- Compact, water-resistant design suitable for flatwater environments

# Parts that we'll work from
Since some parts are make or break, these will be fixed.
### Motor
- **Model**: DNYSYSJ Brushless Motor Underwater Thruster
- **Link**: [Amazon Link](https://www.amazon.com/DNYSYSJ-Brushless-Underwater-Thruster-Propeller/dp/B0B3J4CM9H/ref=sr_1_6?crid=1DUJ6560P1L1F&dib=eyJ2IjoiMSJ9.cSCgbRjYAkYqYru0KZvQkfGSR4QJpNoS0l1dPxNY_zRS1fzA1ROwOallx95HSLTVNKq3m2RPGEAhpBQzskeJAl1HusW-5cnARE7kFjcKTW4_0ISvuJIgTjQt3hjA5RtgjvTY2WYUrw8D0Jog-J-ezcZRZSisWwM-p7Sn-FN4-Zs52RuIKmHeJcVhNN90LiMSxx3uvmIoNIDO5O7cwdB5Hp7GN4DL_SZT7zhMvTBjun9pRMlLWay3WU3Smht8OPbAU1706fSacS69lfevVSXBOFnKCaQY5OZXDG5nZEE_dqo.cRxn2haDHBs9dYN9fsLQUX9mptjmGgjkuBsUtU2PLug&dib_tag=se&keywords=dc%2BBrushless%2BUnderwater%2BThruster&qid=1744845912&s=toys-and-games&sprefix=dc%2Bbrushless%2Bunderwater%2Bthruster%2Ctoys-and-games%2C74&sr=1-6&th=1)
- **Specifications**:
  - Voltage: 12V-24V
  - Power: 30-200W
  - KV Rating: 600KV
  - Material: 304 Stainless Steel Bearing + Aluminum Alloy
  - Propeller: 4-Blade Nylon, 60mm diameter
  - Total Length: 75mm
  - Price: $20.00 each (need 2)

### Controller
- **Model**: Wishiot ESP32 LoRa V3 Development Board
- **Link**: [Amazon Link](https://www.amazon.com/dp/B0D2DBRR6T)
- **Specifications**:
  - Microcontroller: ESP32-S3FN8 with dual-core Xtensa LX7 architecture
  - CPU Speed: Up to 240 MHz
  - RAM: 512 KB
  - Flash Memory: 8 MB
  - Connectivity: WiFi, LoRa, and BLE
  - Display: 0.96-inch OLED
  - Price: $24.98