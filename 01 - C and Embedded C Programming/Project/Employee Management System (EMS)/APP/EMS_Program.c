/*
 * EMS_Program.c
 *
 *   Created on: Aug 1, 2022
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all EMS -Employee Management System- functions' implementations.
 */

/* APP -> Application Layer */
#include "EMS_Interface.h"

/* Declaration of global variables */
static DLL_Tag_st Glb_stEmpList; // DLL_Tag structure (head & tail)
static u32 Glb_u32EmpListIndex;  // Index to indicate position of current Employee

/*
 Name: EMS_vdEMSInit
 Input: void
 Output: void
 Description: Static Function to insert employees to DLL without any users' interventions.
*/
static vd EMS_vdEMSInit(void)
{
    /* Define local variable to set the error state, No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Define local Array of Nodes to store Employee Data */
    NodeDLL Loc_AstEmpNodes[EMS_U8_NO_OF_EMPS_INIT] = /* Age  ID   Salary       Name               Title  */
                                                       {{28, 1043, 25000, "Mohamed Osama"  , "Sr Software Developer"},
                                                        {23, 1810, 15000, "Gamal Rabie"    , "Jr Data Analyst"      },
                                                        {45, 1001, 35000, "Abdullah Khaled", "Team Lead"            },
                                                        {30, 1027, 20000, "Heba Bahaa"     , "Sr HR Specialist"     },
                                                        {40, 1000, 45000, "Ahmed Ismail"   , "CEO"                  }};

    /* Loop: To Insert all Employees to DLL */
    for (u32 Loc_u32Index = 0; Loc_u32Index < EMS_U8_NO_OF_EMPS_INIT; Loc_u32Index++)
    {
        /* Insert Employee to DLL */
        Loc_u8ErrorState = DLL_u8InsertDLLNodeByPos(&Glb_stEmpList, &Loc_AstEmpNodes[Loc_u32Index], Glb_u32EmpListIndex);

        /* Check: Insertion succeeded */
        if (Loc_u8ErrorState == ERR_TYPES_U8_NO_ERROR)
        {
            /* Increment Global Index */
            Glb_u32EmpListIndex++;
        }
    }
}

/*
 Name: EMS_vdStartProg
 Input: void
 Output: void
 Description: Function to print out welcome message, after initializing the program,
              and inserting employees to DLL.
*/
vd EMS_vdStartProg(void)
{
    /* Initialize DLL */
    DLL_vdDLLInit(&Glb_stEmpList);

    /* Initialize EMS */
    EMS_vdEMSInit();

    /* Print out message: Starting the program */
    CON_u8SystemOut(" Starting the program....");
    /* Print out message: Welcome */
    CON_u8SystemOut("\t\tWelcome!");
}

/*
 Name: EMS_vdDefaultProg
 Input: void
 Output: void
 Description: Function to print out error message when user inputs wrong option.
*/
vd EMS_vdDefaultProg(void)
{
    /* Print out message: Processing */
    CON_u8SystemOut(" Processing....");
    /* Print out error: Wrong option, please try again */
    CON_u8SystemOut(" Error! Wrong option, please try again!");
}

/*
 Name: EMS_vdExitProg
 Input: void
 Output: void
 Description: Function to print out goodbye message, after deleting employees from DLL.
*/
vd EMS_vdExitProg(void)
{
    /* Delete DLL */
    DLL_u8DeleteDLL(&Glb_stEmpList);

    /* Print out message: Goodbye */
    CON_u8SystemOut("\t\tGoodbye!");
    /* Print out message: Exiting the program */
    CON_u8SystemOut(" Exiting the program....");
}

