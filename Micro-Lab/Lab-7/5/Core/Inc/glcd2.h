#ifndef __glcd2_h
#define __glcd2_h



void control_high(int pin);
void control_low(int pin);
void control_xor(int pin);
void Data_Port(int data);
void DataCom_Port_Dir(void);
void GLCD_Command(char Command)	;

void GLCD_Data(char Data)	;
void GLCD_Init();
void GLCD_ClearAll();
void GLCD_String(char page_no, char *str);
void GLCD_Image(const char* image);	
void GLCD_Animate(void);

#endif
