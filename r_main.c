/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2010, 2011 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G13 V1.03.01 [11 Oct 2011]
* Device(s)    : R5F100LE
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 1/29/2017
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */

#include"ALCD64.c"
#include "RL64_WiFi.C"

#define DCM_L0 P5.0
#define DCM_L1 P5.1
#define DCM_R0 P5.2
#define DCM_R1 P5.3

#define Relay_Clean P5.5
#define Ultra_Sensor P3.0
#define Relay_Water_Pump P1.6


/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */

unsigned char WiFi_Rx_Arr[100];

extern unsigned char Rx_data_arr0[400];
extern unsigned char Rx_count0;
extern unsigned char Rx_ST_Flag0;
extern unsigned char Rx_data0;
int a,b,m,n,x,y;
int SingleStep = 1000, Perpen = 1500;


void Devie_Init(void );
void DCM_AutoMode(void);
void DCM_Forward(void);
void DCM_Reverse(void);
void DCM_Left(void);
void DCM_Right(void);
void DCM_Stop(void);

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    /* Start user code. Do not edit comment generated here */

	unsigned char i,j;
	Devie_Init( );
	MSDelay( 1000 );


	WiFi_Send( "WiFi ACTIVATED", 14 );	
	ALCD_Message( 0xC0," WiFi ACTIVATED " );

	Rx_ST_Flag0 = 0;
	Rx_count0 = 0;
	ALCD_Comm( 0x01 );

	while (1U)
    {
		MSDelay(100);
		ALCD_Message( 0x80,"WAITNG FR COMND " );

		if( Rx_ST_Flag0 == 1 )
		{
			ALCD_Comm( 0x01 );								// Clear display Screen
			MSDelay(200);	
			ALCD_Message( 0x80,"  WiFi DATA RX  " );
			i = 0;
			while( Rx_data_arr0[i] != ':' )
			{
				i++;
			}
			i++;
			j = 0;
			while( Rx_data_arr0[i] != '@' )
			{
				WiFi_Rx_Arr[j] = Rx_data_arr0[i];
				i++;
				j++;
			}
			WiFi_Rx_Arr[i] = '\0';
			ALCD_Message( 0xC0, WiFi_Rx_Arr );
			MSDelay(1000);
			Rx_ST_Flag0 = 0;
			Rx_count0 = 0;
			MSDelay(100);	
			ALCD_Comm( 0x01 );			// Clear display Screen
			MSDelay(100);				
		}
		
		if((Rx_data_arr0[11]=='F') && (Rx_data_arr0[12]=='F')) 
		{
			MSDelay( 100 );
			ALCD_Message( 0xC9, Rx_data_arr0 );
			DCM_Forward( );
			MSDelay( 1000 );
			ALCD_Message( 0xC9, "                ");
		}
		else if((Rx_data_arr0[11]=='B') && (Rx_data_arr0[12]=='B'))
		{
			MSDelay( 100 );
			ALCD_Message( 0xC9, Rx_data_arr0 );
			DCM_Reverse( );
			MSDelay( 1000 );
			ALCD_Message( 0xC9, "                ");
	}
		else if((Rx_data_arr0[11]=='R') && (Rx_data_arr0[12]=='R'))
		{
			MSDelay( 100 );
			ALCD_Message( 0xC9, Rx_data_arr0 );
			DCM_Right( );
			MSDelay( 1000 );
			ALCD_Message( 0xC9, "                ");
		}
		else if((Rx_data_arr0[11]=='L') && (Rx_data_arr0[12]=='L'))
		{
			MSDelay( 100 );
			ALCD_Message( 0xC9, Rx_data_arr0 );
			DCM_Left( );
			MSDelay( 1000 );
			ALCD_Message( 0xC9, "                ");
		}
		else if((Rx_data_arr0[11]=='C') && (Rx_data_arr0[12]=='C'))
		{
			ALCD_Message( 0xC9, Rx_data_arr0 );
			Relay_Water_Pump = 1;
			MSDelay( 1000 );
			Relay_Water_Pump = 0;
			MSDelay( 100 );
			Relay_Clean = 1;
			MSDelay( 1000 );
			ALCD_Message( 0xC9, "                ");
			break;
		}
		else if((Rx_data_arr0[11]=='A') && (Rx_data_arr0[12]=='A'))
		{
			ALCD_Message( 0xC9, Rx_data_arr0 );
			DCM_AutoMode();
			ALCD_Message( 0xC9, "                ");
			break;
		}
		else if((Rx_data_arr0[11]=='C') && (Rx_data_arr0[12]=='P'))
		{
			ALCD_Message( 0xC9, Rx_data_arr0 );
			Relay_Clean = 0;
			MSDelay( 1000 );
			ALCD_Message( 0xC9, "                ");
			break;
		}
		
		else if((Rx_data_arr0[11]=='S') && (Rx_data_arr0[12]=='S'))
		{
			MSDelay( 100 );
			ALCD_Message( 0xC9, Rx_data_arr0 );
			DCM_Stop( );
			MSDelay( 1000 );
			ALCD_Message( 0xC9, "                ");
			break;

		}
		if( Ultra_Sensor == 1 )
		{
			ALCD_Message( 0xC0, "OBSTACLE DETECT ");
			DCM_Left( );		
			MSDelay( 1000 );
		}
		Rx_ST_Flag0 = 0;
		Rx_count0 = 0;
	}
	while (1U)
    {
        ;
    }
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

