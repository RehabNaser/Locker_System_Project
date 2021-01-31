# Locker_System_Project
An Embedded System Project using ATmega32 Microcontroller
## Main Function:
The main function is enabling the user to put the valuable things in a locker and put a password that isn't deleted even if the Micro-controller power is off.
## System consists of:
1. Buzzer.
2. Keypad.
3. LCD.
4. Microcontroller(Using ATmega32).
## Details:
1. **First** time the saved password is **0000**.
2. User should enter **0000** to open locker at the **first** time.
3. To **change** the password:
   * The locker must be **open**(And if the locker is **closed** already and you try to press on **B** button, The system will **reject** that action and output a **message** on the **LCD** to inform you).
   * The user should press on **B** button then enter the **new 4 digits** password.
      * If he entered **less** than 4 digits, The system will **reject** that password and output a **message** on the **LCD** to inform him that's password too **short**.
      * If he entered **more** than 4 digits, The system will **reject** that action before pressing on **B** button and output a **message** on the **LCD** to inform him that's password too **long**.
   * The user must press on **B** button **again** To **save** the new password.
   * The **Buzzer** will be **ON** for **3 second** then **OFF** once the user press on **B** button. 
4. **Pressing** on **any button** will make the **Buzzer ON** for **100msec**.
5. To **close** the locker:
   * The user should press only on **C** button.
   * And if the locker is **closed** already and he tries to press on **C** button, The system will **reject** that action and output a **message** on the **LCD** to inform him.
6. To **open** the locker:
   * The user should enter the **4 digits** password then press only on **D** button.
   * And if the locker is **open** already and you try to enter the password, The system will **reject** that action and output a **message** on the **LCD** to inform you.
   * If you enter a **wrong 4 digits**, The **buzzer** will be **ON** for **3 second** then **OFF**.
   * If you enter **less than 4 digits**, The system will **reject** that password and output a **message** on the **LCD** to inform you that's password too **short**.
   * If you enter **more than 4 digits**, The system will **reject** that action before pressing on **D** button and output a message on the **LCD** to inform you that's password too **long**.
7. To **reset** the password, If the user forgot it:
   * If the locker is **open**:
     * **Pressing** on **'0'** for **5 second**.
   * If the locker is **closed**:
     * The **developer** should **flash the software** again.
     * If the user **presses** on **'0'** button for **5 second**, The system will **reject** that action and output a **message** on the **LCD** to inform him).
