# Self-Guided RC Boat Implementation Design

## Overview
This design creates a simple, durable, and cost-effective autonomous boat capable of navigating a 10-mile GPS route. It uses twin-hull (catamaran) design with PVC pipes for flotation, differential thrust for steering, and long-range LoRa communication for telemetry.

## 1. Hull Design
- **Configuration**: Catamaran (twin-hull) for stability
- **Materials**: 4" diameter PVC pipe (2 x 24" lengths)
- **Frame**: 1/4" waterproof plywood connecting the hulls (12" x 18")
- **Electronics Housing**: Waterproof plastic container (6" x 4" x 2.5")
  - [Waterproof Box with Clear Lid](https://www.amazon.com/Waterproof-Plastic-Electric-Project-Junction/dp/B07RMNBCST/) - $9.99

## 2. Propulsion System
- **Motors**: 2x DNYSYSJ Brushless Motors (as specified) - $40.00
  - Mounted on the rear of each hull using 3D printed mounts
- **ESCs**: 2x HobbyWing QuicRun 30A Waterproof ESC - $24.98
  - [HobbyWing ESC](https://www.amazon.com/Hobbywing-QuicRun-Waterproof-Brushed-Electronic/dp/B0765PH4ZR/) - $12.49 each
- **Motor Mounts**: 3D printed PLA with waterproofing (design provided separately)

## 3. Navigation System
- **Main Controller**: ESP32 with built-in WiFi/Bluetooth - $8.99
  - [ESP32 Development Board](https://www.amazon.com/ESP32-WROOM-32-Development-Microcontroller-Integrated-Compatible/dp/B08D5ZD528/) 
- **GPS Module**: NEO-6M GPS Module - $12.99
  - [Diymall NEO-6M GPS Module](https://www.amazon.com/Diymall-NEO-6M-Module-Arduino-Helicopter/dp/B01H5FNA4K/)
  - Accuracy: ±2.5m
  - Update rate: 1Hz (sufficient for slow-moving boat)
- **Compass/IMU**: GY-91 MPU9250 + BMP280 10DOF Module - $9.99
  - [GY-91 Sensor Module](https://www.amazon.com/HiLetgo-MPU9250-Compass-Acceleration-Gyroscope/dp/B01I1J0Z7Y/)
  - For heading information between waypoints

## 4. Communication System
- **Primary Long-Range**: LoRa SX1276 433MHz Module - $19.99
  - [LoRa SX1276 433MHz](https://www.amazon.com/MakerFocus-Development-Transmission-Reception-Antenna/dp/B078W63CPG/)
  - Range: 10+ miles line-of-sight
  - Data rate: ~5kbps (sufficient for telemetry)
- **Base Station**: Identical LoRa module with USB-TTL converter for laptop connection
- **Antenna**: 433MHz Whip Antenna, 3dBi gain, 17cm length

## 5. Power System
- **Battery**: 3S 5200mAh 11.1V LiPo Battery - $29.99
  - [Zeee 11.1V 5200mAh LiPo Battery](https://www.amazon.com/Zeee-5200mAh-Connector-Helicopter-Airplane/dp/B08696W3JG/)
  - Runtime: ~3 hours at average cruising speed
  - Capacity sufficient for 10+ miles range
- **Battery Monitor**: Low voltage alarm with display - $7.99
  - [LiPo Battery Monitor](https://www.amazon.com/PACK-Battery-Voltage-Tester-Checker/dp/B07Y7ZQ6KQ/)

## 6. Control System
- **RC Backup Control**: FlySky FS-i6 2.4GHz 6-Channel Transmitter/Receiver - Optional addition, not in initial budget
- **Manual Control Range**: ~300 meters (with standard RC system when added later)
- **Autonomous Control**: 100% via pre-programmed waypoints

## 7. Software Architecture
- **Platform**: Arduino framework on ESP32
- **Navigation Logic**:
  - Simple PID controller for heading correction
  - Waypoint following with 5m acceptance radius
  - Differential thrust control for steering
- **Telemetry Protocol**: Custom lightweight protocol over LoRa:
  - GPS coordinates (12 bytes)
  - Battery voltage (2 bytes)
  - System status (1 byte)
  - Current waypoint (1 byte)

## 8. Assembly Details
- **Hull Separation**: 12" center-to-center
- **Overall Dimensions**: 24" length x 16" width x 8" height
- **Weight**: Approximately 2.5kg fully assembled
- **Waterproofing**: Marine silicone sealant for all through-hull connections
- **Motor Depth**: Motors positioned with propellers 2" below waterline

## 9. Cost Breakdown
- Motors (2x): $40.00
- ESCs (2x): $24.98
- ESP32 Controller: $8.99
- GPS Module: $12.99
- IMU/Compass: $9.99
- LoRa Communication: $19.99
- Battery: $29.99
- Waterproof Box: $9.99
- PVC Pipe & Plywood: ~$10.00
- Misc Hardware: ~$8.00
- **Total**: $174.93

## 10. Optional Components (Within Budget Constraints)
- **Hull Material Alternative**: 3" PVC instead of 4" to save weight (-$5)
- **Motor Alternative**: Single motor with rudder system instead of differential thrust (-$20)
- **Power Alternative**: USB Power Bank with voltage step-up (-$10)
- **Communication Alternative**: Basic NRF24L01+ modules with range extender for shorter range testing (-$15)

With these optimizations, the total cost could be reduced to approximately $125.

## 11. Performance Expectations
- **Max Speed**: ~3-4 knots (1.5-2 m/s)
- **Range**: 10+ miles on full battery
- **Navigation Accuracy**: Within 5m of waypoints
- **Communication Update Rate**: Every 30 seconds (configurable)

## 12. Future Expansion
- **Camera Mount**: 3D printed mount on center platform
- **Solar Charging**: Small solar panel for extended operation
- **Water Quality Sensors**: Expansion port on ESP32 available for I2C sensors 