/*
 Name: EMS_vdInsertEmp
 Input: void
 Output: void
 Description: Function to insert employees to DLL.
*/
vd EMS_vdInsertEmp(void)
{
    /* Define local variable to set the error state, No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;
    /* Define local Node Emoloyee to store Employee Data */
    NodeDLL Loc_stEmpNode;
    /* Define local array to get Employee ID as string */
    u8 Loc_Au8EmpID[EMS_U32_MAX_NO_OF_DIGITS] = {0};
    /* Define local variable to get Employee ID as u32 */
    u32 Loc_u32EmpID;
    /* Define local variable to get User Input */
    u8 Loc_u8UsrIn = 'N';

    /* Print out message: Processing */
    CON_u8SystemOut(" Processing....");

    /* Loop: Until user enters a numeric ID */
    do
    {
        /* Get ID from User */
        printf("\n\n");
        printf("\tAdd Employee Data");
        printf("\n\n");
        printf(" ID:     ");
        scanf(" %[^\n]s", Loc_Au8EmpID);

        /* Check 1: User enters a non-numeric ID */
        if (CON_u8IsDigit(Loc_Au8EmpID) == ERR_TYPES_U8_NOT_DIGIT)
        {
            /* Print out error: ID is non-numeric */
            CON_u8SystemOut(" Error! ID is non-numeric!");
        }
        /* Check 2: User enters a numeric ID */
        else
        {
            /* Convert string ID to u32 ID */
            Loc_u32EmpID = atoi(Loc_Au8EmpID);

            /* Search Employee in DLL */
            Loc_u8ErrorState = DLL_u8SearchDLLByVal(&Glb_stEmpList, &Loc_stEmpNode, Loc_u32EmpID);

            /* Check 2.1: Employee is found */
            if (Loc_u8ErrorState == ERR_TYPES_U8_NO_ERROR)
            {
                /* Print out message: Processing */
                CON_u8SystemOut(" Processing....");
                /* Print out error: ID is duplicated */
                CON_u8SystemOut(" Error! ID is duplicated!");
            }
            /* Check 2.2: Employee is not found */
            else if (Loc_u8ErrorState == ERR_TYPES_U8_NOT_FOUND)
            {
                Loc_stEmpNode.ID = Loc_u32EmpID;

                /* Get rest of data from User */
                printf(" Name:   ");
                scanf(" %[^\n]s", Loc_stEmpNode.Name);
                printf(" Age:    ");
                scanf("%d", &Loc_stEmpNode.Age);
                printf(" Title:  ");
                scanf(" %[^\n]s", Loc_stEmpNode.Title);
                printf(" Salary: ");
                scanf("%d", &Loc_stEmpNode.Salary);

                /* Confirmation to insert Employee */
                printf("\n\n");
                printf(" Are you sure you want to save changes? (Y/N): ");
                scanf(" %c", &Loc_u8UsrIn);

                /* Check 2.2.1: User confirms to insert Employee */
                if (Loc_u8UsrIn == 'Y' || Loc_u8UsrIn == 'y')
                {
                    /* Insert Employee to DLL */
                    Loc_u8ErrorState = DLL_u8InsertDLLNodeByPos(&Glb_stEmpList, &Loc_stEmpNode, Glb_u32EmpListIndex);

                    /* Check 2.2.1.1: Insertion succeeded */
                    if (Loc_u8ErrorState == ERR_TYPES_U8_NO_ERROR)
                    {
                        /* Increment Global Index */
                        Glb_u32EmpListIndex++;

                        /* Print out message: Processing */
                        CON_u8SystemOut(" Processing....");
                        /* Print out message: Data were added successfully */
                        CON_u8SystemOut(" Data were added successfully!");
                    }
                    /* Check 2.2.1.1: Insertion failed */
                    else if (Loc_u8ErrorState == ERR_TYPES_U8_NULL_PTR)
                    {
                        /* Print out message: Processing */
                        CON_u8SystemOut(" Processing....");
                        /* Print out error: Failed to allocate memory */
                        CON_u8SystemOut(" Error! Failed to allocate memory!");
                    }
                }
                break;
            }
        }
    } while (CON_U8_TRUE);

    /* Print out message: Returning to Main Menu */
    CON_u8SystemOut(" Returning to Main Menu....");
}

