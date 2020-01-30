//Used CLion to complete the task

/// THOUGHT PROCESS------------------------------------------------------------------------
// STEP 1: CONVERT HEX INPUT DATA INTO BINARY AND CONCATENATE BINARY OUTPUT
// STEP 2: SEPARATE THE DATA AFTER EVERY 12 BITS TO MAKE 8 CHANNELS(12 BITS PER CHANNEL)
// STEP 3: DECODE EACH BIT OF EVERY CHANNEL AND STORE IT IN THE PREDEFINED STRUCT IN THE HEADER FILE
// STEP 4: EVEN PARITY CHECK TO BE PERFORMED IN [0-7] BITS OF EVERY CHANNEL AND PARITY STATUS TO BE STORED IN THE PREDEFINED STRUCT
// STEP 5: PRINT OUT ALL THE CHANNELS ALONG WITH THE ITS ATTRIBUTES(VALUE, STATUS, FLAGS, PARITY)

// OUTPUT WILL BE OF THE FOLLOWING ORDER:
// CHANNEL NUMBER: {1,2,3,4,5,6,7,8}
// STATUS: {0 -> if status bit is 0} {1 -> if status bit is 1}
// Flag A: {0 -> if flag_a bit is clr/0} {1 -> if flag_a bit is set/1}
// Flag B: {0 -> if flag_b bit is clr/0} {1 -> if flag_b bit is set/1}
// Flag C: {0 -> if flag_c bit is clr/0} {1 -> if flag_c bit is set/1}
// Parity: {0 -> if the number of bits in the value bits [0-7] are even} {1 -> if the number of bits in the value bits [0-7] are odd}
// Value: {Value bits [0-7] are represented in HEX CODE}


#include <stdint.h> // For unit8_t
#include <stdio.h>  // For printf/sprintf
#include <string.h> // For concatenation and strlen
#include "emb_test.h"   // Header file with enums, structs and struct initialization



///FUNCTION HEADERS-----------------------------------------------------------------------------
// Header for hex2bin function
char * hex2bin(char*);
// Header for bin2hex function
int bin2hex(int);
// Header for read_channels function
void read_channels(void*, void*);



///GIVEN DATA---------------------------------------------------------------------------------
// Given input data in Hex
const uint8_t input_data[12] =
        {
                0xF0, 0x24, 0xF8, 0xC0, 0x4B, 0x1B,
                0x68, 0x4F, 0xF0, 0xFF, 0x31, 0x18,
        };



///DRIVER CODE------------------------------------------------------------------------------------
int main(void)
{
    read_channels(input_data, output);
}



///FUNCTION DEFINITIONS----------------------------------------------------------------------------
// Function to convert input data from Hex to Binary
// Takes array of char to store the converted binary values and returns a char pointer
char * hex2bin(char *bin){

    // Char to store hex value from input_data
    char hex[17];

    // Length of input_data calculation
    int lengthOfInputData = sizeof(input_data)/ sizeof(input_data[0]);

    // Loop till the last element in input_data
    for (int j = 0; j < lengthOfInputData; j++) {

        // Store hex value in hex from input_data one at a time
        sprintf(hex, "%x", input_data[j]);

        // Loop through every hex value until null termination
        for (int i = 0; hex[i] != '\0'; i++) {
            switch (hex[i]) {
                // strcat to concatenate appropriate binary value to bin
                case '0':
                    strcat(bin, "0000");
                    break;
                case '1':
                    strcat(bin, "0001");
                    break;
                case '2':
                    strcat(bin, "0010");
                    break;
                case '3':
                    strcat(bin, "0011");
                    break;
                case '4':
                    strcat(bin, "0100");
                    break;
                case '5':
                    strcat(bin, "0101");
                    break;
                case '6':
                    strcat(bin, "0110");
                    break;
                case '7':
                    strcat(bin, "0111");
                    break;
                case '8':
                    strcat(bin, "1000");
                    break;
                case '9':
                    strcat(bin, "1001");
                    break;
                case 'a':
                case 'A':
                    strcat(bin, "1010");
                    break;
                case 'b':
                case 'B':
                    strcat(bin, "1011");
                    break;
                case 'c':
                case 'C':
                    strcat(bin, "1100");
                    break;
                case 'd':
                case 'D':
                    strcat(bin, "1101");
                    break;
                case 'e':
                case 'E':
                    strcat(bin, "1110");
                    break;
                case 'f':
                case 'F':
                    strcat(bin, "1111");
                    break;
                default:
                    printf("Invalid HEX code");
            }   // End of switch
        }   // End of inner for loop
    }   // End of outer for loop

    return bin; // Function returns the updated bin (Concatenated binary value of all the hex values from input_data)
}

