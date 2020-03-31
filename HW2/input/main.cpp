#include "mbed.h"

BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);
char table[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x0};

Serial pc( USBTX, USBRX );

AnalogIn Ain(A0);

float ADCdata;

Timer t;



float previoustime = 0;        

float interval = 1; //if 2 ,means 2 seconds.


float currenttime = t.read();

DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);

int ledState = 0;

int counter = 0;

int sine_state = 0;

int number = 0;
int n1 = 0;
int n2 = 0;
int n3 = 0;

DigitalIn  Switch(SW3);


DigitalOut decimal(D8);



float seconds;


float sine;

AnalogOut Aout(DAC0_OUT);



int sample = 1500;

int i;

float sampledata[1500];




int main(){

    t.start();

    

    while(1){

        currenttime = t.read();

        if(currenttime - previoustime > interval) { //go into every 2 seconds
            previoustime = currenttime; 
            
         
            
            number = counter; //update every 1 second !!!!!!!!!!
            
            counter = 0;
        }


        ADCdata = Ain;
        //pc.printf("%1.3f\r\n", ADCdata);
        
        if((ADCdata > 0.3) && (sine_state == 0)){
            counter++;
            sine_state = 1;
        }
        
        if(ADCdata < 0.2){
            sine_state = 0;
        }
        
        n3 = number % 10;
       
        n2 = ((number - n3)%100) / 10;
        n1 = number / 100 ;

        //display = table[number];

        redLED = 1;
        greenLED = 0;
        

        if(Switch == 0){

            redLED = 0;
            greenLED = 1;

            display = table[n1];
            wait(1);

            display = table[n2];
            wait(1);

            display = table[n3];
            decimal = 1;
            wait(1);

            display = table[10];
            decimal = 0;
            
        }

        /*
        for (i = 0; i < sample; i++){


        sampledata[i] = Ain;

        wait(1./sample);

        }

        for (i = 0; i < sample; i++){

        pc.printf("%1.3f\r\n", sampledata[i]);

        wait(0.002);

        }
        */
        
        seconds = t.read();

        sine =  0.5+0.5*sin(2*3.141*number*seconds);

        Aout = sine;

        

        

    }

    
        



        

}





    