/*
 Name: EMS_vdDeleteEmp
 Input: void
 Output: void
 Description: Function to delete employees from DLL.
*/
vd EMS_vdDeleteEmp(void)
{
    /* Define local variable to set the error state, No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;
    /* Define local Node Emoloyee to store Employee Data */
    NodeDLL Loc_stEmpNode;
    /* Define local array to get Employee ID as string */
    u8 Loc_Au8EmpID[EMS_U32_MAX_NO_OF_DIGITS] = {0};
    /* Define local variable to get Employee ID as u32 */
    u32 Loc_u32EmpID;
    /* Define local variable to get User Input */
    u8 Loc_u8UsrIn = 'N';

    /* Print out message: Processing */
    CON_u8SystemOut(" Processing....");

    /* Loop: Until user enters a numeric ID */
    do
    {
        /* Get ID from User */
        printf("\n\n");
        printf("\tDelete Employee Data");
        printf("\n\n");
        printf(" ID:     ");
        scanf(" %[^\n]s", Loc_Au8EmpID);

        /* Check 1: User enters a non-numeric ID */
        if (CON_u8IsDigit(Loc_Au8EmpID) == ERR_TYPES_U8_NOT_DIGIT)
        {
            /* Print out error: ID is non-numeric */
            CON_u8SystemOut(" Error! ID is non-numeric!");
        }
        /* Check 2: User enters a numeric ID */
        else
        {
            /* Convert string ID to u32 ID */
            Loc_u32EmpID = atoi(Loc_Au8EmpID);

            /* Search Employee in DLL */
            Loc_u8ErrorState = DLL_u8SearchDLLByVal(&Glb_stEmpList, &Loc_stEmpNode, Loc_u32EmpID);

            /* Check 2.1: Employees list is empty */
            if (Loc_u8ErrorState == ERR_TYPES_U8_NULL_PTR)
            {
                /* Print out message: Processing */
                CON_u8SystemOut(" Processing....");
                /* Print out error: Employees list is empty */
                CON_u8SystemOut(" Error! Employees list is empty!");

                break;
            }
            /* Check 2.2: Employee is not found */
            else if (Loc_u8ErrorState == ERR_TYPES_U8_NOT_FOUND)
            {
                /* Print out message: Processing */
                CON_u8SystemOut(" Processing....");
                /* Print out error: ID is not found */
                CON_u8SystemOut(" Error! ID is not found!");

                break;
            }
            /* Check 2.3: Employee is found */
            else if (Loc_u8ErrorState == ERR_TYPES_U8_NO_ERROR)
            {
                /* Print out message: Processing */
                CON_u8SystemOut(" Processing....");

                /* Display Employee Data */
                printf("\n\n");
                printf("\tDelete Employee Data");
                printf("\n\n");
                printf(" ID:      %d\n", Loc_stEmpNode.ID);
                printf(" Name:    %s\n", Loc_stEmpNode.Name);
                printf(" Age:     %d\n", Loc_stEmpNode.Age);
                printf(" Title:   %s\n", Loc_stEmpNode.Title);
                printf(" Salary:  %d\n", Loc_stEmpNode.Salary);

                /* Confirmation to delete Employee */
                printf("\n");
                printf(" Are you sure you want to delete data? (Y/N): ");
                scanf(" %c", &Loc_u8UsrIn);

                /* Check 2.3.1: User confirms to delete Employee */
                if (Loc_u8UsrIn == 'Y' || Loc_u8UsrIn == 'y')
                {
                    /* Delete Employee from DLL */
                    Loc_u8ErrorState = DLL_u8DeleteDLLNodeByVal(&Glb_stEmpList, Loc_u32EmpID);

                    /* Check 2.3.1.1: Deletion succeeded */
                    if (Loc_u8ErrorState == ERR_TYPES_U8_NO_ERROR)
                    {
                        /* Decrement Global Index */
                        Glb_u32EmpListIndex--;

                        /* Print out message: Processing */
                        CON_u8SystemOut(" Processing....");
                        /* Print out message: Data were deleted successfully */
                        CON_u8SystemOut(" Data were deleted successfully!");
                    }
                }
                break;
            }
        }
    } while (CON_U8_TRUE);

    /* Print out message: Returning to Main Menu */
    CON_u8SystemOut(" Returning to Main Menu....");
}