// Function to convert given binary value to hex value
// Returns int type hex value of the given int type binary value
int bin2hex(int x){
    // Converting Binary(int value) to Hex to store it to uint8_t data type in control_channel_t Struct
    int binVal = x, hexVal = 0, i = 1, remainder;

    while (binVal != 0) {
        remainder = binVal % 10;
        hexVal = hexVal + remainder * i;
        i = i * 2;
        binVal = binVal / 10;
    }   // End of while loop, hexVal stores the HEX code for the Binary input given
    return hexVal;
}

// Function to read the binary value and separate to its appropriate variable in the predefined struct in the header file
void read_channels(void* data_in, void* data_out){
    // Initialization of Char to store combined binary value (although 12 X 8 = 96)
    char bin[100] = "";

    // Converts and concatenates into binary for all the input_data in hex code
    // Returns the updated array of char (bin)
    hex2bin(bin);

    //printf("Binary number = %s\n", bin);  // CODE TESTING PURPOSE ONLY

    // Storing the length of bin that are actually occupied
    unsigned int lengthOfBin = strlen(bin);

    //printf("Length of bin: %d\n\n", lengthOfBin); // CODE TESTING PURPOSE ONLY

    // Initialize 8 char array to separate combined binary value into 8 different channels (13 because last bit for null termination)
    char one [13];
    char two [13];
    char three [13];
    char four [13];
    char five [13];
    char six [13];
    char seven [13];
    char eight [13];


    // Copy 12 bits per channel starting from (0-11), (12-23), ...., (84-95)
    strncpy(one, &bin[0], 12);
    strncpy(two, &bin[12], 12);
    strncpy(three, &bin[24], 12);
    strncpy(four, &bin[36], 12);
    strncpy(five, &bin[48], 12);
    strncpy(six, &bin[60], 12);
    strncpy(seven, &bin[72], 12);
    strncpy(eight, &bin[84], 12);


    //Since strncpy was used(no null termination), we need to add the null termination at the end of each channel
    one[12] = '\0';
    two[12] = '\0';
    three[12] = '\0';
    four[12] = '\0';
    five[12] = '\0';
    six[12] = '\0';
    seven[12] = '\0';
    eight[12] = '\0';


    // Printing out the separated channels from channel 1 through channel 8
    printf("Channel 1: %s\n", one);
    printf("Channel 2: %s\n", two);
    printf("Channel 3: %s\n", three);
    printf("Channel 4: %s\n", four);
    printf("Channel 5: %s\n", five);
    printf("Channel 6: %s\n", six);
    printf("Channel 7: %s\n", seven);
    printf("Channel 8: %s\n", eight);



    // Initialization for the typedef enums defined in the header file
    ctrl_stat_t statusOne;
    ctrl_flag_t flagAOne;
    ctrl_flag_t flagBOne;
    ctrl_flag_t flagCOne;
    ctrl_parity_t parityOne;

    // Separating channel to its own sections for value, flags, and status
    // Outer for loop, loops for all the 8 channels that was separated above
    for(int j = 0; j < 8; j++) {

        // Below initializations resets every loop such that no new variables required for every channel
        // Stores the value, flags and status for every channel as a char data type
        char value [10] = "";
        char flag_a;
        char flag_b;
        char flag_c;
        char status;

        // Inner for loop, loops for every bit (12) of the channel
        for (int i = 0; i < 12; i++) {

            // While loop, loops for every value bits [0-7] of the channel
            while (i < 8) {
                // j as the switch case because j defines which channel
                // Scraping out the value bits from the channel
                switch(j){
                    // Cases 0 through 7 are for all the channels (case 0 -> channel 1, case 1 -> channel 2, .... , case 7 -> channel 8)
                    case 0:{
                        //Since direct concatenate using *(&one[i]) not allowed for strncat, I had to go through char pointer (const char accepted for 2nd argument of strncat)
                        // Concatenate the value bits [0-7] to a char called "value"
                        char *rgh = &one[i];
                        strncat(value, *(&rgh), 1);
                        break;
                    }
                    case 1:{
                        char *rgh = &two[i];
                        strncat(value, *(&rgh), 1);
                        break;
                    }
                    case 2:{
                        char *rgh = &three[i];
                        strncat(value, *(&rgh), 1);
                        break;
                    }
                    case 3:{
                        char *rgh = &four[i];
                        strncat(value, *(&rgh), 1);
                        break;
                    }
                    case 4:{
                        char *rgh = &five[i];
                        strncat(value, *(&rgh), 1);
                        break;
                    }
                    case 5:{
                        char *rgh = &six[i];
                        strncat(value, *(&rgh), 1);
                        break;
                    }
                    case 6:{
                        char *rgh = &seven[i];
                        strncat(value, *(&rgh), 1);
                        break;
                    }
                    case 7:{
                        char *rgh = &eight[i];
                        strncat(value, *(&rgh), 1);
                        break;
                    }
                    default:
                        printf("\nValue Bit Concatenation Error\n");
                        break;
                }   // End of switch statement
                // Increment i for the next iteration of the while loop
                i++;
            }   // End of while loop after concatenating value bits [0-7] and exits out this block with i = 8

            // Flag_A testing for each channels
            if (i == 8) {
                // j used as switch case because j is defined for the channels [8 Channels]
                switch(j){
                    // Storing the bit[1/0] of the flag_a bit of the channel
                    // cases 0 to 7 are for channels 1 through 8 respectively
                    case 0:{
                        flag_a = *(&one[i]);
                        break;
                    }
                    case 1:{
                        flag_a = *(&two[i]);
                        break;
                    }
                    case 2:{
                        flag_a = *(&three[i]);
                        break;
                    }
                    case 3:{
                        flag_a = *(&four[i]);
                        break;
                    }
                    case 4:{
                        flag_a = *(&five[i]);
                        break;
                    }
                    case 5:{
                        flag_a = *(&six[i]);
                        break;
                    }
                    case 6:{
                        flag_a = *(&seven[i]);
                        break;
                    }
                    case 7:{
                        flag_a = *(&eight[i]);
                        break;
                    }
                    default:
                        printf("\nFlag A Validation Error\n");
                        break;
                }
            } else if (i == 9) {
                switch(j){
                    // Storing the bit[1/0] of the flag_b bit of the channel
                    // cases 0 to 7 are for channels 1 through 8 respectively
                    case 0:{
                        flag_b = *(&one[i]);
                        break;
                    }
                    case 1:{
                        flag_b = *(&two[i]);
                        break;
                    }
                    case 2:{
                        flag_b = *(&three[i]);
                        break;
                    }
                    case 3:{
                        flag_b = *(&four[i]);
                        break;
                    }
                    case 4:{
                        flag_b = *(&five[i]);
                        break;
                    }
                    case 5:{
                        flag_b = *(&six[i]);
                        break;
                    }
                    case 6:{
                        flag_b = *(&seven[i]);
                        break;
                    }
                    case 7:{
                        flag_b = *(&eight[i]);
                        break;
                    }
                    default:
                        printf("\nFlag B Validation Error\n");
                        break;
                }
            } else if (i == 10) {
                switch(j){
                    // Storing the bit[1/0] of the flag_c bit of the channel
                    // cases 0 to 7 are for channels 1 through 8 respectively
                    case 0:{
                        flag_c = *(&one[i]);
                        break;
                    }
                    case 1:{
                        flag_c = *(&two[i]);
                        break;
                    }
                    case 2:{
                        flag_c = *(&three[i]);
                        break;
                    }
                    case 3:{
                        flag_c = *(&four[i]);
                        break;
                    }
                    case 4:{
                        flag_c = *(&five[i]);
                        break;
                    }
                    case 5:{
                        flag_c = *(&six[i]);
                        break;
                    }
                    case 6:{
                        flag_c = *(&seven[i]);
                        break;
                    }
                    case 7:{
                        flag_c = *(&eight[i]);
                        break;
                    }
                    default:
                        printf("\nFlag C Validation Error\n");
                        break;
                }
            } else if (i == 11) {
                switch(j){
                    // Storing the bit[1/0] of the status bit of the channel
                    // cases 0 to 7 are for channels 1 through 8 respectively
                    case 0:{
                        status = *(&one[i]);
                        break;
                    }
                    case 1:{
                        status = *(&two[i]);
                        break;
                    }
                    case 2:{
                        status = *(&three[i]);
                        break;
                    }
                    case 3:{
                        status = *(&four[i]);
                        break;
                    }
                    case 4:{
                        status = *(&five[i]);
                        break;
                    }
                    case 5:{
                        status = *(&six[i]);
                        break;
                    }
                    case 6:{
                        status = *(&seven[i]);
                        break;
                    }
                    case 7:{
                        status = *(&eight[i]);
                        break;
                    }
                    default:
                        printf("\nStatus Bit Validation Error\n");
                        break;
                }
            }
        }


// CODE TESTING PURPOSE ONLY
/*    printf("Value : %s\n", value);
    printf("Flag_A : %c\n", flag_a);
    printf("Flag_B : %c\n", flag_b);
    printf("Flag_C : %c\n", flag_c);
    printf("Status : %c\n", status);*/


        // Converting string(value) to int(x) for transferring VALUE to control_channel_t Struct
        int x;
        sscanf(value, "%d", &x);

        //printf("%d\n", x);    // CODE TESTING PURPOSE ONLY

        // To store the hex conversion of the binary
        int hexValue;
        hexValue = bin2hex(x);


        //printf("Hex value: %X\n", hexVal);    // CODE TESTING PURPOSE ONLY



        // Status Bit Check
        if (status == '0') {
            statusOne = CTRL_STAT_OK;
        } else if (status == '1') {
            statusOne = CTRL_STAT_ERR;
        }

        // Flag_A Bit Check
        if (flag_a == '0') {
            flagAOne = CTRL_FLAG_CLR;
        } else if (flag_a == '1') {
            flagAOne = CTRL_FLAG_SET;
        }

        // Flag_B Bit Check
        if (flag_b == '0') {
            flagBOne = CTRL_FLAG_CLR;
        } else if (flag_b == '1') {
            flagBOne = CTRL_FLAG_SET;
        }


        // Flag_C Bit Check
        if (flag_c == '0') {
            flagCOne = CTRL_FLAG_CLR;
        } else if (flag_c == '1') {
            flagCOne = CTRL_FLAG_SET;
        }


        //Parity Check for the value bits [0-7]
        int evenCount = 0;
        for (int k = 0; k < 8; k++) {
            if (j == 0 && *(&one[k]) == '1') {
                evenCount++;
            }
            else if (j == 1 && *(&two[k]) == '1') {
                evenCount++;
            }
            else if (j == 2 && *(&three[k]) == '1') {
                evenCount++;
            }
            else if (j == 3 && *(&four[k]) == '1') {
                evenCount++;
            }
            else if (j == 4 && *(&five[k]) == '1') {
                evenCount++;
            }
            else if (j == 5 && *(&six[k]) == '1') {
                evenCount++;
            }
            else if (j == 6 && *(&seven[k]) == '1') {
                evenCount++;
            }
            else if (j == 7 && *(&eight[k]) == '1') {
                evenCount++;
            }

        }

        if (evenCount % 2 == 0) {
            parityOne = CTRL_PARITY_EVEN;
        } else if (evenCount % 2 == 1) {
            parityOne = CTRL_PARITY_ODD;
        }


        output[j].status = statusOne;
        output[j].flag_a = flagAOne;
        output[j].flag_b = flagBOne;
        output[j].flag_c = flagCOne;
        output[j].parity = parityOne;
        output[j].value = hexValue;


        printf("\nCHANNEL %d\n", j+1);
        printf("Status: %d\n", output[j].status);
        printf("Flag A: %d\n", output[j].flag_a);
        printf("Flag B: %d\n", output[j].flag_b);
        printf("Flag C: %d\n", output[j].flag_c);
        printf("Parity: %d\n", output[j].parity);
        printf("Value(Hex): %X\n\n", output[j].value);

    }
}


