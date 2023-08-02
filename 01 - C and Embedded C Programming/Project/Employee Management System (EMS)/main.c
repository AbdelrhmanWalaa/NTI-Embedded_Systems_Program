/*
 *   Created on: Aug 1, 2022
 *       Author: Abdelrhman Walaa
 *  Description: EMS -Employee Managment System- is a program to help user insert, delete, modify, and display employees' data. This program is implemented using double linked list
                 data structure to store employees' data.
 */

#include "APP/EMS_Interface.h"

int main(void)
{
    /* Define local array to get user's Input as string */
    u8 Loc_Au8UsrIn[EMS_U8_MAX_NO_OF_DIGITS] = {0};
    /* Define local variable to get User's Input as u8 */
    u8 Loc_u8UsrIn = 0;

    /* Start the program */
    EMS_vdStartProg();

    do
    {
        printf("\n\n");
        printf("\t\t  -EMS-\n\tEmployee Managment System");
        printf("\n\n");
        printf(" Please Choose an option for Employees:\n\n 1.Insert\n 2.Delete\n 3.Modify\n 4.Display\n 5.Display All\n 6.Exit\n");

        /* Get User's option */
        printf("\n Your Option: ");
        scanf(" %[^\n]s", Loc_Au8UsrIn);

        /* Check 1: User enters a non-numeric input */
        if (CON_u8IsDigit(Loc_Au8UsrIn) == ERR_TYPES_U8_NOT_DIGIT)
        {
            /* Print out error: Input is non-numeric */
            CON_u8SystemOut(" Error! Input is non-numeric!");
        }
        /* Check 2: User enters a numeric input */
        else
        {
            /* Convert string Input to u8 Input */
            Loc_u8UsrIn = atoi(Loc_Au8UsrIn);

            /* Switch between different options */
            switch (Loc_u8UsrIn)
            {
            /* Case 1: Insert an Employee */
            case EMS_enIns:
                EMS_vdInsertEmp();
                break;
            /* Case 2: Delete an Employee */
            case EMS_enDel:
                EMS_vdDeleteEmp();
                break;
            /* Case 3: Modify an Employee */
            case EMS_enMod:
                EMS_vdModifyEmp();
                break;
            /* Case 4: Display an Employee */
            case EMS_enDsp:
                EMS_vdDisplayEmp();
                break;
            /* Case 5: Display all Employees */
            case EMS_enDspAll:
                EMS_vdDisplayAllEmps();
                break;
            /* Case 6: Exit */
            case EMS_enExt:
                EMS_vdExitProg();
                exit(0);
            /* Default: Wrong Input! */
            default:
                EMS_vdDefaultProg();
            }
        }
    } while (CON_U8_TRUE);

    return 0;
}