# NRF24 Transceiver

This repository provides Arduino code examples and instructions for building a wireless transmitter and receiver pair using NRF24L01 modules.

## About

The NRF24L01 is a widely used 2.4GHz wireless transceiver module, perfect for Arduino-based wireless communication projects. This repository contains easy-to-use sketches for both transmitter and receiver, wiring diagrams, and troubleshooting resources to help you set up reliable two-way wireless communication between two (or more) Arduino boards.

## Features

- Simple and clear transmitter and receiver code examples
- Step-by-step wiring instructions for various Arduino boards
- Tips for improving range and reliability
- Troubleshooting guide for common NRF24L01 issues

## Getting Started

### Hardware Required

- 2× Arduino (Uno, Nano, Mega, etc.)
- 2× NRF24L01 or NRF24L01+ modules
- Jumper wires
- Breadboards (optional)
- 3.3V power supply (recommended for NRF24L01)

### Wiring

For both Transmitter and Receiver modules:

- VCC → 3.3V (Do NOT use 5V)
- GND → GND
- CE  → Pin 9 (modifiable)
- CSN → Pin 10 (modifiable)
- SCK → Pin 13
- MOSI → Pin 11
- MISO → Pin 12

### Example Code

See the `/examples` folder for ready-to-upload Arduino sketches for both transmitter and receiver.

## Usage

1. Install the [RF24 library](https://github.com/nRF24/RF24) using the Arduino IDE Library Manager.
2. Connect the NRF24L01 modules to your Arduino boards as shown above.
3. Upload the Transmitter sketch to one Arduino and the Receiver sketch to the other.
4. Open the Serial Monitors for both boards to observe wireless communication in action.

## License

MIT License

---

Happy experimenting with wireless communication! 📡🤝📡
