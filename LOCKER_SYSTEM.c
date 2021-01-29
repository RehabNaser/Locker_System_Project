/*
 * File Name: LOCKER_SYSTEM.c
 * Creation Date: 01/26/2021
 * Author: Rehab
 * Description: C File for Locker System Project....
 */ 

#include "LOCKER_SYSTEM.h"

volatile uint8 Delay_100msFlag=STOP;
volatile uint8 Delay_3secFlag=STOP;
volatile uint8 Key_0_PressingTimeCalculateFlag=STOP;
volatile uint8 LCDStateFlag=CLEAR;

volatile uint32 OverflowCounterForKey_0=0;
volatile uint32 Key_0_PressingTime=0;

volatile uint8 PasswordCorrectionChecker;

int main(void)
{
	LCDInit();
	BuzzerInit(BUZZER0);
	KeypadInit();
	Timer0Init(TIMER0_NORMAL_MODE,TIMER0_INTERNAL_CLK_PRESC_1024,0);
	Timer0InterruptInit(TIMER0_OVERFLOW);
	
	volatile uint8 InputKey;
	volatile uint8 PasswordlengthChecker;
	
	volatile uint8 LockerStateFlag=CLOSE;
	volatile uint8 Key_B_StateFlag=NOT_PRESSED;
	volatile uint8 KeyPressingFlag=RELEASED;
	
    while(1)
    {
		InputKey=KeypadMustPressed();
		_delay_ms(20);
		if((KeypadReadKey()==InputKey)&&(KeyPressingFlag==RELEASED))
		{
			BuzzerOn(BUZZER0);
			Delay_100msFlag=START;
			KeyPressingFlag=PRESSED;
			LCDClean();
			if(LockerStateFlag==OPEN)
			{
				if(InputKey==Keypad[1][3])
				{
					BuzzerOn(BUZZER0);
					Delay_3secFlag=START;
					if(Key_B_StateFlag==NOT_PRESSED)
					{
						Key_B_StateFlag=PRESSED;
						LCDClear();
						LCDDisplayString(1,1,"Enter New Pass..");
						LCDStateFlag=WRITTEN;
					}
					else
					{
						if(PasswordlengthChecker==CORRECT_LENGTH)
						{
							SetPassword(0,PASSWORD_DIGITS_NUMBER);
							Key_B_StateFlag=NOT_PRESSED;
							LCDClear();
							LCDDisplayString(1,1,"New Pass Saved..");
							LCDStateFlag=WRITTEN;
							ClearEnteredDigitsCounter();
						}
						else
						{
							ShortPassword();
							ClearEnteredDigitsCounter();
						}
					}
				}
				else if(InputKey==Keypad[2][3])
				{
					LCDClear();
					LCDDisplayString(1,1,"Locker is Closed");
					LCDStateFlag=WRITTEN;
					LockerStateFlag=CLOSE;
					ClearEnteredDigitsCounter();
				}
				else if(InputKey==Keypad[3][1])
				{
					Key_0_PressingTimeCalculateFlag=PRESSED;
				}
				else if(Key_B_StateFlag==PRESSED)
				{
					PasswordlengthChecker=EnterPassword(PASSWORD_DIGITS_NUMBER,InputKey);
					if(InputKey==Keypad[3][3])
					{
						if(PasswordlengthChecker==CORRECT_LENGTH)
						{
							LCDClear();
							LCDDisplayString(1,1,"Press B to Save");
							LCDStateFlag=WRITTEN;
						}
						else
						{
							ShortPassword();							
						}
					}
					else
					{
						IsPasswordLong(PasswordlengthChecker);
					}
				}
				else
				{
					LCDClear();
					LCDDisplayString(1,1,"Opened Already");
					LCDStateFlag=WRITTEN;
				}
			}
			else
			{
				if(InputKey==Keypad[1][3])
				{
					LCDClear();
					LCDDisplayString(1,1,"Must Open Locker");
					LCDStateFlag=WRITTEN;
					ClearEnteredDigitsCounter();
				}
				else if(InputKey==Keypad[2][3])
				{
					LCDClear();
					LCDDisplayString(1,1,"Closed Already");
					LCDStateFlag=WRITTEN;
					ClearEnteredDigitsCounter();
				}
				else if(InputKey==Keypad[3][1])
				{
					Key_0_PressingTimeCalculateFlag=PRESSED;
				}
				else
				{
					PasswordlengthChecker=EnterPassword(PASSWORD_DIGITS_NUMBER,InputKey);
					if(InputKey==Keypad[3][3])
					{
						if(PasswordlengthChecker==CORRECT_LENGTH)
						{
							PasswordCorrectionChecker=CheckPassword(0,PASSWORD_DIGITS_NUMBER);
							if(PasswordCorrectionChecker==CORRECT_PASSWORD)
							{
								LCDClear();
								LCDDisplayString(1,1,"Locker is Opened");
								LockerStateFlag=OPEN;
								LCDStateFlag=WRITTEN;
							}
							else
							{
								BuzzerOn(BUZZER0);
								Delay_3secFlag=START;
								LCDClear();
								LCDDisplayString(1,1,"Wrong Password..");
								LCDDisplayString(2,1,"Re-enter Pass..");
								LCDStateFlag=WRITTEN;
							}
						}
						else
						{
							ShortPassword();							
						}
					}
					else
					{
						IsPasswordLong(PasswordlengthChecker);
					}
				}				
			}
					
		}
		if((KeypadReadKey()!=InputKey)&&(KeyPressingFlag==PRESSED))
		{
			
			if(Key_0_PressingTimeCalculateFlag==START)
			{
				if(LockerStateFlag==OPEN)
				{
					if(Key_B_StateFlag==PRESSED)
					{
						PasswordlengthChecker=EnterPassword(PASSWORD_DIGITS_NUMBER,Keypad[3][1]);
						IsPasswordLong(PasswordlengthChecker);
					}
					else
					{
						LCDClear();
						LCDDisplayString(1,1,"Opened Already");
						LCDStateFlag=WRITTEN;
					}
				}
				else
				{
					PasswordlengthChecker=EnterPassword(PASSWORD_DIGITS_NUMBER,Keypad[3][1]);
					IsPasswordLong(PasswordlengthChecker);
				}
				OverflowCounterForKey_0=0;
				Key_0_PressingTimeCalculateFlag=STOP;				
			}
			KeyPressingFlag=RELEASED;
		}
		if((KeypadReadKey()==InputKey)&&(KeyPressingFlag==PRESSED)&&(Key_0_PressingTimeCalculateFlag==PRESSED))
		{
			if(Key_0_PressingTime>=5)
			{
				LCDClear();
				if(LockerStateFlag==OPEN)
				{
					for(uint8 i=0;i<PASSWORD_DIGITS_NUMBER;i++)
					{
						EEPROMWriteData(i,0);
					}
					LCDDisplayString(1,1,"Pass is Reseted");
				}
				else
				{
					LCDDisplayString(1,1,"Must Open Locker");
					LCDDisplayString(2,1,"Or Re-Flash Code");
				}
				LCDStateFlag=WRITTEN;
				Key_0_PressingTimeCalculateFlag=STOP;
				OverflowCounterForKey_0=0;
				Key_0_PressingTime=0;
				ClearEnteredDigitsCounter();
			}			
		}
    }
}

