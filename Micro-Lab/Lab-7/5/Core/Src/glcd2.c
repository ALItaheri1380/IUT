#include "stm32f407xx.h"

#include <stdio.h>					
#include "Font_Header.h"
#include "Image.h"

#define RS					8		/* Define control pins on GPIOE*/
#define RW					9
#define EN					10
#define CS1					12
#define CS2					13
#define RST					14

#define TotalPage			8


void control_high(int pin)
	{
			GPIOE->ODR |=(1<< pin);	
		}
	
	void control_low(int pin)
	{

		GPIOE->ODR &=~(1<< pin);
}
	void control_xor(int pin)
	{
		GPIOE->ODR ^=(1<< pin);
		}
	
		void Data_Port(int data)
	{
		
		GPIOE->ODR=(GPIOE->ODR &0xffffff00)| (data &0x000000ff);
	}
	
	void DataCom_Port_Dir(void)
	{
			RCC->AHB1ENR |= 0x10;//(1<<4);  GPIOE
		
			GPIOE->MODER  = 0x55555555;
			GPIOE->OTYPER = 0x00000000;  
			GPIOE->OSPEEDR =0xAAAAAAAA;  
			GPIOE->PUPDR =0x00000000;  //  0:0 --> no pull up or pulldown
	
	}
	
	
	
/********************************************************************/
	
void GLCD_Command(char Command)		/* GLCD command function */
{
	Data_Port(Command);			
	control_low(RS);		/* Make RS LOW to select command register */
	
  control_low(RW);		/* Make RW LOW to select write operation */
  control_high(EN);	/* Make HIGH to LOW transition on Enable pin */
	Delay_us(5);
	control_low(EN);
	Delay_us(5);
}

void GLCD_Data(char Data)			/* GLCD data function */
{
	Data_Port(Data);				/* Copy data on data pin */
	control_high(RS); 	/* Make RS HIGH to select data register */
	control_low(RW);  /* Make RW LOW to select write operation */
  control_high(EN);/* Make HIGH to LOW transition on Enable pin */
	Delay_us(5);
	control_low(EN);
	Delay_us(5);
}

void GLCD_Init()					/* GLCD initialize function */
{
	DataCom_Port_Dir();
	
	/* Select both left & right half of display & Keep reset pin high */
	
	control_high(CS1);
	control_high(CS2);
	control_high(RST);
	
	Delay_ms(20);
	GLCD_Command(0x3E);				/* Display OFF */
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
	GLCD_Command(0xC0);				/* Set z address (start line=0) */
	GLCD_Command(0x3F);				/* Display ON */
}



void GLCD_ClearAll()				/* GLCD all display clear function */
{
	int i,j;
	/* Select both left & right half of display */
	control_high(CS1);
	control_high(CS2);
	
	for(i = 0; i < TotalPage; i++)
	{
		GLCD_Command((0xB8) + i);	/* Increment page each time after 64 column */
		for(j = 0; j < 64; j++)
		{
			GLCD_Data(0);			/* Write zeros to all 64 column */
		}
	}
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
}