/*
 Name: EMS_vdModifyEmp
 Input: void
 Output: void
 Description: Function to modify employees in DLL.
*/
vd EMS_vdModifyEmp(void)
{
    /* Define local variable to set the error state, No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;
    /* Define local Node Emoloyee to store Employee Data */
    NodeDLL Loc_stEmpNode;
    /* Define local array to get Employee ID as string */
    u8 Loc_Au8EmpID[EMS_U32_MAX_NO_OF_DIGITS] = {0};
    /* Define local variable to get Employee ID as u32 */
    u32 Loc_u32EmpID;
    /* Define local variable to get User Input */
    u8 Loc_u8UsrIn = 'N';

    /* Print out message: Processing */
    CON_u8SystemOut(" Processing....");

    /* Loop: Until user enters a numeric ID */
    do
    {
        /* Get ID from User */
        printf("\n\n");
        printf("\tModify Employee Data");
        printf("\n\n");
        printf(" ID:     ");
        scanf(" %[^\n]s", Loc_Au8EmpID);

        /* Check 1: User enters a non-numeric ID */
        if (CON_u8IsDigit(Loc_Au8EmpID) == ERR_TYPES_U8_NOT_DIGIT)
        {
            /* Print out error: ID is non-numeric */
            CON_u8SystemOut(" Error! ID is non-numeric!");
        }
        /* Check 2: User enters a numeric ID */
        else
        {
            /* Convert string ID to u32 ID */
            Loc_u32EmpID = atoi(Loc_Au8EmpID);

            /* Search Employee in DLL */
            Loc_u8ErrorState = DLL_u8SearchDLLByVal(&Glb_stEmpList, &Loc_stEmpNode, Loc_u32EmpID);

            /* Check 2.1: Employees list is empty */
            if (Loc_u8ErrorState == ERR_TYPES_U8_NULL_PTR)
            {
                /* Print out message: Processing */
                CON_u8SystemOut(" Processing....");
                /* Print out error: Employees list is empty */
                CON_u8SystemOut(" Error! Employees list is empty!");

                break;
            }
            /* Check 2.2: Employee is not found */
            else if (Loc_u8ErrorState == ERR_TYPES_U8_NOT_FOUND)
            {
                /* Print out message: Processing */
                CON_u8SystemOut(" Processing....");
                /* Print out error: ID is not found */
                CON_u8SystemOut(" Error! ID is not found!");

                break;
            }
            /* Check 2.3: Employee is found */
            else if (Loc_u8ErrorState == ERR_TYPES_U8_NO_ERROR)
            {
                /* Print out message: Processing */
                CON_u8SystemOut(" Processing....");

                /* Display Employee old Data */
                printf("\n\n");
                printf("\tModify Employee Data");
                printf("\n\n");
                printf(" ID:      %d\n", Loc_stEmpNode.ID);
                printf(" Name:    %s\n", Loc_stEmpNode.Name);
                printf(" Age:     %d\n", Loc_stEmpNode.Age);
                printf(" Title:   %s\n", Loc_stEmpNode.Title);
                printf(" Salary:  %d\n", Loc_stEmpNode.Salary);

                /* Get new data from User */
                printf("\n\n");
                printf("\tAdd Employee Data");
                printf("\n\n");
                printf(" ID:   %d\n", Loc_u32EmpID);
                Loc_stEmpNode.ID = Loc_u32EmpID;
                printf(" Name:   ");
                scanf(" %[^\n]s", Loc_stEmpNode.Name);
                printf(" Age:    ");
                scanf("%d", &Loc_stEmpNode.Age);
                printf(" Title:  ");
                scanf(" %[^\n]s", Loc_stEmpNode.Title);
                printf(" Salary: ");
                scanf("%d", &Loc_stEmpNode.Salary);

                /* Confirmation to modify Employee */
                printf("\n\n");
                printf(" Are you sure you want to save changes? (Y/N): ");
                scanf(" %c", &Loc_u8UsrIn);

                /* Check 2.3.1: User confirms to modify Employee */
                if (Loc_u8UsrIn == 'Y' || Loc_u8UsrIn == 'y')
                {
                    /* Modify Employee in DLL */
                    Loc_u8ErrorState = DLL_u8ModifyDLLNodeByVal(&Glb_stEmpList, &Loc_stEmpNode, Loc_u32EmpID);

                    /* Check 2.3.1.1: Modification succeeded */
                    if (Loc_u8ErrorState == ERR_TYPES_U8_NO_ERROR)
                    {
                        /* Print out message: Processing */
                        CON_u8SystemOut(" Processing....");
                        /* Print out message: Data were modified successfully */
                        CON_u8SystemOut(" Data were modified successfully!");
                    }
                }
                break;
            }
        }
    } while (CON_U8_TRUE);

    /* Print out message: Returning to Main Menu */
    CON_u8SystemOut(" Returning to Main Menu....");
}

/*
 Name: EMS_vdDisplayEmp
 Input: void
 Output: void
 Description: Function to display employees in DLL.
 */