ISR(TIMER0_OVF_vect)
{
	static uint32 OverflowCounterFor100ms=0;
	static uint32 OverflowCounterFor3s=0;
	
	if(Delay_100msFlag==START)
	{
		if(Delay_3secFlag==STOP)
		{
			OverflowCounterFor100ms++;
			if(OverflowCounterFor100ms==Timer0Delay_sec_Normal(0.1,1024))
			{
				BuzzerOff(BUZZER0);
				OverflowCounterFor100ms=0;
				Delay_100msFlag=STOP;
			}	
		}
		else
		{
			OverflowCounterFor100ms=0;
			Delay_100msFlag=STOP;			
		}
	}
	if(Delay_3secFlag==START)
	{
		OverflowCounterFor3s++;
		if(OverflowCounterFor3s==Timer0Delay_sec_Normal(3,1024))
		{
			BuzzerOff(BUZZER0);
			OverflowCounterFor3s=0;
			Delay_3secFlag=STOP;
		}
	}
	
	if(Key_0_PressingTimeCalculateFlag==START)
	{
		OverflowCounterForKey_0++;
		Key_0_PressingTime=(uint32)(OverflowCounterForKey_0*((256.0*1024)/F_CPU));
	}
}

void LCDClean(void)
{	
	if(LCDStateFlag==WRITTEN)
	{
		LCDClear();
		LCDStateFlag=CLEAR;
	}
}

void LongPassword(void)
{
	LCDClear();
	LCDDisplayString(1,1,"Too Long Pass..");
	LCDStateFlag=WRITTEN;	
}

void ShortPassword(void)
{
	LCDClear();
	LCDDisplayString(1,1,"Too Short Pass..");
	LCDDisplayString(2,1,"Re-Enter Again");
	LCDStateFlag=WRITTEN;
}

void IsPasswordLong(uint8 PasswordlengthChecker)
{
	if(PasswordlengthChecker==LONG_LENGTH)
	{
		LongPassword();
	}
	else
	{
		LCDSendData('*');
	}	
}