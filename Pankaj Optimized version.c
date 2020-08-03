#include<p18f4580.h>

#define IN1 PORTCbits.RC0
#define IN2 PORTCbits.RC1
#define E PORTCbits.RC2

void delay(int a)
{
	int i,j;
	for(i=0;i<a;i++)
	for(j=0;j<100;j++);
}



int adc_val;

void pwm_val()
{
//		T2CON=0X01;   /*Prescale4 */
//    	//TMR2 = 0;
//		CCP1CON=0x0C;               /* Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4>bits*/
 
		CCPR1L= 0.0002*adc_val+0.001*adc_val ;   
				          /* Set the duty cycle period by writing to the CCPR1L register ,  calculation CCPR1L : CCP1CON<5:4> =( PR2+1)(Duty Cylcle/100)*/
                          /* CCPR1L= (64+1)(25/100)=16.25 ~16 */

		T2CONbits.T2CKPS1=0;      /* Timer2 clock prescalar select bit                            */
		T2CONbits.T2CKPS0=1;       
		T2CONbits.TMR2ON=1;       /*  Timer2 ON bit                                      */
		PR2=0.2499*adc_val;       /*TON=PR2  , calculate TON based on duty cycle   TON=Duty Cycle*Total Period(255)/100  ,   TON= 25*255/100=63.750~ 64 */

		

}


void main()
{
	
   	int i;
	
	TRISAbits.TRISA0=1;
	TRISC=0x00;
	ADCON0=0x01;
	ADCON1=0x0D;
	ADCON2=0x80;
	
    T2CON=0X01;   /*Prescale4 */
    TMR2 = 0;
    CCP1CON=0x0C;               /* Set the PWM duty cycle by writing to the CCPR1L register and CCP1CON<5:4>bits*/
 
    
	    
	while(1)
	{
		IN1 = 1;
		IN2 = 0;
		ADCON0bits.GO=1;
		while(ADCON0bits.GO==1);
			adc_val=ADRESH;
			adc_val=adc_val<<8;
			adc_val=adc_val+ADRESL;
			CCPR1L = adc_val>>2;
		
		pwm_val();
		
		

				
	}

}