void Devie_Init(void )
{
	MSDelay( 200 );
	ALCD_Init( );

	ALCD_Message( 0x80, "  AUTONOMOUS  ");
	ALCD_Message( 0xC0, " CLEANING ROBOT ");
	MSDelay( 1000 );
	
	R_SAU0_Create( );
	R_UART0_Create( );
	R_UART0_Start( );
	MSDelay( 100 );

	DCM_Forward( );
	MSDelay( 1000 );
	DCM_Stop( );
	
	DCM_Reverse();
	MSDelay( 1000 );
	DCM_Stop( );

	DCM_Left();
	MSDelay( 1000 );
	DCM_Stop( );

	DCM_Right();
 	MSDelay( 1000 );
	DCM_Stop( );

	Relay_Water_Pump = 1;
 	MSDelay( 1000 );
	Relay_Water_Pump = 0;
 	MSDelay( 500 );
	
	Relay_Clean = 1;
	MSDelay( 1000 );
	Relay_Clean = 0;
 	MSDelay( 500 );

	WiFi_Init_Comm( );
	MSDelay(1000);	
}	

void DCM_Forward(void)
{
	DCM_L0 = 0;
	DCM_L1 = 1;
	DCM_R0 = 0;
	DCM_R1 = 1;
	MSDelay( 1000 );
}
void DCM_Reverse(void)
{
	DCM_L0 = 1;
	DCM_L1 = 0;
	DCM_R0 = 1;
	DCM_R1 = 0;
	MSDelay( 1000 );
}
void DCM_Left(void)
{
	DCM_L0 = 0;
	DCM_L1 = 0;
	DCM_R0 = 0;
	DCM_R1 = 1;
	MSDelay( 1000 );
}
void DCM_Right(void)
{
	DCM_L0 = 0;
	DCM_L1 = 1;
	DCM_R0 = 0;
	DCM_R1 = 0;
	MSDelay( 1000 );
}
void DCM_AutoMode(void)
{
	a=0;
	b=0;
	m=5;
	n=5;
	x=m;
	y=n;
	while(y!=0)
	{
		while(x!=0)
		{
			x--;
			b++;
			DCM_Forward();
			Relay_Water_Pump = 1;
 	MSDelay( 1000 );
	Relay_Water_Pump = 0;
 	MSDelay( 500 );
	
	Relay_Clean = 1;
	MSDelay( 1000 );
	Relay_Clean = 0;
 	MSDelay( 500 );
			MSDelay(SingleStep);
			
			DCM_Stop();
			MSDelay(200);
		}
		x=m;
		y--;
		DCM_Left();
		MSDelay(Perpen);
		DCM_Forward();
		MSDelay(SingleStep);
		DCM_Left();
		MSDelay(Perpen);
		DCM_Stop();
		a++;
		MSDelay(200);
		while(x!=0)
		{
			x--;
			b--;
			DCM_Forward();
			MSDelay(SingleStep);
			Relay_Water_Pump = 1;
 	MSDelay( 1000 );
	Relay_Water_Pump = 0;
 	MSDelay( 500 );
	
	Relay_Clean = 1;
	MSDelay( 1000 );
	Relay_Clean = 0;
 	MSDelay( 500 );
			DCM_Stop();
			MSDelay(200);
		}
		x=m;
		y--;
		DCM_Right();
		MSDelay(Perpen);
		DCM_Forward();
		MSDelay(SingleStep);
		DCM_Right();
		MSDelay(Perpen);
		DCM_Stop();
		a++;
		MSDelay(200);
	}
	MSDelay(1000);
}
void DCM_Stop(void)
{
	DCM_L0 = 0;
	DCM_L1 = 0;
	DCM_R0 = 0;
	DCM_R1 = 0;
	MSDelay( 1000 );
}

/* End user code. Do not edit comment generated here */
