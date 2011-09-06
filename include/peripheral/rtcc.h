/*********************************************************************
 *
 *                  RTCC Lib definitions
 *
 *********************************************************************
 * FileName:        Rtcc.h
 * Dependencies:	p32xxxx.h
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology Inc..
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PIC32 Microcontroller is intended
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PIC32 Microcontroller products.
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 * $Id: Rtcc.h,v 1.10 2007/01/16 20:30:43 C12878 Exp $
 * $Name:  $
 *
 ********************************************************************/


#ifndef _RTCC_H_
#define _RTCC_H_


#include <p32xxxx.h>
#include <peripheral/lock.h>
#ifdef __cplusplus
extern "C"
  {
#endif
#ifdef _RTCC

// RTCC definitions

// union/structure for read/write of time into the RTCC device
typedef union
{
	struct
	{
		unsigned char	rsvd;		// reserved for future use. should be 0
		unsigned char	sec;		// BCD codification for seconds, 00-59
		unsigned char	min;		// BCD codification for minutes, 00-59
		unsigned char	hour;		// BCD codification for hours, 00-24
	};								// field access
	unsigned char		b[4];		// byte access
	unsigned short		w[2];		// 16 bits access
	unsigned long		l;			// 32 bits access
}rtccTime;

// union/structure for read/write of date into the RTCC device
typedef union
{
	struct
	{
		unsigned char	wday;		// BCD codification for day of the week, 00-06
		unsigned char	mday;		// BCD codification for day of the month, 01-31
		unsigned char	mon;		// BCD codification for month, 01-12
		unsigned char	year;		// BCD codification for years, 00-99
	};								// field access
	unsigned char		b[4];		// byte access
	unsigned short		w[2];		// 16 bits access
	unsigned long		l;			// 32 bits access
}rtccDate;

// valid values of alarm repetition for the RTCC device
typedef enum
{
	RTCC_RPT_HALF_SEC,		// repeat alarm every half second
	RTCC_RPT_SEC,			// repeat alarm every second
	RTCC_RPT_TEN_SEC,		// repeat alarm every ten seconds
	RTCC_RPT_MIN,			// repeat alarm every minute
	RTCC_RPT_TEN_MIN,		// repeat alarm every ten minutes
	RTCC_RPT_HOUR,			// repeat alarm every hour
	RTCC_RPT_DAY,			// repeat alarm every day
	RTCC_RPT_WEEK,			// repeat alarm every week
	RTCC_RPT_MON,			// repeat alarm every month
	RTCC_RPT_YEAR			// repeat alarm every year (except when configured for Feb 29th.)
}rtccRepeat;

// results returned by initialization functions
typedef enum
{
	RTCC_CLK_ON,			// success, clock is running
	RTCC_SOSC_NRDY,			// SOSC not running
	RTCC_CLK_NRDY,			// RTCC clock not running
	RTCC_WR_DSBL,			// WR is disabled
}rtccRes;

// RTCC interface functions


// high level control functions

/*********************************************************************
 * Function:        rtccRes RtccInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          RTCC_CLK_ON if the RTCC clock is actually running
 * 					a clock status code otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function initializes the RTCC device. It starts the RTCC clock,
 * 					enables the RTCC and disables RTCC write. Disables the Alarm and the OE.
 * 					Clears the alarm interrupt flag and disables the alarm interrupt.
 *
 * Note:            It usually takes 4x256 clock cycles (approx 31.2 ms) for the oscillator signal to be available
 * 					to the RTCC. The user must make sure that the clock is actually running using RtccGetClkStat()
 * 					before expecting the RTCC to count.
 *
 * Example:			rtccRes res=RtccInit();
 ********************************************************************/
rtccRes		RtccInit(void);

/*********************************************************************
 * Function:        rtccRes RtccOpen((unsigned long tm, unsigned long dt, int drift)
 *
 * PreCondition:    tm an unsigned long containing the fields of a valid rtccTime structure:
 * 						- sec:	BCD codification, 00-59
 * 						- min:  BCD codification, 00-59
 * 						- hour: BCD codification, 00-24
 * 			dt is an unsigned long conatining the valid fields of a rtccDate structure:
 * 						- wday:	BCD codification, 00-06
 * 						- mday: BCD codification, 01-31
 * 						- mon: BCD codification, 01-12
 * 						- year: BCD codification, 00-99
 * 			drift has to fit into signed 10 bits representation
 *
 * Input:           	tm - the time value to be set
 * 			dt - the date value to be set
 * 			drift	- value to be added/subtracted to perform calibration
 *
 * Output:          RTCC_CLK_ON if the RTCC clock is actually running
 * 					a clock status code otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function initializes the RTCC device. It starts the RTCC clock, sets the desired time and calibration
 * 					and enables the RTCC. Disables the Alarm and the OE and further RTCC writes.
 * 					Clears the alarm interrupt flag and disables the alarm interrupt.
 *
 * Note:            It usually takes 4x256 clock cycles (approx 31.2 ms) for the oscillator signal to be available
 * 					to the RTCC. The user must make sure that the clock is actually running using RtccGetClkStat()
 * 					before expecting the RTCC to count.
 *
 * Example:		rtccDate dt; dt.wday=05; dt.mday=0x28; dt.mon=0x2; dt.year=0;
 * 			rtccTime tm; tm.sec=0x15; tm.min=0x30; tm.hour=01;
 * 			rtccRes res=RtccOpen(tm.l, dt.l, 10);
 * 					or
 * 			rtccRes res=RtccOpen(0x01301500, 0x00022805, 10);
 ********************************************************************/
rtccRes		RtccOpen(unsigned long tm, unsigned long dt, int drift);

/*********************************************************************
 * Function:        void RtccShutdown(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function shutdowns the RTCC device. It stops the RTCC clock,
 * 					sets the RTCC Off and disables RTCC write. Disables the Alarm and the OE.
 * 					Clears the alarm interrupt flag and disables the alarm interrupt.
 *
 * Note:            None
 *
 * Example:			RtccShutdown();
 ********************************************************************/
void		RtccShutdown(void);


// time and alarm functions

/*********************************************************************
 * Function:        void RtccSetTime(unsigned long tm)
 *
 * PreCondition:    tm an unsigned long containing the fields of a valid rtccTime structure:
 * 						- sec:	BCD codification, 00-59
 * 						- min:  BCD codification, 00-59
 * 						- hour: BCD codification, 00-24
 *
 * Input:           tm - the time value to be set
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function sets the current time in the RTCC device.
 *
 * Note:            - The write is successful only if Wr Enable is set.
 * 					The function will enable the write itself, if needed.
 * 					- The device could be stopped in order
 * 					to safely perform the update of the RTC time register.
 * 					However, the device status will be restored but	the routine won't wait
 * 					for the CLK to be running before returning. User has to check RtccGetClkStat() (will take approx 30us).
 * 					- The routine could disable the interrupts for a very short time to be able
 * 					to update the time and date registers.
 *
 * Example:			rtccTime tm; tm.sec=0x15; tm.min=0x30; tm.hour=01; RtccSetTime(tm.l);
 * 					or
 * 					RtccSetTime(0x01301500);
 *
 ********************************************************************/
void		RtccSetTime(unsigned long tm);

/*********************************************************************
 * Function:        unsigned long RtccGetTime(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          The current value of the time which can be safely casted to an rtccTime structure.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current time of the RTCC device.
 *
 * Note:            - The function makes sure that the read value is valid.
 * 					It avoids waiting for the RTCSYNC to be clear by
 * 					performing successive reads.
 *
 * Example:			rtccTime tm; tm.l=RtccGetTime();
 ********************************************************************/
extern __inline__ unsigned long __attribute__((always_inline))	RtccGetTime(void)
{
	unsigned int	t0, t1;
	do
	{
		t0=RTCTIME;
		t1=RTCTIME;
	}while(t0!=t1);
	return t0;
}

/*********************************************************************
 * Function:        void RtccSetDate(unsigned long dt)
 *
 * PreCondition:    dt is an unsigned long conatining the valid fields of a rtccDate structure:
 * 						- wday:	BCD codification, 00-06
 * 						- mday: BCD codification, 01-31
 * 						- mon: BCD codification, 01-12
 * 						- year: BCD codification, 00-99
 *
 * Input:           dt - the date value to be set
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function sets the current date in the RTCC device.
 *
 * Note:            - The write is successful only if Wr Enable is set.
 * 					The function will enable the write itself, if needed.
 * 					- The device could be stopped in order
 * 					to safely perform the update of the RTC time register.
 * 					However, the device status will be restored but	the routine won't wait
 * 					for the CLK to be running before returning. User has to check RtccGetClkStat() (will take approx 30us).
 * 					- The routine could disable the interrupts for a very short time to be able
 * 					to update the time and date registers.
 *
 * Example:			rtccDate dt; dt.wday=05; dt.mday=0x28; dt.mon=0x2; dt.year=0; RtccSetDate(dt.l);
 * 					or
 * 					RtccSetDate(0x00022805);
 ********************************************************************/
void		RtccSetDate(unsigned long dt);

/*********************************************************************
 * Function:        unsigned long RtccGetDate(void)
 *
 * PreCondition:    pDt a valid pointer
 *
 * Input:           None
 *
 * Output:          an unsigned long representing the current date.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current date of the RTCC device. Can be safely cast into rtccDate.
 *
 * Note:            The function makes sure that the read value is valid.
 * 					It avoids waiting for the RTCSYNC to be clear by
 * 					performing successive reads.
 *
 * Example:			rtccDate dt; dt.l=RtccGetDate();
 ********************************************************************/
extern __inline__ unsigned long __attribute__((always_inline))	RtccGetDate(void)
{
	unsigned int	d0, d1;
	do
	{
		d0=RTCDATE;
		d1=RTCDATE;
	}while(d0!=d1);

	return d0;
}

/*********************************************************************
 * Function:        void RtccSetTimeDate(unsigned long tm, unsigned long dt)
 *
 * PreCondition:    tm a valid rtccTime structure having proper halues:
 * 						- sec:	BCD codification, 00-59
 * 						- min:  BCD codification, 00-59
 * 						- hour: BCD codification, 00-24
 * 					date a valid rtccDate structure having proper values
 * 						- wday:	BCD codification, 00-06
 * 						- mday: BCD codification, 01-31
 * 						- mon: BCD codification, 01-12
 * 						- year: BCD codification, 00-99
 *
 * Input:           tm - the time value to be set
 * 					dt - the date value to be set
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function sets the current time and date in the RTCC device.
 *
 * Note:            - The write is successful only if Wr Enable is set.
 * 					The function will enable the write itself, if needed.
 * 					- The device could be stopped in order
 * 					to safely perform the update of the RTC time register.
 * 					However, the device status will be restored but	the routine won't wait
 * 					for the CLK to be running before returning. User has to check RtccGetClkStat() (will take approx 30us).
 * 					- The routine could disable the interrupts for a very short time to be able
 * 					to update the time and date registers.
 *
 * Example:			rtccTime tm; tm.sec=0x15; tm.min=0x59; tm.hour=0x23;
 * 					rtccDate dt; dt.wday=05; dt.mday=0x28; dt.mon=0x2; dt.year=0;
 * 					RtccSetTimeDate(tm, dt);
 * 					or
 * 					RtccSetTimeDate(0x23591500, 0x00022805);
 ********************************************************************/
void		RtccSetTimeDate(unsigned long tm, unsigned long dt);

/*********************************************************************
 * Function:        void RtccGetTimeDate(rtccTime* pTm, rtccDate* pDt)
 *
 * PreCondition:    pTm, pDt valid pointers
 *
 * Input:           pTm - pointer to a rtccTime union to store the current time
 * 					pDt - pointer to a rtccDate union to store the current date
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function updates the user supplied union/structures with
 * 					the current time and date of the RTCC device.
 *
 * Note:            - The function makes sure that the read value is valid.
 * 					It avoids waiting for the RTCSYNC to be clear by
 * 					performing successive reads.
 *
 * Example:			rtccTime tm; rtccDate dt; RtccGetTimeDate(&tm, &dt);
 ********************************************************************/
extern __inline__ void __attribute__((always_inline))	RtccGetTimeDate(rtccTime* pTm, rtccDate* pDt)
{
	rtccTime	t0;
	rtccDate	d0;
	do
	{
		d0.l=RTCDATE;
		t0.l=RTCTIME;
		pTm->l=RTCTIME;
		pDt->l=RTCDATE;
	}while((d0.l!=pDt->l) || (t0.l!=pTm->l));		// update the user requested data
}


/*********************************************************************
 * Function:        void RtccSetAlarmTime(unsigned long tm)
 *
 * PreCondition:    tm a valid rtccTime structure having proper values:
 * 						- sec:	BCD codification, 00-59
 * 						- min:  BCD codification, 00-59
 * 						- hour: BCD codification, 00-24
 *
 * Input:           tm - the alarm time to be set
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function sets the current alarm time in the RTCC device.
 *
 * Note:            - The function might wait for the proper Alarm window
 * 					to safely perform the update of the ALRMTIME register.
 * 					- Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 *
 * Example:			rtccTime tm; tm.sec=0x15; tm.min=0x59; tm.hour=0x23; RtccSetAlarmTime(tm.l);
 * 					or
 * 					RtccSetAlarmTime(0x23591500);
 ********************************************************************/
void		RtccSetAlarmTime(unsigned long tm);

/*********************************************************************
 * Function:        unsigned long RtccGetAlarmTime(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          the current alarm time
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current alarm time of the RTCC device.
 *
 * Note:            None
 *
 * Example:         rtccTime tm; tm.l=RtccGetAlarmTime();
 ********************************************************************/
extern __inline__ unsigned long __attribute__((always_inline))	RtccGetAlarmTime(void)
{
	return	ALRMTIME;
}


/*********************************************************************
 * Function:        void RtccSetAlarmDate(unsigned long dt)
 *
 * PreCondition:    dt a valid rtccDate formatted structure having proper values:
 * 						- wday:	BCD codification, 00-06
 * 						- mday: BCD codification, 01-31
 * 						- mon: BCD codification, 01-12
 *
 * Input:           dt - value of the alarm date
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function sets the alarm date in the RTCC device.
 *
 * Note:            - The function might wait for the proper Alarm window
 * 					to safely perform the update of the ALRMDATE register.
 * 					- Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 * 					- Note that the alarm date does not contain a year field.
 *
 * Example:			rtccDate dt; dt.wday=0; dt.mday=0x12; dt.mon=0x12; RtccSetAlarmDate(dt.l);
 * 					or
 * 					RtccSetAlarmDate(0x121200);
 ********************************************************************/
void		RtccSetAlarmDate(unsigned long dt);

/*********************************************************************
 * Function:        unsigned long RtccGetAlarmDate(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          The current alarm date. Can be safely cast into an rtccDate.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current alarm date of the RTCC device.
 *
 * Note:            None
 *
 * Example:         rtccDate dt; dt.l=RtccGetAlarmDate();
 ********************************************************************/
extern __inline__ unsigned long __attribute__((always_inline))	RtccGetAlarmDate(void)
{
	return	ALRMDATE;
}


/*********************************************************************
 * Function:        void RtccSetAlarmTimeDate(unsigned long tm, unsigned long dt)
 *
 * PreCondition:    tm a valid rtccTime structure having proper values:
 * 						- sec:	BCD codification, 00-59
 * 						- min:  BCD codification, 00-59
 * 						- hour: BCD codification, 00-24
 * 					dt a valid rtccDate structure having proper values:
 * 						- wday:	BCD codification, 00-06
 * 						- mday: BCD codification, 01-31
 * 						- mon: BCD codification, 01-12
 *
 * Input:           tm - the alarm time to be set
 * 					dt - the alarm date to be set
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function sets the current alarm time and date in the RTCC device.
 *
 * Note:            - The function might wait for the proper Alarm window
 * 					to safely perform the update of the ALRMTIME, ALRMDATE registers.
 * 					- Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 * 					- Note that the alarm time does not contain a year field.
 *
 * Example:			rtccTime tm; tm.sec=0; tm.min=0x59; tm.hour-0x23;
 * 					rtccDate dt; dt.wday=0; dt.mday=0x12; dt.mon=0x12;
 * 					RtccSetAlarmTimeDate(tm.l, dt.l);
 * 					or
 * 					RtccSetAlarmTimeDate(0x235900, 0x121200);
 ********************************************************************/
void		RtccSetAlarmTimeDate(unsigned long tm, unsigned long dt);

/*********************************************************************
 * Function:        void RtccGetAlarmTimeDate(rtccTime* pTm, rtccDate* pDt)
 *
 * PreCondition:    pTm, pDt valid pointers
 *
 * Input:           pTm - pointer to a rtccTime union to store the alarm time
 * 					pDt - pointer to a rtccDate union to store the alarm date
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function updates the user supplied union/structures with
 * 					the current alarm time and date of the RTCC device.
 *
 * Note:            None
 *
 * Example:			rtccTime tm; rtccDate dt; RtccGetAlarmTimeDate(&tm, &dt);
 ********************************************************************/
extern __inline__ void __attribute__((always_inline))	RtccGetAlarmTimeDate(rtccTime* pTm, rtccDate* pDt)
{
	pTm->l=ALRMTIME;
	pDt->l=ALRMDATE;
}

/*********************************************************************
 * Function:        void RtccAlarmEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function enables the alarm of the RTCC device.
 *
 * Note:            - The function might wait for the proper Alarm window
 * 					to safely perform the update of the RTCALRM register.
 * 					- Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 *
 * Example:			RtccAlarmEnable();
 ********************************************************************/
 void		RtccAlarmEnable(void);


/*********************************************************************
 * Function:        void RtccAlarmDisable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function disables the alarm of the RTCC device.
 *
 * Note:            - The function might wait for the proper Alarm window
 * 					to safely perform the update of the RTCALRM register.
 * 					- Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 *
 * Example:			RtccAlarmDisable();
 ********************************************************************/
 void		RtccAlarmDisable(void);


/*********************************************************************
 * Function:        int RtccGetAlarmEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          curent status of the RTCC alarm
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the alarm status of the RTCC device.
 *
 * Note:            None
 *
 * Example:			int isAlrmEnabled=RtccGetAlarmEnable();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline)) RtccGetAlarmEnable(void)
{
	int	isAlrm0, isAlrm1;
	do
	{
		isAlrm0=RTCALRMbits.ALRMEN;
		isAlrm1=RTCALRMbits.ALRMEN;
	}while(isAlrm0!=isAlrm1);

	return isAlrm0;
}


/*********************************************************************
 * Function:        void RtccChimeEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function enables the chime alarm of the RTCC device.
 *
 * Note:            - The function might wait for the proper Alarm window
 * 					to safely perform the update of the RTCALRM register.
 * 					- Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 *
 * Example:			RtccChimeEnable();
 ********************************************************************/
void		RtccChimeEnable(void);

/*********************************************************************
 * Function:        void RtccChimeDisable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function disables the chime alarm of the RTCC device.
 *
 * Note:            - The function might wait for the proper Alarm window
 * 					to safely perform the update of the RTCALRM register.
 * 					- Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 *
 * Example:			RtccChimeDisable();
 ********************************************************************/
void		RtccChimeDisable(void);


/*********************************************************************
 * Function:        int RtccGetChimeEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          current status of the alarm chime
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the chime alarm of the RTCC device.
 *
 * Note:            None
 *
 * Example:			int isChimeEnabled=RtccGetChimeEnable();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline)) RtccGetChimeEnable(void)
{
	int	ch0, ch1;
	do
	{
		ch0=RTCALRMbits.CHIME;
		ch1=RTCALRMbits.CHIME;
	}while(ch0!=ch1);

	return ch0;

}

/*********************************************************************
 * Function:        void RtccSetAlarmRpt(rtccRepeat rpt)
 *
 * PreCondition:    rpt has to be a proper rtccRepeat enumeration value
 * Input:           rpt 		- value of the desired alarm repeat rate
 *
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function sets the RTCC alarm repeat rate.
 *
 * Note:            - The function might wait for the proper Alarm window
 * 					to safely perform the update of the RTCALRM register.
 * 					- Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 *
 * Example:			RtccSetAlarmRpt(RTCC_RPT_MIN);
 ********************************************************************/
void		RtccSetAlarmRpt(rtccRepeat rpt);

/*********************************************************************
 * Function:        rtccRepeat RtccGetAlarmRpt(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          The value of the current alarm repeat rate.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current RTCC alarm repeat rate.
 *
 * Note:            None
 *
 * Example:			rtccRepeat rptAlrm=RtccGetAlarmRpt();
 ********************************************************************/
extern __inline__ rtccRepeat __attribute__((always_inline)) RtccGetAlarmRpt(void)
{
	rtccRepeat	r0, r1;

	do
	{
		r0=(rtccRepeat)(RTCALRM&_RTCALRM_AMASK_MASK);
		r1=(rtccRepeat)(RTCALRM&_RTCALRM_AMASK_MASK);
	}while(r0!=r1);

	return (rtccRepeat)(r0>>_RTCALRM_AMASK_POSITION);
}

/*********************************************************************
 * Function:        void RtccSetAlarmRptCount(int rptCnt)
 *
 * PreCondition:    rptCnt has to be a value less then 256
 *
 * Input:           rpt 		- value of the desired alarm repeat rate
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function sets the RTCC alarm repeat count.
 * 					The number of alarm triggers will be rptCnt+1:
 * 						- one alarm trigger if rptCnt==0
 * 						- ....
 * 						- 256 alarm triggers if rptCnt=255
 *
 * Note:            - rptCnt will be truncated to fit into 8 bit representation.
 * 		            - The function might wait for the proper Alarm window
 * 					to safely perform the update of the RTCALRM register.
 * 					- Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 * 					- If rptCnt is 0, there will be one alarm trigger.
 *
 * Example:			RtccSetAlarmRptCount(10);
 ********************************************************************/
void		RtccSetAlarmRptCount(int rptCnt);

/*********************************************************************
 * Function:        int RtccGetAlarmRptCount(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          the current alarm repeat count
 *
 * Side Effects:    None
 *
 * Overview:        The function reads the RTCC alarm repeat counter.
 *
 * Note:            The reading is affected by the sttatus of RTCALRM.ALRMSYNC bit.
 * 					Double readings are performed.
 *
 * Example:			int alrmRptCnt=RtccGetAlarmRptCount();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline)) RtccGetAlarmRptCount(void)
{
	int	rpt0, rpt1;
	do
	{
		rpt0=RTCALRMbits.ARPT;
		rpt1=RTCALRMbits.ARPT;
	}while(rpt0!=rpt1);

	return rpt0;
}

/*********************************************************************
 * Function:        int	RtccWeekDay(int year, int month, int day)
 *
 * PreCondition:    Date greater than 14 Sep 1752.
 *
 * Input:           year	- year value
 * 					month	- month value, 1-12
 * 					day		- day value, 1-31
 *
 * Output:          the week of the day, 0 for Sun, 1 for Mon and so on
 *
 * Side Effects:    None
 *
 * Overview:        The algorithm calculates the week of the day for new style
 * 					dates, beginning at 14 Sep 1752.
 * 					Based on an algorithm by Lewis Carroll.
 *
 * Note:            None
 *
 * Example:			int weekDay=RtccWeekDay(2004, 02, 28);
 ********************************************************************/
int			RtccWeekDay(int year, int month, int day);


// low level control functions

/*********************************************************************
 * Function:        rtccRes RtccEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          RTCC_CLK_ON if the RTCC was enabled and the RTCC clock is running,
 * 					a clock status code otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function enables the RTCC.
 *
 * Note:            - The write operations have to be enabled in order to be able to toggle the ON control bit.
 * 					Otherwise the function will fail.
 * 					See RtccWrEnable() function.
 * 					- The function doesn't wait for the RTC clock to be on.
 *
 * Example:			rtccRes clkStat=RtccEnable();
 ********************************************************************/
rtccRes		RtccEnable(void);


/*********************************************************************
 * Function:        int RtccDisable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if the RTCC was disabled,
 * 					FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function disables the RTCC.
 *
 * Note:            1. The write operations have to be enabled in order to be able to toggle the ON control bit.
 * 					Otherwise the function will fail.
 * 					See RtccWrEnable() function.
 * 					2. When ON control bit is set to 0, RTCCON.RTCSYNC, RTCCON.HALFSEC and
 * 					RTCCON.RTCOE are asynchronously reset.
 * 					- The function waits for the RTC clock to be off.
 *
 * Example:			RtccDisable();
 ********************************************************************/
int		RtccDisable(void);

/*********************************************************************
 * Function:        int RtccGetEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          the current enabled/disabled status of the RTCC module.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the RTCCON.ON bit anded with RTCCLKON.
 *
 * Note:            None
 *
 * Example:         int isEnabled=RtccGetEnable();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline))	RtccGetEnable(void)
{
	return	(RTCCON&(_RTCCON_ON_MASK|_RTCCON_RTCCLKON_MASK));
}

/*********************************************************************
 * Function:        rtccRes RtccGetClkStat(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          RTCC_CLK_ON if the RTCC clock is running (the oscillator output is presented to the RTCC module).
 * 					an clock status otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the RTCCON.ON bit anded with RTCCLKON.
 *
 * Note:            None
 *
 * Example:			int isClkOn=RtccGetClkStat();
 ********************************************************************/
extern __inline__ rtccRes __attribute__((always_inline)) RtccGetClkStat(void)
{

	if( (!(OSCCONbits.SOSCEN)) || (!(OSCCONbits.SOSCRDY)) )
	{
		return RTCC_SOSC_NRDY;
	}
	else if(!(RTCCONbits.RTCCLKON))
	{
		return RTCC_CLK_NRDY;
	}

	return RTCC_CLK_ON;
}


/*********************************************************************
 * Function:        void RtccSetCalibration(int drift)
 *
 * PreCondition:    drift has to fit into signed 10 bits representation
 *
 * Input:           drift	- value to be added/subtracted to perform calibration
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function updates the value that the RTCC uses in the
 * 					auto-adjust feature, once every minute.
 * 					The drift value acts as a signed value, [-512, +511], 0 not having
 * 					any effect.
 *
 * Note:            - Writes to the RTCCON.CAL[9:0] register should  only occur when the timer
 * 					is turned off or immediately or after the edge of the seconds pulse
 * 					(except when SECONDS=00 - due to the possibility of the auto-adjust event).
 * 					In order to speed-up the process, the API function performs the reading
 * 					of the HALFSEC field.
 * 					- The function may block for half a second, worst case, when called
 * 					at the start of the minute.
 * 					- A write to the SECONDS value resets the state of the calibration and the prescaler.
 * 					If calibration just occurred, it will occur again at the prescaler rollover.
 * 					- Interrupts can not be disabled for such a long period. However, long interrupt routines
 * 					can interfere with the proper functioning of the device. Care must be taken.
 *
 * Example:			RtccSetCalibration(10);
 ********************************************************************/
void		RtccSetCalibration(int drift);

/*********************************************************************
 * Function:        int RtccGetCalibration(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Current value of the RTCC calibration field.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the value that the RTCC uses in the
 * 					auto-adjust feature, once every minute.
 * 					The calibration value is a signed 10 bits value, [-512, +511].
 *
 * Note:            None
 *
 * Example:         int currCal=RtccGetCalibration();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline))	RtccGetCalibration(void)
{
	return	RTCCONbits.CAL;
}

/*********************************************************************
 * Function:        void RtccWrEnable(int enable)
 *
 * PreCondition:    None
 *
 * Input:           enable - boolean to enable/disable the RTCC updates.
 *
 * Output:          None.
 *
 * Side Effects:    None
 *
 * Overview:        The function enables the updates to the RTCC
 *                  time registers and ON control bit.
 *
 * Note:            - The write can be enabled by performing a specific unlock sequence.
 *                  In order to succeed, this sequence need not be interrupted by other memory accesses
 *                  (DMA transfers, interrupts, etc).
 *                  - Interrupts and DMA transfers that might disrupt the write unlock sequence are disabled
 *                  shortly for properly unlocking the device.
 *
 * Example:        RtccWrEnable(1);
 ********************************************************************/
extern __inline__ void __attribute__((always_inline))	RtccWrEnable(int enable)
{
	if(enable)
	{
		mSysUnlockOpLock(RTCCONSET=_RTCCON_RTCWREN_MASK);
	}
	else
	{
		RTCCONCLR=_RTCCON_RTCWREN_MASK;
	}
}


/*********************************************************************
 * Function:        int RtccGetWrEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if the RTCC is unlocked, FALSE if locked
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current status of the RTCC write enable bit.
 *
 * Note:            None
 *
 * Example:         int isWrEnabled=RtccGetWrEnable();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline))	RtccGetWrEnable(void)
{
	return	RTCCONbits.RTCWREN!=0;
}

/*********************************************************************
 * Function:        int RtccGetSync(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if the SYNC signal is asserted, FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current status of the RTCCON SYNC bit.
 *
 * Note:            None
 *
 * Example:         int isSync=RtccGetSync();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline))	RtccGetSync(void)
{
	return	RTCCONbits.RTCSYNC!=0;
}


/*********************************************************************
 * Function:        int RtccGetHalfSecond(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if the RTCC is in the second HALF SECOND  interval, FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current status of the RTCCON HALFSEC bit.
 *
 * Note:            None
 *
 * Example:         int is2HalfSec=RtccGetHalfSecond();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline))	RtccGetHalfSecond(void)
{
	return	RTCCONbits.HALFSEC!=0;
}

/*********************************************************************
 * Function:        int RtccGetAlrmSync(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if the AlrmSync signal is asserted, FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current status of the RTCALRM ALRMSYNC bit.
 *
 * Note:            None
 *
 * Example:         int isSync=RtccGetAlrmSync();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline))	RtccGetAlrmSync(void)
{
	return	RTCALRMbits.ALRMSYNC!=0;
}


/*********************************************************************
 * Function:        void RtccSelectPulseOutput(int secPulse)
 *
 * PreCondition:    None
 *
 * Input:           secPulse - boolean to select the seconds/alarm pulse as output
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function selects the seconds clock pulse or the alarm pulse as the function of the RTCC output pin.
 *
 * Note:            The RTCC has to be enabled for the output to actually be active.
 *
 * Example:         RtccSelectPulseOutput(1);
 ********************************************************************/
extern __inline__ void __attribute__((always_inline))	RtccSelectPulseOutput(int secPulse)
{
	if(secPulse)
	{
		RTCCONSET=_RTCCON_RTSECSEL_MASK;
	}
	else
	{
		RTCCONCLR=_RTCCON_RTSECSEL_MASK;
	}
}



/*********************************************************************
 * Function:        void RtccAlarmPulseHigh(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function sets the initial value of the output Alarm Pulse to logic 1.
 *
 * Note:            1. The RTCC has to be enabled for the output to actually be active.
 * 					2. This Alarm Pulse output is writable only when the alarm is disabled.
 *					3. The function might wait for the proper Alarm window
 * 					to safely perform the update of the RTCALRM register.
 * 					4. Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 *
 * Example:			RtccAlarmPulseHigh();
 ********************************************************************/
void		RtccAlarmPulseHigh(void);

/*********************************************************************
 * Function:        void RtccAlarmPulseLow(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function sets the initial value of the output Alarm Pulse to logic 0.
 *
 * Note:            1. The RTCC has to be enabled for the output to actually be active.
 * 					2. This Alarm Pulse output is writable only when the alarm is disabled.
*					3. The function might wait for the proper Alarm window
 * 					to safely perform the update of the RTCALRM register.
 * 					4. Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 *
 * Example:			RtccAlarmPulseLow();
 ********************************************************************/
void		RtccAlarmPulseLow(void);

/*********************************************************************
 * Function:        void RtccAlarmPulseToggle(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function toggles the value of the output Alarm Pulse.
 *
 * Note:            1. The RTCC has to be enabled for the output to actually be active.
 * 					2. This Alarm Pulse output is writable only when the alarm is disabled.
*					3. The function might wait for the proper Alarm window
 * 					to safely perform the update of the RTCALRM register.
 * 					4. Interrupts are disabled shortly when properly probing the ALRMSYNC needed.
 *
 * Example:			RtccAlarmPulseToggle();
 ********************************************************************/
void		RtccAlarmPulseToggle(void);

/*********************************************************************
 * Function:        int RtccGetAlarmPulse(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          1 if the Alarm Pulse output is asserted
 *                  0 otherwise
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the current state of the output Alarm Pulse.
 *
 * Note:            The alarm has to be enabled for this function to return the current state of the Alarm Pulse output.
 *
 * Example:         int alrmPulse=RtccGetAlarmPulse();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline))	RtccGetAlarmPulse(void)
{
	return RTCALRMbits.PIV!=0;
}


/*********************************************************************
 * Function:        void RtccOutputEnable(int enable)
 *
 * PreCondition:    None
 *
 * Input:           enable -  boolean to enable/disable the RTCC output pin
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function enables/disables the Output pin of the RTCC.
 *
 * Note:            The RTCC has to be enabled for the output to actually be active.
 *
 * Example:         RtccOutputEnable(1);
 ********************************************************************/
extern __inline__ void __attribute__((always_inline))	RtccOutputEnable(int enable)
{
	if(enable)
	{
		RTCCONSET=_RTCCON_RTCOE_MASK;
	}
	else
	{
		RTCCONCLR=_RTCCON_RTCOE_MASK;
	}
}

/*********************************************************************
 * Function:        int RtccGetOutputEnable(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if Output is enabled, FALSE otherwise.
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the enabled/disabled status of the RTCC Output pin.
 *
 * Note:            None
 *
 * Example:         int isOutEnabled=RtccGetOutputEnable();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline))	RtccGetOutputEnable(void)
{
	return	RTCCONbits.RTCOE!=0;
}


// special purpose functions
/*********************************************************************
 * Function:        void RtccFreezeEnable(int enable)
 *
 * PreCondition:    None
 *
 * Input:           enable - boolean to enable/disable the freeze
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The function enables/disables the FRZ status of the RTCC
 *
 * Note:            The FRZ bit reads always 0, unless in debug mode.
 *
 * Example:         RtccFreezeEnable(1);
 ********************************************************************/
extern __inline__ void __attribute__((always_inline))	RtccFreezeEnable(int enable)
{
	if(enable)
	{
		RTCCONSET=_RTCCON_FRZ_MASK;
	}
	else
	{
		RTCCONCLR=_RTCCON_FRZ_MASK;
	}
}


/*********************************************************************
 * Function:        int RtccGetFreeze(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if freeze mode enabled, FALSE if disabled
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the FRZ status of the RTCC
 *
 * Note:            The FRZ bit reads always 0, unless in debug mode.
 *
 * Example:         int isFrz=RtccGetFreeze();
 ********************************************************************/
extern __inline__ int __attribute__((always_inline))	RtccGetFreeze(void)
{
	return RTCCONbits.FRZ!=0;
}


/********************************************************************
 * Include legacy RTCC functions
 * New projects should not use them!
 * Note that interrupt functions are no longer provided.
 * The functions in the int.h should be used instead.
 ********************************************************************/
#ifndef _PLIB_DISABLE_LEGACY
	#include <peripheral/legacy/rtcc_legacy.h>
#endif

#endif  // _RTCC

#ifdef __cplusplus
  }
#endif
#endif /*_RTCC_H_*/
