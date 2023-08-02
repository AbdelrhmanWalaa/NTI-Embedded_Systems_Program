/*
 * CON_Program.c
 *
 *   Created on: Aug 1, 2022
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all CON -Console- functions' implementations.
 */

/* SRV -> Service Layer */
#include "CON_Interface.h"

/*
 Name: CON_vdHideCursor
 Input: u8 True or False
 Output: void
 Description: Static Function to show cursor or hide it according to input.
*/
static vd CON_vdHideCursor(u8 Cpy_u8Bool)
{
    /* Check 1: To show the cursor */
    if (Cpy_u8Bool == CON_U8_FALSE)
    {
        printf("\e[?25h");
    }
    /* Check 2: To hide the cursor */
    else if (Cpy_u8Bool == CON_U8_TRUE)
    {
        printf("\e[?25l");
    }
}

/*
 Name: CON_vdSystemOut
 Input: Pointer to string
 Output: u8 Error or No Error
 Description: Function to print string on screen passed as input.
*/
u8 CON_u8SystemOut(u8 *Cpy_pu8String)
{
    /* Define local variable to set the error state, No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Check 1: Pointer is NULL */
    if (Cpy_pu8String == NULL)
    {
        /* Update error state, Pointer is NULL! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }
    /* Check 2: Pointer is not NULL */
    else
    {
        /* Hide cursor */
        CON_vdHideCursor(CON_U8_TRUE);
        /* Clear screen */
        system("cls");
        /* Delay 0.5 sec. */
        sleep(0.5);

        printf("\n\n");

        /* Loop: Until the end of string */
        while (*Cpy_pu8String != '\0')
        {
            printf("%c", *Cpy_pu8String);

            /* Increment Pointer */
            Cpy_pu8String++;
        }

        /* Delay 3 sec. */
        sleep(3);
        /* Clear screen */
        system("cls");
        /* Show cursor */
        CON_vdHideCursor(CON_U8_FALSE);
    }

    return Loc_u8ErrorState;
}

/*
 Name: CON_u8IsDigit
 Input: Pointer to string
 Output: u8 Error or No Error
 Description: Function to check wether the passed string contains digits only or not, if string consists
              of digits only it return no error, else it returns error.
*/
u8 CON_u8IsDigit(u8 *Cpy_pu8String)
{
    /* Define local variable to set the error state, No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Check 1: Pointer is NULL */
    if (Cpy_pu8String == NULL)
    {
        /* Update error state, Pointer is NULL! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }
    /* Check 2: Pointer is not NULL */
    else
    {
        /* Loop: Until the end of string */
        while (*Cpy_pu8String != '\0')
        {
            /* Check 2.1: String contains letters */
            if ((*Cpy_pu8String < CON_U8_ASCII_ZERO) || (*Cpy_pu8String > CON_U8_ASCII_NINE))
            {
                /* Update error state, String contains letters! */
                Loc_u8ErrorState = ERR_TYPES_U8_NOT_DIGIT;

                break;
            }
            /* Check 2.1: String does not contain letters */
            else
            {
                /* Increment Pointer */
                Cpy_pu8String++;
            }
        }
    }

    return Loc_u8ErrorState;
}