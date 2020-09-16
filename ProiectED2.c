int digit=0,s=0,m=0,ms=0, h=0;

int h_up=-1, h_down=-1, m_up=-1, m_down=-1, time=0, time2=0;

int adc_l, adc_h;

int IN0=-1, seth=-1, setm=-1;

///display si activare motor

//void afi(int m,int s);
void display (int p, int c)
{
PORTB &=0b00000000;
PORTC &=0b00000000;

      switch(c){
   case 0:
       PORTC |=~0b00111111; break;
   case 1:
       PORTC |=~0b00000110; break;
   case 2:
       PORTC |=~0b01011011; break;
   case 3:
       PORTC |=~0b01001111; break;
  case 4:
       PORTC |=~0b01100110; break;
   case 5:
       PORTC |=~0b01101101; break;
   case 6:
       PORTC |=~0b01111101; break;
   case 7:
       PORTC |=~0b00000111; break;
    case 8:
       PORTC |=~0b01111111; break;
    case 9:
       PORTC |=~0b01101111; break;
    case -1:
         PORTC |=~0b01000000; break;


 }
 switch(p){

  case 1:
       PORTB |=(1<<3); break;
   case 2:
       PORTB |=(1<<2); break;
   case 3:
       PORTB |=(1<<1); break;
   case 4:
       PORTB |=(1<<0); break;
   case -1:
       PORTB |=(1<<2);
       PORTB |=(1<<3); break;
   case -2:
        PORTB |=(1<<1);
        PORTB |=(1<<0); break;
 }
 Delay_ms(4);
}

void func_set_care_ceas() iv IVT_ADDR_INT0
{
     IN0++;
     if(IN0==7)
     {
            IN0=0;
            s=setm;     //m=setm;
                m=seth;           //h=seth;
     }

     else
         digit=0;

}

void func_modificare_ceas() iv IVT_ADDR_INT1
{
     if(IN0==1)
     {
               seth++;
               if(seth==24)
                           seth=0;
     }
     if(IN0==2)
     {
                 setm++;
                 if(setm==60)
                           setm=0;
     }
     if(IN0==3)
     {

               h_up++;
               if(h_up==24)
                           h_up=0;
     }
     if(IN0==4)
     {
                 m_up++;
                 if(m_up==60)
                           m_up=0;
     }
     if(IN0==5)
     {
                 h_down++;
                 if(h_down==24)
                           h_down=0;
     }
     if(IN0==6)
     {
                 m_down++;
                 if(m_down==60)
                           m_down=0;
     }

}

void Init_INT0(){
GICR |= (1<<6); // activarea întreruperii externe INT0
MCUCR |= 0b00000011;

}
void Init_INT1(){
GICR |= (1<<7); // activarea întreruperii externe INT0
MCUCR |= 0b00001100;

}

