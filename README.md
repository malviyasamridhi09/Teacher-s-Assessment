# Booth's Algorithm in C++

## Overview
Booth's Algorithm is an efficient method for multiplying **signed integers** in binary using **Two’s Complement**. It eliminates the need for multiple addition or subtraction operations, making it useful for **low-level arithmetic computations**.

## Features
- Supports **positive and negative numbers**.
- Uses **Two’s Complement** for signed number representation.
- Performs **Arithmetic Right Shift** for correct bit manipulation.
- Produces **accurate results** for integer multiplication.

## How It Works
1. Convert the multiplicand and multiplier into binary (Two’s Complement if negative).
2. Initialize registers (**A, Q, Q-1**) and the iteration counter.
3. Perform the following for `n` cycles:
   - If `Q0 Q-1` is `10`, subtract M from A.
   - If `Q0 Q-1` is `01`, add M to A.
   - Perform **Arithmetic Right Shift** on (A, Q, Q-1).
4. After `n` cycles, the result is stored in **(A, Q)** and converted to decimal.

## Applications
- **Computer Architecture**: Used in ALUs for multiplication.
- **Embedded Systems**: Efficient multiplication in low-power devices.
- **Digital Signal Processing (DSP)**: High-speed calculations in signal processing.

## Usage
- Enter the **multiplicand and multiplier** as input.
- The program outputs the **correct product**.

---
🚀 **Efficient and Accurate Signed Multiplication using Booth's Algorithm!**

