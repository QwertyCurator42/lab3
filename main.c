//*****************************************************************
// Name:    Polina Rygina and Conner Barnes
// Date:    Fall 2023
// Lab:     03
// Purp: Play Super Mario Bros 1-1 Theme
//
// Assisted: 
// Assisted by:  
//
// Academic Integrity Statement: I certify that, while others may have
// assisted me in brain storming, debugging and validating this program,
// the program itself is my own work. I understand that submitting code
// which is the work of other individuals is a violation of the course
// Academic Integrity Policy and may result in a zero credit for the
// assignment, course failure and a report to the Academic Dishonesty
// Board. I also understand that if I knowingly give my original work to
// another individual that it could also result in a zero credit for the
// assignment, course failure and a report to the Academic Dishonesty
// Board.
//*****************************************************************
#include "mcc_generated_files/mcc.h"
#pragma warning disable 520     
#pragma warning disable 1498

#define N       55       // Number of notes

#define NUM_OCTAVES 2

#define QUA 15625 //Quarter
#define TRIP_QUA 10417 //Quarter in a triplet
#define EIG 7813  //Eight
#define TSD 1954  //32nd

#define A4  0
#define AS4 1
#define B4  2
#define E4  7
#define G4  10
#define A5  12
#define B5  14
#define C5  15
#define D5  17
#define E5  19
#define F5  20
#define G5  22
#define A6  24
#define REST 25

//*****************************************************************

//*****************************************************************

void main(void) {
    uint8_t i = 0;
    
    uint16_t scale[(NUM_OCTAVES * 12) + 2] = {               // length is 24 + 2 for rest, and A6 
        18192, 17168, 16192, 15296, 14448, 13632,
        12864, 12144, 11472, 10816, 10208, 9632,
        9088, 8592, 8112, 7648, 7232, 6816,
        6432, 6080, 5728, 5408, 5104, 4816, 4560,0
    };
    uint16_t notes[N] = {
        E5, E5, REST, E5, REST, C5, E5,
        G5, REST, G4, REST,  
        C5, REST, G4, REST, E4, 
        REST, A4, B4, AS4, A4,  
        G4, E5, G5, A6, F5, G5, 
        REST, E5, C5, D5, B4, REST,     
        C5, REST, G4, REST, E4, 
        REST, A4, B4, AS4, A4,  
        G4, E5, G5, A6, F5, G5,
        REST, E5, C5, D5, B4, REST                 
    };
    uint16_t duration[N] = {
        EIG, EIG, EIG, EIG, EIG, EIG, QUA,              //Measure 1
        QUA, QUA, QUA, QUA,                             //Measure 2
        QUA, EIG, QUA, EIG, QUA,                        //Loop 1: Measure 1
        EIG, QUA, QUA, EIG, QUA,                        //Loop 1: Measure 2 
        TRIP_QUA, TRIP_QUA, TRIP_QUA, QUA, EIG, EIG,    //Loop 1: Measure 3
        EIG, QUA, EIG, EIG, QUA, EIG,                   //Loop 1: Measure 4
        QUA, EIG, QUA, EIG, QUA,                        //Loop 2: Measure 1
        EIG, QUA, QUA, EIG, QUA,                        //Loop 2: Measure 2 
        TRIP_QUA, TRIP_QUA, TRIP_QUA, QUA, EIG, EIG,    //Loop 2: Measure 3
        EIG, QUA, EIG, EIG, QUA, EIG                    //Loop 2: Measure 4
    };
    
    SYSTEM_Initialize();

    for (;;) {
        if (TOP_BUTTON_GetValue() == 0) {   //When button is pressed
            for (i=0;i < N;i++){            //Run through all notes
                TMR0_WriteTimer(0x10000 - duration[i]);  //Set note duration
                INTCONbits.TMR0IF = 0;                  //Set ovf bit
                while (TMR0_HasOverflowOccured() == false){   
                    if (scale[notes[i]]!=0){ 
                        TMR1_WriteTimer(0x10000 - scale[notes[i]]); 
                        PIR1bits.TMR1IF = 0;
                        while (TMR1_HasOverflowOccured() == false);
                        SPEAKER_PIN_Toggle();
                    }
                }
                TMR0_WriteTimer(0x10000 - TSD);
                INTCONbits.TMR0IF = 0;
                while (TMR0_HasOverflowOccured() == false);
            }// end duration
        } // end pressed button   
    } // end infinite loop    
} // end main
