# 🧩 Two-Player Maze Race Game (Raspberry Pi Pico)

A real-time two-player racing game using **Raspberry Pi Picos**, 8x8 LED matrices, and UART serial communication. Players navigate a maze with a joystick and race to reach the finish tile first. The game includes visual feedback via LEDs, matrix animations, and a synchronized start protocol.

---

## 🎮 Features

- 🕹️ Real-time movement using analog joystick input
- 📡 UART-based communication between two Pi Picos
- 🧠 Multiple maze layouts with wall detection
- ⏳ LED countdown before game begins (3–2–1)
- 🏁 Win detection with green/red LED blinking feedback
- 💡 Player tile blinking for visibility
- 🔁 Visual arrow animation when idle or post-game

---

## 🧱 Hardware Components

- 2x **Raspberry Pi Pico** boards
- 2x **8x8 LED Matrix displays** (with row/column pin control)
- 2x **Analog Joysticks** (with built-in pushbutton)
- 2x **Momentary pushbuttons** (for game start)
- 2x Sets of **Red, Yellow, and Green LEDs** (status indicators)
- Breadboards, jumper wires, resistors
- **TX/RX (UART)** connections between the two Picos

---

## ⚙️ System Overview

Each Pico independently:
- Handles joystick input and maze logic
- Displays the player and maze on the LED matrix
- Exchanges status signals over UART
- Shows win/loss screens with LED blinking

> Game starts only when both players press the start button. A UART handshake ensures both boards begin simultaneously.

---

## 🧠 How It Works

1. Player selects a maze using the joystick button.
2. Both press the start button → devices exchange READY/GO over UART.
3. Countdown displays: 3, 2, 1.
4. Players race to the maze’s goal tile.
5. First player to reach the goal sends "WIN" over UART.
6. Winner sees blinking green LED and a win screen; loser sees red LED and a loss screen.
