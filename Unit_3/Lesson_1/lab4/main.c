/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Eng MANAL
 * @brief          : Main program body
 ******************************************************************************
 */
#define SYSCTL_RCGC2_R (*((volatile unsigned long*)0x400FE108))// put in this pointer a value
#define GPIO_PORTF_DIR_R (*((volatile unsigned long*)0x40025400))//long to make sure that it is 4 bytes , int may be 2 or 4
#define GPIO_PORTF_DEN_R (*((volatile unsigned long*)0x4002551C))
#define GPIO_PORTF_DATA_R (*((volatile unsigned long*)0x400253FC))


int main()
{
	volatile unsigned long delay_count ;
	SYSCTL_RCGC2_R = 0x20; 
	//delay to make sure GPIO is up and running
	for(delay_count=0 ; delay_count < 200 ; delay_count++);// delay_count not used so it might be deleted in optmization so volatile
	GPIO_PORTF_DIR_R |= 1<<3 ; // set bet 3 so make pin3 is output pin
	GPIO_PORTF_DEN_R |= 1<<3 ; // enable pin3
	
	while(1)
	{
		
		GPIO_PORTF_DATA_R |= 1<<3 ;
		for(delay_count=0 ; delay_count < 200000 ; delay_count++);
		GPIO_PORTF_DATA_R &= ~ (1<<3) ;
		for(delay_count=0 ; delay_count < 200000 ; delay_count++);
		
		
	}
	
	
	
}