vd EMS_vdDisplayEmp(void)
{
    /* Define local variable to set the error state, No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;
    /* Define local Node Emoloyee to store Employee Data */
    NodeDLL Loc_stEmpNode;
    /* Define local array to get Employee ID as string */
    u8 Loc_Au8EmpID[EMS_U32_MAX_NO_OF_DIGITS] = {0};
    /* Define local variable to get Employee ID as u32 */
    u32 Loc_u32EmpID;
    /* Define local variable to get User Input */
    u8 Loc_u8UsrIn = 0;

    /* Print out message: Processing */
    CON_u8SystemOut(" Processing....");

    /* Loop: Until user enters a numeric ID */
    do
    {
        /* Get ID from User */
        printf("\n\n");
        printf("\tModify Employee Data");
        printf("\n\n");
        printf(" ID:     ");
        scanf(" %[^\n]s", Loc_Au8EmpID);

        /* Check 1: User enters a non-numeric ID */
        if (CON_u8IsDigit(Loc_Au8EmpID) == ERR_TYPES_U8_NOT_DIGIT)
        {
            /* Print out error: ID is non-numeric */
            CON_u8SystemOut(" Error! ID is non-numeric!");
        }
        /* Check 2: User enters a numeric ID */
        else
        {
            /* Convert string ID to u32 ID */
            Loc_u32EmpID = atoi(Loc_Au8EmpID);

            /* Search Employee in DLL */
            Loc_u8ErrorState = DLL_u8SearchDLLByVal(&Glb_stEmpList, &Loc_stEmpNode, Loc_u32EmpID);

            /* Check 2.1: Employees list is empty */
            if (Loc_u8ErrorState == ERR_TYPES_U8_NULL_PTR)
            {
                /* Print out message: Processing */
                CON_u8SystemOut(" Processing....");
                /* Print out error: Employees list is empty */
                CON_u8SystemOut(" Error! Employees list is empty!");

                break;
            }
            /* Check 2.2: Employee is not found */
            else if (Loc_u8ErrorState == ERR_TYPES_U8_NOT_FOUND)
            {
                /* Print out message: Processing */
                CON_u8SystemOut(" Processing....");
                /* Print out error: ID is not found */
                CON_u8SystemOut(" Error! ID is not found!");

                break;
            }
            /* Check 2.3: Employee is found */
            else if (Loc_u8ErrorState == ERR_TYPES_U8_NO_ERROR)
            {
                /* Print out message: Processing */
                CON_u8SystemOut(" Processing....");

                /* Display Employee Data */
                printf("\n\n");
                printf("\tDisplay Employee Data");
                printf("\n\n");
                printf(" ID:      %d\n", Loc_stEmpNode.ID);
                printf(" Name:    %s\n", Loc_stEmpNode.Name);
                printf(" Age:     %d\n", Loc_stEmpNode.Age);
                printf(" Title:   %s\n", Loc_stEmpNode.Title);
                printf(" Salary:  %d\n", Loc_stEmpNode.Salary);

                /* Clear Buffer */
                fflush(stdin);

                /* Return to home */
                printf("\n");
                printf(" Press ENTER to continue....");
                scanf("%c", &Loc_u8UsrIn);

                break;
            }
        }
    } while (CON_U8_TRUE);

    /* Print out message: Returning to Main Menu */
    CON_u8SystemOut(" Returning to Main Menu....");
}

/*
 Name: EMS_vdDisplayAllEmps
 Input: void
 Output: void
 Description: Function to display all employees in DLL at once.
 */
vd EMS_vdDisplayAllEmps(void)
{
    /* Print out message: Processing */
    CON_u8SystemOut(" Processing....");

    /* Check 1: Employees list is empty */
    if (Glb_stEmpList.head == NULL)
    {
        /* Print out error: Employees list is empty */
        CON_u8SystemOut(" Error! Employees list is empty!");
    }
    /* Check 2: Employees list is not empty */
    else
    {
        /* Define local pointer EmpNode = head */
        NodeDLL *Loc_pstEmpNode = Glb_stEmpList.head;

        /* Define local variable to get User Input */
        u8 Loc_u8UsrIn = 0;

        /* Display Employee Data */
        printf("\n\n");
        printf("\tDisplay Employees Data");
        printf("\n");

        /* Loop: Until the end of Employees list */
        while (Loc_pstEmpNode != NULL)
        {
            printf("\n");
            printf(" ID:      %d\n", Loc_pstEmpNode->ID);
            printf(" Name:    %s\n", Loc_pstEmpNode->Name);
            printf(" Age:     %d\n", Loc_pstEmpNode->Age);
            printf(" Title:   %s\n", Loc_pstEmpNode->Title);
            printf(" Salary:  %d\n", Loc_pstEmpNode->Salary);

            /* Increment Local Pointer */
            Loc_pstEmpNode = Loc_pstEmpNode->next;
        }

        /* Clear Buffer */
        fflush(stdin);

        /* Return to home */
        printf("\n");
        printf(" Press ENTER to continue....");
        scanf("%c", &Loc_u8UsrIn);
    }

    /* Print out message: Returning to Main Menu */
    CON_u8SystemOut(" Returning to Main Menu....");
}
