/*
 * File Name: LOCKER_SYSTEM.h
 * Creation Date: 01/26/2021
 * Author: Rehab
 * Description: Header File for Locker System Project....
 */ 
 
#ifndef LOCKER_SYSTEM_H_
#define LOCKER_SYSTEM_H_

//FILES INCLUDING
#include <avr/interrupt.h>

#include "EEPROM.h"
#include "INTERRUPT.h"
#include "TIMER0.h"

#include "PASSWORD.h"

#include "LCD.h"
#include "BUZZER.h"
#include "KEYPAD.h"

//MACROS
#define PASSWORD_DIGITS_NUMBER 4

#define NOT_PRESSED 0
#define RELEASED 0
#define PRESSED 1

#define STOP 0
#define START 1

#define CLOSE 0
#define OPEN 1

#define CLEAR 0
#define WRITTEN 1

extern uint8 Keypad[4][4];

//FUNCTIONS PROTOTYPES
void LCDClean(void);
void LongPassword(void);
void ShortPassword(void);
void IsPasswordLong(uint8 PasswordlengthChecker);

#endif