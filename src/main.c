/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <string.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

// *****************************************************************************
// *****************************************************************************
// Section : Parameters and variables
// *****************************************************************************
// *****************************************************************************
/////////////////////////////// PROGRAM VARIABLES ///////////////////////////// 
#define MAX_COMMAND_LEN 8      

// *****************************************************************************
// *****************************************************************************
// Section : Local Functions
// *****************************************************************************
// *****************************************************************************

void executeCommand(char *command)
{
    if(strcmp(command, "ON") == 0)
    {
        LED0_On();
        printf("OK, LED ON.\r\n");
        // optionally should use FLEXCOM1_USART_Write(), because printf takes more clock cycles
    }
    else if (strcmp(command, "OFF") == 0)
    {
        LED0_Off();
        printf("OK, LED OFF.\r\n");
    } 
    else 
    {
        printf("Incorrect command.\r\n");
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    char command[MAX_COMMAND_LEN];
    uint8_t index = 0;
    char c;
  
    while ( true )
    {
        // simple code to read commands from console using UART peripheral library
        // that was generated using MCC and Harmony
        if (FLEXCOM1_USART_Read(&c,1)){
            if(c != '\n' && c != '\r')
            {
                command[index++] = c;
                if(index >= MAX_COMMAND_LEN)
                {
                    index = 0;
                }
            }
            if(c == '\n')
            {
                command[index] = '\0';
                index = 0;
                executeCommand(command);
            }
        }


        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

