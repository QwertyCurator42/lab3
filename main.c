//*****************************************************************
// Name:    Dr. Chris Coulston
// Date:    Fall 2020
// Lab:     03
// Purp: Play Hot Cross Buns (B5, A5, G4)
//
// Assisted: The entire EENG 383 class
// Assisted by: Technical documents
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

#define N       53       // Number of notes, should be 41

#define NUM_OCTAVES 2

#define QUA 15625 //Quarter
#define EIG 7813  //Eight
#define TSD 1954  //32nd

#define E4  7
#define G4  10
#define A4  0
#define AS4 1
#define B4  2
#define G5  22
#define A5  12
#define B5  14
#define C5  15
#define D5  17
#define E5  19
#define F5  20
#define REST 24

void microSecondDelay(uint16_t us);
void milliSecondDelay(uint16_t ms);

//*****************************************************************

//*****************************************************************

void main(void) {

    uint16_t halfPeriodDelay[N] = {507,568,638,16}; // microseconds
    uint16_t halfPeriodTimer[N] = {6080, 6080, 6080, 7648, 6080, 5104, 10208}; // 1:1 timer counts
    uint8_t i = 0;
    
    uint16_t scale[(NUM_OCTAVES * 12) + 1] = {               // length is 24 + 1 for rest (testing))
        18192, 17168, 16192, 15296, 14448, 13632,
        12864, 12144, 11472, 10816, 10208, 9632,
        9088, 8592, 8112, 7648, 7232, 6816,
        6432, 6080, 5728, 5408, 5104, 4816, 0
    };
    uint16_t notes[N] = {
        E5, E5,   REST, E5, REST, C5,   E5,   G5, REST, G4, C5, REST, G4,   REST, // 14 NOTES
        E4, REST, A4,   B4, AS4,  A4,   G4,   E5, G5,   A5, F5, G5,   REST, E5, C5, // 15 NOTES
        D5, B4,   REST, C5, REST, G4,   REST, E4, REST, A4, B4, AS4,  A4,   G4,  //14 NOTES
        E5, G5,   A5,   F5, G5,   REST, E5,   C5, D5,   B4                       //10 NOTES
    };
    uint16_t duration[N] = {
        EIG, EIG, EIG, EIG, EIG, EIG, QUA, QUA, QUA, QUA,
        QUA, EIG, QUA, EIG, QUA, EIG, QUA, QUA, EIG, QUA,
        QUA, QUA, QUA, QUA, EIG, EIG, EIG, QUA, EIG, EIG, 
        QUA, EIG, QUA, EIG, QUA, EIG, QUA, EIG, QUA, QUA,
        EIG, QUA, QUA, QUA, QUA, QUA, EIG, EIG, EIG, QUA,
        EIG, EIG, QUA,
    };
    
    SYSTEM_Initialize();

    for (;;) {
        
        if (TOP_BUTTON_GetValue() == 0) {
            for (i=0;i < N;i++){
                TMR0_WriteTimer(0x10000 - duration[i]);
                INTCONbits.TMR0IF = 0;
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



//*****************************************************************
// Call microseconds(1000) a number of times
//*****************************************************************

void milliSecondDelay(uint16_t ms) {

    uint16_t i;

    for (i = 0; i < ms; i++) microSecondDelay(1000);

} // end millSecond


//*****************************************************************
// Create a delay of 1uS and loop a number of times
//*****************************************************************

void microSecondDelay(uint16_t us) {

    uint16_t i;

    for (i = 0; i < us; i++) {
        asm("NOP"); // 1
        asm("NOP"); // 2
        asm("NOP"); // 3
        asm("NOP"); // 4
        asm("NOP"); // 5

        i = i;
    } // end for     
} // end microSecond()