void GLCD_String(char page_no, char *str)			/* GLCD string write function */
{
	unsigned int i, column;
	unsigned int Page = ((0xB8) + page_no);
	unsigned int Y_address = 0;
	float Page_inc = 0.5;
	
	control_high(CS1);
	control_low(CS2);


	
	GLCD_Command(Page);
	for(i = 0; str[i] != 0; i++)					/* Print each char in string till null */
	{
		if (Y_address > (1024-(((page_no)*128)+FontWidth))) /* Check Whether Total Display get overflowed */
		break;										/* If yes then break writing */
		if (str[i]!=32)								/* Check whether character is not a SPACE */
		{
			for (column=1; column<=FontWidth; column++)
			{
				if ((Y_address+column)==(128*((int)(Page_inc+0.5))))	/* If yes then check whether it overflow from right side of display */
				{
					if (column == FontWidth)		/* Also check and break if it overflow after 5th column */
					break;
					GLCD_Command(0x40);				/* If not 5th and get overflowed then change Y address to START column */
					Y_address = Y_address + column;	/* Increment Y address count by column no. */
					control_xor(CS1);		/* If yes then change segment controller to display on other half of display */
					control_xor(CS2);
					GLCD_Command(Page + Page_inc);	/* Execute command for page change */
					Page_inc = Page_inc + 0.5;		/* Increment Page No. by half */
				}
			}
		}
		if (Y_address>(1024-(((page_no)*128)+FontWidth)))   /* Check Whether Total Display get overflowed */
		break;										/* If yes then break writing */
		if((font[((str[i]-32)*FontWidth)+4])==0 || str[i]==32)/* Check whether character is SPACE or character last column is zero */
		{
			for(column=0; column<FontWidth; column++)
			{
				GLCD_Data(font[str[i]-32][column]);	/* If yes then then print character */
				if((Y_address+1)%64==0)				/* check whether it gets overflowed  from either half of side */
				{
					control_xor(CS1);		/* If yes then change segment controller to display on other half of display */
					control_xor(CS2);
					GLCD_Command((Page+Page_inc));	/* Execute command for page change */
					Page_inc = Page_inc + 0.5;		/* Increment Page No. by half */
				}
				Y_address++;						/* Increment Y_address count per column */
			}
		}
		else										/* If character is not SPACE or character last column is not zero */
		{
			for(column=0; column<FontWidth; column++)
			{
				GLCD_Data(font[str[i]-32][column]); /* Then continue to print hat char */
				if((Y_address+1)%64==0)				/* check whether it gets overflowed  from either half of side */
				{
					control_xor(CS1);		/* If yes then change segment controller to display on other half of display */
					control_xor(CS2);
					GLCD_Command((Page+Page_inc));	/* Execute command for page change */
					Page_inc = Page_inc + 0.5;		/* Increment Page No. by half */
				}
				Y_address++;						/* Increment Y_address count per column */
			}
			GLCD_Data(0);							/* Add one column of zero to print next character next of zero */
			Y_address++;							/* Increment Y_address count for last added zero */
			if((Y_address)%64 == 0)					/* check whether it gets overflowed  from either half of side */
			{
				control_xor(CS1);		/* If yes then change segment controller to display on other half of display */
				control_xor(CS2);
				GLCD_Command((Page+Page_inc));		/* Execute command for page change */
				Page_inc = Page_inc + 0.5;			/* Increment Page No. by half */
			}
		}
	}
	GLCD_Command(0x40);								/* Set Y address (column=0) */
}


void GLCD_Image(const char* image)	/* GLCD string write function */
{
	int column,page,page_add=0xB8,k=0;
	float page_inc=0.5;
	char byte;

	control_high(CS1);	/* Select first Left half of display */
	control_low(CS2);
	
	for(page=0;page<16;page++)		/* Print 16 pages i.e. 8 page of each half of display */
	{
		for(column=0;column<64;column++)
		{
			byte = pgm_read_byte(&image[k+column]);
			GLCD_Data(byte);		/* Print 64 column of each page */
		}
		control_xor(CS1);	/* If yes then change segment controller */
		control_xor(CS2);
		GLCD_Command((page_add+page_inc));/* Increment page address */
		page_inc=page_inc+0.5;
		k=k+64;						/* Increment pointer */
	}
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
}

	void GLCD_Animate(void){
	GLCD_Init();					/* Initialize GLCD */
		
	GLCD_ClearAll();				/* Clear all GLCD display */

  GLCD_String(0,"Microlab STM32f407 1403");			/* Print String on 0th page of display */	
	Delay_ms(2000);
	while(1){
		
	GLCD_Image(img);
	Delay_ms(500);
	GLCD_Image(img1);
	Delay_ms(500);
	}
}