void init_timer(){

    TCCR0 = 0b00001011; //CTC-3,6; Prescaler-0,1,2
    TCNT0 = 0;
    OCR0 = 125;
    TIMSK |= 0b00000010; //set interrupt OCM
}
/*
void afi(int *ttime, int which)
{
     int time=ttime;
             if(time!=-1)
              {
                   digit++;
                   switch(digit){
                        case 1: display(which*2-1,time%10); break;
                        case 2: display(which*2,(time/10)%10); digit=0; break;
                   }
                   if(which==2)
                   {
                          display(1,-1);
                          display(2,-1);
                   }
                   else
                   {
                           display(3,-1);
                           display(4,-1);
                   }

              }
              else{
                    if(time==-1)
                                time++;
                    if(which==2)
                    {
                               display(-1,-1);
                             display(-2,0);
                    }
                    else
                    {
                             display(-2,-1);
                                display(-1,0);
                    }

              }
              ttime=time;
}
*/
void nr_rotati();
void Timer1_OC_ISR() iv IVT_ADDR_TIMER0_COMP { //ISR

     if(IN0==0)                              /// cu h si cu m
     {         PORTD=0x00;
               digit++;
                 switch(digit){
                      case 1: display(1,s%10); break;
                      case 2: display(2,(s/10)%10); break;
                      case 3: display(3,m%10); break;
                      case 4: display(4,(m/10)%10); digit=0; break;
                 }
     }
     else
     {
         /*if(IN0==1)
         {

              afi(&seth, 2);

         } */
         if(IN0==1)
         {             PORTD=0b00000001;
              if(seth!=-1)
              {
                   digit++;
                   switch(digit){
                        case 1: display(3,seth%10); break;
                        case 2: display(4,(seth/10)%10); digit=0; break;
                   }
                   display(1,-1);
                   display(2,-1);
              }
              else{
                    if(seth==-1)
                                seth++;
                     display(-1,-1);
                     display(-2,0);
              }
         }
         if(IN0==2)
         {
              if(setm!=-1)
              {
                   digit++;
                   switch(digit){
                        case 1: display(1,setm%10); break;
                        case 2: display(2,(setm/10)%10); digit=0; break;
                   }
                   display(3,-1);
                   display(4,-1);
              }
              else{
                    if(setm==-1)
                                setm++;
                     display(-2,-1);
                     display(-1,0);
              }
         }

         if(IN0==3)
         {

                PORTD=0b00000010;

                if(h_up!=-1)
                {
                     digit++;
                     switch(digit){
                          case 1: display(3,h_up%10); break;
                          case 2: display(4,(h_up/10)%10); digit=0; break;
                     }
                     display(1,-1);
                     display(2,-1);
                }
                else{
                      if(h_up==-1)
                                  h_up++;
                       display(-1,-1);
                       display(-2,0);
                }

         }
         if(IN0==4)
         {
                if(m_up!=-1)
                {
                     digit++;
                     switch(digit){
                          case 1: display(1,m_up%10); break;
                          case 2: display(2,(m_up/10)%10); digit=0; break;
                     }
                     display(3,-1);
                     display(4,-1);
                }
                else{
                      if(m_up==-1)
                                  m_up++;
                       display(-1,-1);
                       display(-2,0);
                }
         }
         if(IN0==5)
         {
                   PORTD=0b00010000;
                if(h_down!=-1)
                {
                     digit++;
                     switch(digit){
                          case 1: display(3,h_down%10); break;
                          case 2: display(4,(h_down/10)%10); digit=0; break;
                     }
                     display(1,-1);
                     display(2,-1);
                }
                else{
                      if(h_down==-1)
                                  h_down++;
                       display(-2,-1);
                       display(-1,0);
                }
         }
         if(IN0==6)
         {
                if(m_down!=-1)
                {
                     digit++;
                     switch(digit){
                          case 1: display(1,m_down%10); break;
                          case 2: display(2,(m_down/10)%10); digit=0; break;
                     }
                     display(3,-1);
                     display(4,-1);
                }
                else{
                      if(m_down==-1)
                                  m_down++;
                       display(-1,-1);
                       display(-2,0);
                }
         }
     }
   /*
    switch(s){
        case 5: PORTA=0x01;
         break;
        case 10: PORTA=0x02;
         break;
        }
   */
    if (ms == 99){
      s++;
      ms = 0;

              if(m==h_down && s==m_down)  //        if(h==h_down && m==m_down)
              {
                                        time=6;
                                    PORTA=0x03;
              }
              else if(m==h_up && s==m_up)     //if(h==h_up && m==m_up)
              {                         time=6;
                                    PORTA=0x01;
              }
              if(s==m_down+time || s==m_up+time)             //if(s==time)
                                PORTA=0x00;
      if(s == 60){
               s = 0;
               m++;
      }
      if(m ==60)
      {
           m=0;
           h++;
      }
    }
    else ms++;
    if(h==24)
             h=0;

}
/*
void nr_rotati(int direction)
{
     if(direction==1)
     {
                     PORTB |=(1<<6)|(1<<5);
     }
     else if(direction==2)
     {
                     PORTB |=(0<<6)|(1<<5);
     }
     else
           PORTB |=(0<<5);

}
  */
///main

void main() {
     DDRA=0b00000011;
     DDRB=0b00111111;
     DDRD |=0b11110011;
     DDRC |=0b11111111;
     Init_INT0();
     Init_INT1();
     init_timer()  ;

     SREG = 1<<7;

}