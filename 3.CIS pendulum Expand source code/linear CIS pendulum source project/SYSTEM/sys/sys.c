#include "sys.h" 
 /**************************************************************************
Author：Minibalance
Our aliexpress：https://minibalance.aliexpress.com
**************************************************************************/
//Set vector table offset address
//NVIC_VectTab:Base site
//Offset:Offset			 
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)	 
{ 	   	 
	SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);//Set the vector table offset register of NVIC.
	//Is the vector table used in the CODE area or in the RAM area?
}
//Set up NVIC packet
//NVIC_Group:NVIC group 0~4 total 5 groups	   
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)	 
{ 
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//Three position after taking
	temp1<<=8;
	temp=SCB->AIRCR;  //Read previous settings
	temp&=0X0000F8FF; //Empty previous group
	temp|=0X05FA0000; //Write the key
	temp|=temp1;	   
	SCB->AIRCR=temp;  //Set groupings	    	  				   
}
// set NVIC
//NVIC_PreemptionPriority: preemptive priority
//NVIC_SubPriority: response priority
//NVIC_Channel: interrupt number
//NVIC_Group: interrupt packet 0~4
// note that priority should not exceed the set range! Otherwise, there will be unexpected errors.
/// group division:
// group 0:0 preemptive priority, 4 bit response priority.
// group 1:1 preemptive priority, 3 bit response priority.
// group 2:2 preemptive priority, 2 bit response priority.
// group 3:3 preemptive priority, 1 bit response priority.
// group 4:4 preemptive priority, 0 bit response priority.
// The principle of NVIC_SubPriority and NVIC_PreemptionPriority is that the smaller the value, the more priority.   
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//Set groupings
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;//Take a lower four bit  
	NVIC->ISER[NVIC_Channel/32]|=(1<<NVIC_Channel%32);//To break the position (to remove it, to reverse the operation is OK).
	NVIC->IP[NVIC_Channel]|=temp<<4;//Setting response priority and steer priority   	    	  				   
} 
// external interrupt configuration function
// only for GPIOA~G; do not include PVD, RTC and USB to wake up these three.
// parameters:
//GPIOx:0~6, representing GPIOA~G
//BITx: requires enabling bits.
//TRIM: trigger mode, 1, down rising edge; 2, up and down edge; 3, any level trigger.
// this function can only configure 1 IO ports and multiple IO ports at a time, requiring multiple calls.
// this function automatically opens corresponding interrupts and shielded lines.	    
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM) 
{
	u8 EXTADDR;
	u8 EXTOFFSET;
	EXTADDR=BITx/4;//get the number of interrupt register group.
	EXTOFFSET=(BITx%4)*4; 
	RCC->APB2ENR|=0x01;//Enable IO to reuse clock			 
	AFIO->EXTICR[EXTADDR]&=~(0x000F<<EXTOFFSET);//清除原来设置！！！
	AFIO->EXTICR[EXTADDR]|=GPIOx<<EXTOFFSET;//EXTI.BITx Mapping to GPIOx.BITx 
	//Automatic setting
	EXTI->IMR|=1<<BITx;//  Open the interrupt on line BITx
	//EXTI->EMR|=1<<BITx;//Events on line BITx are not masked (if you don't mask this sentence, it's possible on hardware, but you can't get into interrupts during software emulation!)
 	if(TRIM&0x01)EXTI->FTSR|=1<<BITx;//Event descending edge triggering on line BITx
	if(TRIM&0x02)EXTI->RTSR|=1<<BITx;//Event rising and falling edge triggering on line BITx
} 	  
// no reset of all peripherals can be performed here, otherwise the serial port will not work at least.
// reset all clock registers.	  
void MYRCC_DeInit(void)
{	
 	RCC->APB1RSTR = 0x00000000;//Resetting end			 
	RCC->APB2RSTR = 0x00000000; 
	  
  	RCC->AHBENR = 0x00000014;  //Sleep mode flash and SRAM clock enable. Other closures.	  
  	RCC->APB2ENR = 0x00000000; //The peripheral clock is closed.		   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //Enable internal high-speed clock HSION	 															 
	RCC->CFGR &= 0xF8FF0000;   //Reset SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //Reset HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //Reset HSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //Reset PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //Close all interrupts		 
	//Configuration vector table				  
#ifdef  VECT_TAB_RAM
	MY_NVIC_SetVectorTable(0x20000000, 0x0);
#else   
	MY_NVIC_SetVectorTable(0x08000000,0x0);
#endif
}
//THUMB directive does not support assembly inlining.
// using the following methods to implement the assembler instruction WFI
__asm void WFI_SET(void)
{
	WFI;		  
}
//Close all interrupts
__asm void INTX_DISABLE(void)
{
	CPSID I;		  
}
//Open all interrupts
__asm void INTX_ENABLE(void)
{
	CPSIE I;		  
}
// Set the top address of the stack
//addr: the top address of the stack
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

//Enter standby mode	  
void Sys_Standby(void)
{
	SCB->SCR|=1<<2;//Enable SLEEPDEEP位 (SYS->CTRL)	   
  	RCC->APB1ENR|=1<<28;     //Enable power clock	    
 	PWR->CSR|=1<<8;          //设置WKUP用于唤醒
	PWR->CR|=1<<2;           //清除Wake-up 标志
	PWR->CR|=1<<1;           //PDDS置位		  
	WFI_SET();				 //执行WFI指令		 
}	     
//系统软复位   
void Sys_Soft_Reset(void)
{   
	SCB->AIRCR =0X05FA0000|(u32)0x04;	  
} 		 
//JTAG模式设置,用于设置JTAG的模式
//mode:jtag,swd模式设置;00,全使能;01,使能SWD;10,全关闭;	   
//#define JTAG_SWD_DISABLE   0X02
//#define SWD_ENABLE         0X01
//#define JTAG_SWD_ENABLE    0X00		  
void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //开启辅助时钟	   
	AFIO->MAPR&=0XF8FFFFFF; //清除MAPR的[26:24]
	AFIO->MAPR|=temp;       //设置jtag模式
} 
//系统时钟初始化函数
//pll:选择的倍频数，从2开始，最大值为16		 
void Stm32_Clock_Init(u8 PLL)
{
	unsigned char temp=0;   
	MYRCC_DeInit();		  //复位并配置向量表
 	RCC->CR|=0x00010000;  //外部高速时钟使能HSEON
	while(!(RCC->CR>>17));//等待外部时钟就绪
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;//抵消2个单位
	RCC->CFGR|=PLL<<18;   //设置PLL值 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	FLASH->ACR|=0x32;	  //FLASH 2个延时周期

	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//等待PLL锁定
	RCC->CFGR|=0x00000002;//PLL作为系统时钟	 
	while(temp!=0x02)     //等待PLL作为系统时钟设置成功
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}    
}		    




























