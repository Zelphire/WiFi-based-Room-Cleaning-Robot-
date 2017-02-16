//--------------------------------------------------------------------------------------------------------------------
// 416_Ration_ALCD64.c
//--------------------------------------------------------------------------------------------------------------------

// AUTH:	SHASHI KIRAN
// DATE:	09/09/2013

// MODIFIED BY:
// MODIFIED DATE:

// Program to 

// Target: PROJECT BOARD of RENESAS G13 R5F100LEA (PES-49-1212)

// Tool chain: CubeSuite+

//--------------------------------------------------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------------------------------------------------

#define ALCD_RS P0.5
#define ALCD_Enable P0.6

//--------------------------------------------------------------------------------------------------------------------
// Global VARIABLES
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// Global CONSTANTS
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// Function PROTOTYPES
//--------------------------------------------------------------------------------------------------------------------

void ALCD_Init( void );
void ALCD_Message( unsigned char addr, unsigned char *data_ptr );
void ALCD_Comm( unsigned char comm_data );				// Sending Commands
void ALCD_Data( unsigned char disp_data );				// Sending Data
void MSDelay( unsigned int Milli_Sec );					// Delay of 1 milli second

//--------------------------------------------------------------------------------------------------------------------
// void ALCD_Init( void )
//--------------------------------------------------------------------------------------------------------------------
// Function Name:	void ALCD_Init( void )
// Arguments	:	No arguments
// Return Value	:	No return value
// Description	:	This function 

void ALCD_Init( void )
{

	ALCD_Comm( 0x38 );								// 2 Lines and 5x7 matrix
	ALCD_Comm( 0x0E );								// Display ON, Cursor blinking
	ALCD_Comm( 0x01 );								// Clear display Screen
	ALCD_Comm( 0x06 );								// Shift cursor right

}


//--------------------------------------------------------------------------------------------------------------------
// void ALCD_Message( char addr, char *data_ptr )
//--------------------------------------------------------------------------------------------------------------------
// Function Name:	void ALCD_Message( char addr, char *data_ptr )
// Arguments	:	2 argument used
// addr -> receives ALCD character position address.
// *data_ptr -> receives string to be displayed on ALCD
// Return Value	:	No Return value
// Description	:	Send ALCD character position address from where the data sent will 
// starts of displaying.

void ALCD_Message( unsigned char addr, unsigned char *data_ptr )
{

	ALCD_Comm( addr );	
	while( *data_ptr != '\0' )
	{
		ALCD_Data( *data_ptr );
		data_ptr++;
		MSDelay(1);							// 0.1 sec delay
	}
}


//--------------------------------------------------------------------------------------------------------------------
// void ALCD_Comm( char comm_data )
//--------------------------------------------------------------------------------------------------------------------
// Function Name:	void ALCD_Comm( char comm_data )
// Arguments	:	1 argument used
// comm_data -> it receives command for ALCD
// Return Value	:	No return value
// Description	:	This function will send command to ALCD

void ALCD_Comm(unsigned char comm_data )			// Sending commands to ALCD
{
	P7 = comm_data;
	ALCD_RS = 0;							// instruction signal
//	ALCD_R1_W0 = 0;							// write mode
	ALCD_Enable = 1;
	MSDelay(1);
	ALCD_Enable = 0;
}			


//--------------------------------------------------------------------------------------------------------------------
// void ALCD_Data( char disp_data )
//--------------------------------------------------------------------------------------------------------------------
// Function Name:	void ALCD_Data( char disp_data )
// Arguments	:	1 argument used
// disp_data -> it will receive 1 byte character data, which is display on ALCD
// Return Value	:	No return value
// Description	:	This function will display 1 byte character on ALCD

void ALCD_Data(unsigned char disp_data )			// Sending data to be displayed
{
	P7 = disp_data;
	ALCD_RS = 1;							// data signal
//	ALCD_R1_W0 = 0;							// write mode
	ALCD_Enable = 1;
	MSDelay(1);
	ALCD_Enable = 0;
}			


//-------------------------------------------------------------------------------------------------------------------
// void MSDelay( unsigned int Milli_Sec )
//--------------------------------------------------------------------------------------------------------------------
// Function Name:	void MSDelay( unsigned int Milli_Sec )
// Arguments	:	1 argument used	
// Milli_Sec -> value in this variable will give that msec 
// Return Value	:	No return value
// Description	:	This function will generate the required milli second delay based on the Milli_Sec variable.
// This function is tested on P89V51RD2 controller

void MSDelay( unsigned int Milli_Sec )
{
	 unsigned int x,y;

	for(x=0;x<Milli_Sec;x++)
	{
		for(y=0;y<3000;y++)
		{
			;
		}
	}
}







