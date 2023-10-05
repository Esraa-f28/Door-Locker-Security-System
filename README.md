# Door Locker Security System

## Introduction

This is a sophisticated Door Locker Security System project, utilizing two ATmega32 Microcontrollers operating at 8MHz. The system employs a layered architecture model with two distinct units: HMI_ECU (Human Machine Interface) and Control_ECU. Together, they create a robust security solution with the following features:

## System Sequence

### Step 1 – Create a System Password
- The system prompts the user with "Please Enter Password" on the 2x16 LCD.
- The user enters a 5-digit password, with each digit displayed as an asterisk (*).
- After the initial password entry, the system requests re-entry for confirmation.
- If the two entered passwords match, the system stores the password in EEPROM and proceeds to Step 2. If not, the user is prompted to repeat Step 1.

### Step 2 - Main Options
- The 2x16 LCD displays the main system options.

### Step 3 - Open Door (+)
- The LCD prompts the user to enter the password.
- Upon password entry, HMI_ECU sends it to Control_ECU for verification.
- If the passwords match:
  - The DC-Motor rotates clockwise for 15 seconds, displaying "Door is Unlocking" on the LCD.
  - The motor holds for 3 seconds.
  - The DC-Motor rotates counterclockwise for 15 seconds, displaying "Door is Locking" on the LCD.

### Step 4 - Change Password (-)
- The LCD prompts the user to enter the password.
- Upon password entry, HMI_ECU sends it to Control_ECU for comparison.
- If the passwords match, the system proceeds to Step 1 for password change.

### Step 5
- If the passwords do not match in Step 3 (+: Open Door) or Step 4 (-: Change Password):
  - The user is prompted once more for the password.
  - If the passwords match, the system either opens the door or proceeds to password change in Steps 3 and 4.
  - If the passwords are still unmatched, the following actions occur:
    - The Buzzer activates for 1 minute.
    - An error message is displayed on the LCD for 1 minute.
    - The system is locked, and keypad inputs are disabled during this time.
    - The system returns to Step 2, displaying the main options again.

## Driver Requirements

- GPIO Driver
- Keypad Driver
- LCD Driver (2x16)
- Timer Driver
- UART Driver
- I2C Driver
- EEPROM Driver
- Buzzer Driver
- DC-Motor Driver

## Microcontroller
- ATmega32


## Schematic
![image](https://github.com/Esraa-f28/Door-Locker-Security-System/assets/103899204/321bfe40-b42f-4df6-b73d-4e9af1418a08)
