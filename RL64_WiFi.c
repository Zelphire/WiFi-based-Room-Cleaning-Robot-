//--------------------------------------------------------------------------------------------------------------------
//	RL64_WiFi.c
//--------------------------------------------------------------------------------------------------------------------
// AUTH:	SHASHI KIRAN
// DATE:	18/11/2015

// MODIFIED BY:
// MODIFIED DATE:

// Project:

// Target: 

// Tool chain: 

//--------------------------------------------------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------------------------------------------------



//--------------------------------------------------------------------------------------------------------------------
// Global VARIABLES
//--------------------------------------------------------------------------------------------------------------------

//unsigned char GPRS_Comm_Err_Count;
//unsigned char Control_Z = 0x1A;
unsigned char WIFI_OK_Flag;
//unsigned char GPRS_ERROR_Flag;

extern unsigned char Rx_data_arr0[400];
extern unsigned char Rx_count0;
extern unsigned char Rx_ST_Flag0;
extern unsigned char Rx_data0;


//--------------------------------------------------------------------------------------------------------------------
// Global CONSTANTS
//--------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------
// Function PROTOTYPES
//--------------------------------------------------------------------------------------------------------------------
unsigned char Temp_Str_Length;

unsigned char WiFi_Data_Str_Length_Arr[5]="00\r\n";

void WiFi_Init_Comm( void );
void WiFi_Send( unsigned char *WiFi_Data_Str_Ptr, unsigned char WiFi_Data_Str_Length );


//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------

void WiFi_Init_Comm( void )
{
	unsigned char i;
	
	ALCD_Comm( 0x01 );								// Clear display Screen
	MSDelay(100);	

	Rx_ST_Flag0 = 0;
	Rx_count0 = 0;

//	R_UART1_Send( "AT\r", 3 );
//	ALCD_Message( 0x80, "AT");
//	MSDelay(2000);
		
	R_UART0_Send( "AT+CIPMUX=1\r\n", 13 );
	ALCD_Message( 0x80, "AT+CIPMUX=1" );
	MSDelay(5000);

	while(1)
	{
		Rx_ST_Flag0 = 0;
		Rx_count0 = 0;
		R_UART0_Send( "AT+CIPSERVER=1,80\r\n", 19 );
		ALCD_Message( 0x80, "AT+CIPSERVER=1,80" );
		MSDelay(2000);
		ALCD_Message( 0x80,"WAIT              " );
		MSDelay(10000);	
		ALCD_Message( 0xC0,"SCAN              " );
		MSDelay(1000);
		WIFI_OK_Flag = 0;
		if( Rx_ST_Flag0 == 1 )
		{
			ALCD_Message( 0x80, Rx_data_arr0 );
			MSDelay(2000);
//			ALCD_Message( 0xC0,"      DATA RX     " );
			for(i=0; i<40; i++)
			{
				if( (Rx_data_arr0[i]=='O') && (Rx_data_arr0[i+1]=='K') )                     //OK
				{
					ALCD_Message( 0xC0,"        OK       " );
					WIFI_OK_Flag = 1;
					break;
				}
				else if( (Rx_data_arr0[i]=='C') && (Rx_data_arr0[i+1]=='O') &&(Rx_data_arr0[i+2]=='N') && (Rx_data_arr0[i+3]=='N') )                     //OK
				{
					ALCD_Message( 0xC0,"    0,CONNECT    " );
					WIFI_OK_Flag = 1;
					break;
				}
				else if( (Rx_data_arr0[i]=='E') && (Rx_data_arr0[i+1]=='R') && (Rx_data_arr0[i+2]=='R') && (Rx_data_arr0[i+3]=='O'))
				{
					ALCD_Message( 0xC0,"      ERROR      " );
					break;
				}
			}
			if( WIFI_OK_Flag == 1 )
				break;
		}
	}
	MSDelay(2000);
	ALCD_Comm( 0x01 );								// Clear display Screen
	MSDelay(100);	
}


void WiFi_Send( unsigned char *WiFi_Data_Str_Ptr, unsigned char WiFi_Data_Str_Length )
{
	unsigned char i;
	
	Temp_Str_Length = WiFi_Data_Str_Length;
	
	WiFi_Data_Str_Length_Arr[1] = (Temp_Str_Length%10)+48;
	WiFi_Data_Str_Length_Arr[0] = (Temp_Str_Length/10)+48;
	
	Rx_ST_Flag0 = 0;
	Rx_count0 = 0;
	
	R_UART0_Send( "AT+CIPSEND=0,", 13 );
	MSDelay(100);
	R_UART0_Send( WiFi_Data_Str_Length_Arr, 4 );
	MSDelay(2000);
	Rx_ST_Flag0 = 0;
	Rx_count0 = 0;
	R_UART0_Send( WiFi_Data_Str_Ptr, WiFi_Data_Str_Length );
//	MSDelay(3000);
//	R_UART1_Send( &Control_Z, 1 );
	MSDelay(5000);
	Rx_ST_Flag0 = 0;
	Rx_count0 = 0;
	MSDelay(100);
}

