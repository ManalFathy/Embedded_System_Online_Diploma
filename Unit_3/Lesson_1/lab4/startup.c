// startup.cabs
//Eng. Manal

#include <stdint.h>
extern int main(void);

void Reset_Handler();
void Default_Handler()
{
	Reset_Handler();
}

void NMI_Handler() __attribute__((weak,alias("Default_Handler")));
void H_fault_Handler() __attribute__((weak,alias("Default_Handler")));
// booking 1024 byte located by .bss through uninitializes arrary of int 256 element(256*4=1024) 

static unsigned long stack_top[256];

void (* const g_p_fn_vectors[])() __attribute__((section(".vectors")))  =
{
	 (void (*)()) ((unsigned long )stack_top + sizeof(stack_top)) ,
	 &Reset_Handler ,
	 &NMI_Handler ,
	 &H_fault_Handler ,
};
extern unsigned int _E_text; // they are symbols not variabls have add not value SO when dealing with them use& 
extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;


void Reset_Handler()
{ //copy data section from flash to ram
	unsigned int DATA_SIZE = (unsigned char*) &_E_DATA -(unsigned char*) &_S_DATA;
	unsigned char* P_src = (unsigned char*)&_E_text; // cating to char to copy byte by byte
	unsigned char* P_det = (unsigned char*)&_S_DATA;
	for(int i=0 ; i < DATA_SIZE ; i++)
	{
		*((unsigned char*)(P_det++)) = *((unsigned char*)(P_src++));
	}
	
	//initialize .bss in sram =0
	unsigned int bss_SIZE = (unsigned char*) &_E_bss -(unsigned char*) &_S_bss;
	P_det = (unsigned char*)&_S_bss;
	for(int i=0 ; i < bss_SIZE ; i++)
	{
		*((unsigned char*)(P_det++)) = (unsigned char)0;
	}
	//jump to main()
	main();
}
