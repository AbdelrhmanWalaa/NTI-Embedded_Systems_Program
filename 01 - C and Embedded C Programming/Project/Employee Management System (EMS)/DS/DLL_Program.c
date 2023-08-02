/*
 * DLL_Program.c
 *
 *   Created on: Aug 1, 2022
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all DLL -Double Linked List- functions' implementations.
 */

/* DS -> Data Structure Layer */
#include "DLL_Interface.h"

/*
 Name: DLL_vdDLLInit
 Input: Address of DLL_Tag structure (head & tail)
 Output: void
 Description: Fuction to initialize structure members; pointers with NULL.
*/
vd DLL_vdDLLInit(DLL_Tag_st *Cpy_pstDLLTag)
{
    /* Initialize head and tail with NULL */
    Cpy_pstDLLTag->head = NULL;
    Cpy_pstDLLTag->tail = NULL;
}

/*
 Name: DLL_u8IsPtrNull
 Input: Pointer to DLL Node structure
 Output: u8 Error or No Error
 Description: Static Function to check wether the passed pointer to Node is NULL or not,
              if the pointer is not NULL it returns No Error, else it returns Erorr.
*/
static u8 DLL_u8IsPtrNull(NodeDLL *Cpy_pstNode)
{
    /* Define local variable to set the error state, No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Check: Pointer is NULL */
    if (Cpy_pstNode == NULL)
    {
        /* Update error state, Pointer is NULL! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }

    return Loc_u8ErrorState;
}

/*
 Name: DLL_u8CreateDLLNode
 Input: Pointer to Address of new Node
 Output: u8 Error or No Error
 Description: Static Fuction to create new DLL Node, using dynamic memory allocation, if it
              succeeded to allocate memory it returns No Error, else it returns Error.
*/
static u8 DLL_u8CreateDLLNode(NodeDLL **Cpy_pstNewNode)
{
    /* Define local variable to set the error state = No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Allocate memory to new Node using calloc funtion */
    *Cpy_pstNewNode = (NodeDLL *)calloc(1, sizeof(NodeDLL));

    /* Check: Allocation does not succeed */
    if (DLL_u8IsPtrNull(*Cpy_pstNewNode) == ERR_TYPES_U8_NULL_PTR)
    {
        /* Update error state, Pointer is NULL, Failed to allocate memory! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }

    return Loc_u8ErrorState;
}

/*
 Name: DLL_u8DisplayDLL
 Input: Address of DLL_Tag structure (head & tail)
 Output: u8 Error or No Error
 Description: Function to display DLL Nodes, it prints out DLL in order and returns No Error,
              if list is empty it returns Error.
*/
u8 DLL_u8DisplayDLL(DLL_Tag_st *Cpy_pstDLLTag)
{
    /* Define local variable to set the error state = No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Check 1: DLL is empty */
    if (DLL_u8IsPtrNull(Cpy_pstDLLTag->head) == ERR_TYPES_U8_NULL_PTR)
    {
        /* Update error state, Pointer is NULL, List is Empty! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }
    /* Check 2: DLL is not empty */
    else
    {
        /* Define local pointer Current to Node = head */
        NodeDLL *Loc_pstCurrent = Cpy_pstDLLTag->head;

        printf(" List in order:\n");
        /* Loop: Until the end of DLL */
        while (DLL_u8IsPtrNull(Loc_pstCurrent) != ERR_TYPES_U8_NULL_PTR)
        {
            printf("\n");
            printf(" ID:     %d\n Name:   %s\n Age:    %d\n Title:  %s\n Salary: %d", Loc_pstCurrent->ID, Loc_pstCurrent->Name, Loc_pstCurrent->Age, Loc_pstCurrent->Title, Loc_pstCurrent->Salary);
            printf("\n");

            /* Increment Current Node */
            Loc_pstCurrent = Loc_pstCurrent->next;
        }
    }

    return Loc_u8ErrorState;
}

/*
 Name: DLL_u8DisplayReverseDLL
 Input: Address of DLL_Tag structure (head & tail)
 Output: u8 Error or No Error
 Description: Function to display DLL Nodes, it prints out DLL in a reverse order and returns No Error,
              if list is empty it returns Error.
*/
u8 DLL_u8DisplayReverseDLL(DLL_Tag_st *Cpy_pstDLLTag)
{
    /* Define local variable to set the error state = No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Check 1: DLL is empty */
    if (DLL_u8IsPtrNull(Cpy_pstDLLTag->head) == ERR_TYPES_U8_NULL_PTR)
    {
        /* Update error state, Pointer is NULL, List is Empty! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }
    /* Check 2: DLL is not empty */
    else
    {
        /* Define local pointer Current to Node = tail */
        NodeDLL *Loc_pstCurrent = Cpy_pstDLLTag->tail;

        printf(" List in reversed order:\n");
        /* Loop: Until the end of DLL */
        while (DLL_u8IsPtrNull(Loc_pstCurrent) != ERR_TYPES_U8_NULL_PTR)
        {
            printf("\n");
            printf(" ID:     %d\n Name:   %s\n Age:    %d\n Title:  %s\n Salary: %d", Loc_pstCurrent->ID, Loc_pstCurrent->Name, Loc_pstCurrent->Age, Loc_pstCurrent->Title, Loc_pstCurrent->Salary);
            printf("\n");

            /* Decrement Current Node */
            Loc_pstCurrent = Loc_pstCurrent->prev;
        }
    }

    return Loc_u8ErrorState;
}

/*
 Name: DLL_u8SearchDLLByVal
 Input: Address of DLL_Tag structure (head & tail), Returned Pointer to Node to if found,
        u32 Node ID to be searched
 Output: u8 Error or No Error
 Description: Function to search DLL Nodes, using a value (ID) to do so. It returns Error
              if list is empty or data is not found, else it returns No Error.
*/
u8 DLL_u8SearchDLLByVal(DLL_Tag_st *Cpy_pstDLLTag, NodeDLL *Cpy_pstRetSrchNode, u32 Cpy_u32NodeID)
{
    /* Define local variable to set the error state = No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Check 1: DLL is empty */
    if (DLL_u8IsPtrNull(Cpy_pstDLLTag->head) == ERR_TYPES_U8_NULL_PTR)
    {
        /* Update error state, Pointer is NULL, List is Empty! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }
    /* Check 2: DLL is not empty */
    else
    {
        /* Define local pointer Current to Node = head */
        NodeDLL *Loc_pstCurrent = Cpy_pstDLLTag->head;

        /* Loop: Until the end of DLL, or Node is found */
        while ((DLL_u8IsPtrNull(Loc_pstCurrent->next) != ERR_TYPES_U8_NULL_PTR) && (Loc_pstCurrent->ID != Cpy_u32NodeID))
        {
            /* Increment Current Node */
            Loc_pstCurrent = Loc_pstCurrent->next;
        }

        /* Check 2.1: Node is found */
        if (Loc_pstCurrent->ID == Cpy_u32NodeID)
        {
            *Cpy_pstRetSrchNode = *Loc_pstCurrent;
        }
        /* Check 2.2: Node is not found */
        else
        {
            /* Update error state, Pointer is NULL, Node not found! */
            Loc_u8ErrorState = ERR_TYPES_U8_NOT_FOUND;
        }
    }

    return Loc_u8ErrorState;
}

/*
 Name: DLL_u8CountDLLNodes
 Input: Address of DLL_Tag structure (head & tail), u32 Pointer to Nodes Counter
 Output: u8 Error or No Error
 Description: Function to count DLL Nodes, and returns u32 Counter in pointer parameter.
*/
u8 DLL_u8CountDLLNodes(DLL_Tag_st *Cpy_pstDLLTag, u32 *Cpy_pu32RetCount)
{
    /* Define local variable to set the error state = No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Initialize passed Counter = 0 */
    *Cpy_pu32RetCount = 0;

    /* Check 1: DLL is empty */
    if (DLL_u8IsPtrNull(Cpy_pstDLLTag->head) == ERR_TYPES_U8_NULL_PTR)
    {
        /* Update error state, Pointer is NULL, List is Empty! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }
    /* Check 2: DLL is not empty */
    else
    {
        /* Define local pointer Current to Node = head */
        NodeDLL *Loc_pstCurrent = Cpy_pstDLLTag->head;

        /* Loop: Until the end of DLL */
        while (DLL_u8IsPtrNull(Loc_pstCurrent) != ERR_TYPES_U8_NULL_PTR)
        {
            /* Increment Counter */
            *Cpy_pu32RetCount++;

            /* Increment Current Node */
            Loc_pstCurrent = Loc_pstCurrent->next;
        }
    }

    return Loc_u8ErrorState;
}

/*
 Name: DLL_vdInsDLLNodeAtBeg
 Input: Pointer to Address of head Node, Pointer to Address of new Node
 Output: u8 Error or No Error
 Description: Static Function to insert new Node at the beginning of DLL. This function is called
              by "DLL_u8InsertDLLNodeByPos" function only.
*/
static vd DLL_vdInsDLLNodeAtBeg(NodeDLL **Cpy_pstHead, NodeDLL **Cpy_pstNewNode)
{
    /* Step 1: Make newNode->next = headNode */
    (*Cpy_pstNewNode)->next = *Cpy_pstHead;
    /* Step 2: Make headNode->prev = newNode */
    (*Cpy_pstHead)->prev = *Cpy_pstNewNode;
    /* Step 3: Make headNode = newNode */
    *Cpy_pstHead = *Cpy_pstNewNode;
}

/*
 Name: DLL_vdInsDLLNodeAtMid
 Input: Pointer to Address of current Node, Pointer to Address of new Node
 Output: void
 Description: Static Function to insert new Node in the middle of DLL. This function is called
              by "DLL_u8InsertDLLNodeByPos" function only.
*/
static vd DLL_vdInsDLLNodeAtMid(NodeDLL **Cpy_pstCurrent, NodeDLL **Cpy_pstNewNode)
{
    /* Step 1: Make newNode->next = currentNode */
    (*Cpy_pstNewNode)->next = *Cpy_pstCurrent;
    /* Step 2: Make newNode->prev = currentNode->prev */
    (*Cpy_pstNewNode)->prev = (*Cpy_pstCurrent)->prev;
    /* Step 3: Make currentNode->prev->next = newNode */
    (*Cpy_pstCurrent)->prev->next = *Cpy_pstNewNode;
    /* Step 4: Make currentNode->prev = newNode */
    (*Cpy_pstCurrent)->prev = *Cpy_pstNewNode;
}

/*
 Name: DLL_vdInsDLLNodeAtEnd
 Input: Pointer to Address of tail Node, Pointer to Address of new Node
 Output: void
 Description: Static Function to insert new Node at the end of DLL. This function is called
              by "DLL_u8InsertDLLNodeByPos" function only.
*/
static vd DLL_vdInsDLLNodeAtEnd(NodeDLL **Cpy_pstTail, NodeDLL **Cpy_pstNewNode)
{
    /* Step 1: Make newNode->prev = tailNode */
    (*Cpy_pstNewNode)->prev = *Cpy_pstTail;
    /* Step 2: Make tailNode->next = newNode */
    (*Cpy_pstTail)->next = *Cpy_pstNewNode;
    /* Step 3: Make tailNode = newNode */
    *Cpy_pstTail = *Cpy_pstNewNode;
}

/*
 Name: DLL_u8InsertDLLNodeByPos
 Input: Address of DLL_Tag structure (head & tail), Address of new Node to be stored, u32 Storing position
 Output: u8 Error or No Error
 Description: Function to insert new Nodes, using a value (ID) and position to do so. It returns Error
              if failed to allocate memory, else it returns No Error.
*/
u8 DLL_u8InsertDLLNodeByPos(DLL_Tag_st *Cpy_pstDLLTag, NodeDLL *Cpy_pstNewNode, u32 Cpy_u32NodePos)
{
    /* Define local variable to set the error state = No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Define local pointer NewNode to Node */
    NodeDLL *Loc_pstNewNode;

    /* Check 1: Allocation success */
    if (DLL_u8CreateDLLNode(&Loc_pstNewNode) == ERR_TYPES_U8_NO_ERROR)
    {
        /* Initialize new Node */
        *Loc_pstNewNode = *Cpy_pstNewNode;
        Loc_pstNewNode->next = NULL;
        Loc_pstNewNode->prev = NULL;

        /* Check 1.1: DLL is empty */
        if (DLL_u8IsPtrNull(Cpy_pstDLLTag->head) == ERR_TYPES_U8_NULL_PTR)
        {
            Cpy_pstDLLTag->head = Cpy_pstDLLTag->tail = Loc_pstNewNode;
        }
        /* Check 1.2: DLL is not empty */
        else
        {
            /* Check 1.2.1: Insert at the begininng of DLL */
            if (Cpy_u32NodePos == DLL_U8_BEG_OF_LIST)
            {
                DLL_vdInsDLLNodeAtBeg(&Cpy_pstDLLTag->head, &Loc_pstNewNode);
            }
            /* Check 1.2.2: Insert in between or at the end of DLL */
            else if (Cpy_u32NodePos > DLL_U8_BEG_OF_LIST)
            {
                /* Define local variable to set the flag state = DOWN */
                u8 Loc_u8Flag = DLL_U8_FLAG_DOWN;

                /* Define local pointer Current to Node = head */
                NodeDLL *Loc_pstCurrent = Cpy_pstDLLTag->head;

                /* Loop: Until the position is reached, or the end of DLL is reached */
                for (u32 Loc_u32Index = DLL_U8_BEG_OF_LIST; Loc_u32Index < Cpy_u32NodePos; Loc_u32Index++)
                {
                    /* Check 1.2.2.1: Reached the of end DLL */
                    if (DLL_u8IsPtrNull(Loc_pstCurrent->next) == ERR_TYPES_U8_NULL_PTR)
                    {
                        /* Update flag state, Pointer->next is NULL! */
                        Loc_u8Flag = DLL_U8_FLAG_UP;
                        break;
                    }
                    /* Check 1.2.2.2: Did not reach the of end DLL */
                    else
                    {
                        /* Increment Current Node */
                        Loc_pstCurrent = Loc_pstCurrent->next;
                    }
                }
                /* Check 1.2.3: Flag DOWN */
                if (Loc_u8Flag == DLL_U8_FLAG_DOWN)
                {
                    DLL_vdInsDLLNodeAtMid(&Loc_pstCurrent, &Loc_pstNewNode);
                }
                /* Check 1.2.4: Flag UP */
                else if (Loc_u8Flag == DLL_U8_FLAG_UP)
                {
                    DLL_vdInsDLLNodeAtEnd(&Cpy_pstDLLTag->tail, &Loc_pstNewNode);
                }
            }
        }
    }
    /* Check 2: Allocation failure */
    else if (DLL_u8CreateDLLNode(&Loc_pstNewNode) == ERR_TYPES_U8_NULL_PTR)
    {
        /* Update error state, Pointer is NULL, Failed to allocate memory! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }

    return Loc_u8ErrorState;
}

/*
 Name: DLL_u8ModifyDLLNodeByVal
 Input: Address of DLL_Tag structure (head & tail),
 Output: u8 Error or No Error
 Description: Function to modify Nodes, using a value (ID) to do so. It returns Error
              if list is empty or data is not found, else it returns No Error.
*/
u8 DLL_u8ModifyDLLNodeByVal(DLL_Tag_st *Cpy_pstDLLTag, NodeDLL *Cpy_pstNewNode, u32 Cpy_u32NodeID)
{
    /* Define local variable to set the error state = No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Check 1: DLL is empty */
    if (DLL_u8IsPtrNull(Cpy_pstDLLTag->head) == ERR_TYPES_U8_NULL_PTR)
    {
        /* Update error state, Pointer is NULL, List is Empty! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }
    /* Check 2: DLL is not empty */
    else
    {
        /* Define local pointer Current to Node = head */
        NodeDLL *Loc_pstCurrent = Cpy_pstDLLTag->head;

        /* Loop: Until the end of DLL, or Node is found */
        while ((DLL_u8IsPtrNull(Loc_pstCurrent) != ERR_TYPES_U8_NULL_PTR) && (Loc_pstCurrent->ID != Cpy_u32NodeID))
        {
            /* Increment current Node */
            Loc_pstCurrent = Loc_pstCurrent->next;
        }

        /* Check 2.1: Node is not found */
        if (DLL_u8IsPtrNull(Loc_pstCurrent) == ERR_TYPES_U8_NULL_PTR)
        {
            /* Update error state, Pointer is NULL, Node not found! */
            Loc_u8ErrorState = ERR_TYPES_U8_NOT_FOUND;
        }
        /* Check 2.2: Node is found */
        else
        {
            strcpy(Loc_pstCurrent->Name, Cpy_pstNewNode->Name);
            Loc_pstCurrent->Age = Cpy_pstNewNode->Age;
            strcpy(Loc_pstCurrent->Title, Cpy_pstNewNode->Title);
            Loc_pstCurrent->Salary = Cpy_pstNewNode->Salary;
        }
    }

    return Loc_u8ErrorState;
}

/*
 Name: DLL_vdDelDLLNodeAtBeg
 Input: Pointer to Address of head Node, Pointer to Address of current Node
 Output: void
 Description: Static Function to delete Node at the beginning of DLL. This function is called
              by "DLL_u8DeleteDLLNodeByVal" and "DLL_u8DeleteDLLNodeByPos" functions only.
*/
static vd DLL_vdDelDLLNodeAtBeg(NodeDLL **Cpy_pstHead, NodeDLL **Cpy_pstCurrent)
{
    /* Step 1: Increment headNode */
    *Cpy_pstHead = (*Cpy_pstHead)->next;
    /* Step 2: Make headNode->prev = NULL */
    (*Cpy_pstHead)->prev = NULL;
    /* Step 3: Delete currentNode */
    free(*Cpy_pstCurrent);
}

/*
 Name: DLL_vdDelDLLNodeAtMid
 Input: Pointer to Address of current Node
 Output: void
 Description: Static Function to delete Node in the middle of DLL. This function is called
              by "DLL_u8DeleteDLLNodeByVal" and "DLL_u8DeleteDLLNodeByPos" functions only.
*/
static vd DLL_vdDelDLLNodeAtMid(NodeDLL **Cpy_pstCurrent)
{
    /* Step 1: Make currentNode->prev->next = currentNode->next */
    (*Cpy_pstCurrent)->prev->next = (*Cpy_pstCurrent)->next;
    /* Step 2: Make currentNode->next->prev = currentNode->prev */
    (*Cpy_pstCurrent)->next->prev = (*Cpy_pstCurrent)->prev;
    /* Step 3: Delete currentNode */
    free(*Cpy_pstCurrent);
}

/*
 Name: DLL_vdDelDLLNodeAtEnd
 Input: Pointer to Address of tail Node, Pointer to Address of current Node
 Output: void
 Description: Static Function to delete Node at the end of DLL. This function is called
              by "DLL_u8DeleteDLLNodeByVal" and "DLL_u8DeleteDLLNodeByPos" functions only.
*/
static vd DLL_vdDelDLLNodeAtEnd(NodeDLL **Cpy_pstTail, NodeDLL **Cpy_pstCurrent)
{
    /* Step 1: Decrement tailNode */
    *Cpy_pstTail = (*Cpy_pstTail)->prev;
    /* Step 2: Make tailNode->next = NULL */
    (*Cpy_pstTail)->next = NULL;
    /* Step 3: Delete currentNode  */
    free(*Cpy_pstCurrent);
}

/*
 Name: DLL_u8DeleteDLLNodeByVal
 Input: Address of DLL_Tag structure (head & tail), u32 Node ID to be deleted
 Output: u8 Error or No Error
 Description: Function to delete Nodes, using a value (ID) to do so. It returns Error
              if list is empty or data is not found, else it returns No Error.
*/
u8 DLL_u8DeleteDLLNodeByVal(DLL_Tag_st *Cpy_pstDLLTag, u32 Cpy_u32NodeID)
{
    /* Define local variable to set the error state = No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Check 1: DLL is empty */
    if (DLL_u8IsPtrNull(Cpy_pstDLLTag->head) == ERR_TYPES_U8_NULL_PTR)
    {
        /* Update error state, Pointer is NULL, List is Empty! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }
    /* Check 2: DLL is not empty */
    else
    {
        /* Define local pointer Current to Node = head */
        NodeDLL *Loc_pstCurrent = Cpy_pstDLLTag->head;

        /* Loop: Until the end of DLL, or Node is found */
        while ((DLL_u8IsPtrNull(Loc_pstCurrent) != ERR_TYPES_U8_NULL_PTR) && (Loc_pstCurrent->ID != Cpy_u32NodeID))
        {
            /* Increment current Node */
            Loc_pstCurrent = Loc_pstCurrent->next;
        }

        /* Check 2.1: Node is not found */
        if (DLL_u8IsPtrNull(Loc_pstCurrent) == ERR_TYPES_U8_NULL_PTR)
        {
            /* Update error state, Pointer is NULL, Node not found! */
            Loc_u8ErrorState = ERR_TYPES_U8_NOT_FOUND;
        }
        /* Check 2.2: Node is found */
        else
        {
            /* Check 2.2.1: There is only one Node in DLL */
            if (DLL_u8IsPtrNull(Cpy_pstDLLTag->head->next) == ERR_TYPES_U8_NULL_PTR)
            {
                DLL_u8DeleteDLL(Cpy_pstDLLTag);
            }
            /* Check 2.2.2: Node is found at the beginning of DLL */
            else if (Loc_pstCurrent == Cpy_pstDLLTag->head)
            {
                DLL_vdDelDLLNodeAtBeg(&Cpy_pstDLLTag->head, &Loc_pstCurrent);
            }
            /* Check 2.2.3: Node is found at the end of DLL */
            else if (Loc_pstCurrent == Cpy_pstDLLTag->tail)
            {
                DLL_vdDelDLLNodeAtEnd(&Cpy_pstDLLTag->tail, &Loc_pstCurrent);
            }
            /* Check 2.2.4: Node is found in the middle of DLL*/
            else
            {
                DLL_vdDelDLLNodeAtMid(&Loc_pstCurrent);
            }
        }
    }

    return Loc_u8ErrorState;
}

/*
 Name: DLL_u8DeleteDLLNodeByPos
 Input: Address of DLL_Tag structure (head & tail), u32 Node position to be deleted
 Output: u8 Error or No Error
 Description: Function to delete DLL Nodes, using a position to do so. It returns Error
              if list is empty or data is not found, else it returns No Error.
*/
u8 DLL_u8DeleteDLLNodeByPos(DLL_Tag_st *Cpy_pstDLLTag, u32 Cpy_u32NodePos)
{
    /* Define local variable to set the error state = No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Check 1: DLL is empty */
    if (DLL_u8IsPtrNull(Cpy_pstDLLTag->head) == ERR_TYPES_U8_NULL_PTR)
    {
        /* Update error state, Pointer is NULL, List is Empty! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }
    /* Check 2: DLL is not empty */
    else
    {
        /* Define local pointer Current to Node = head */
        NodeDLL *Loc_pstCurrent = Cpy_pstDLLTag->head;

        /* Check 2.1: Delete at the begininng of DLL */
        if (Cpy_u32NodePos == DLL_U8_BEG_OF_LIST)
        {
            DLL_vdDelDLLNodeAtBeg(&Cpy_pstDLLTag->head, &Loc_pstCurrent);
        }
        /* Check 2.2: Delete in between or at the end of DLL */
        else if (Cpy_u32NodePos > DLL_U8_BEG_OF_LIST)
        {
            /* Define local variable to set the flag state = DOWN */
            u8 Loc_u8Flag = DLL_U8_FLAG_DOWN;

            /* Loop: Until the position is reached, or the end of DLL is reached */
            for (u32 Loc_u32Index = DLL_U8_BEG_OF_LIST; Loc_u32Index < Cpy_u32NodePos; Loc_u32Index++)
            {
                /* Check 2.2.1: Reached the of end DLL */
                if (DLL_u8IsPtrNull(Loc_pstCurrent->next))
                {
                    /* Update flag state, Pointer is NULL! */
                    Loc_u8Flag = DLL_U8_FLAG_UP;
                    break;
                }
                /* Check 2.2.2: Did not reach the of end DLL */
                else
                {
                    /* Increment Current Node */
                    Loc_pstCurrent = Loc_pstCurrent->next;
                }
            }
            /* Check 2.3: Flag DOWN */
            if (Loc_u8Flag == DLL_U8_FLAG_DOWN)
            {
                /* Check 2.3.1: Did not reach the of end DLL */
                if (DLL_u8IsPtrNull(Loc_pstCurrent->next) != ERR_TYPES_U8_NULL_PTR)
                {
                    DLL_vdDelDLLNodeAtMid(&Loc_pstCurrent);
                }
                /* Check 2.3.2: Reached the of end DLL */
                else
                {
                    DLL_vdDelDLLNodeAtEnd(&Cpy_pstDLLTag->tail, &Loc_pstCurrent);
                }
            }
            /* Check 2.4: Flag UP */
            else if (Loc_u8Flag == DLL_U8_FLAG_UP)
            {
                /* Update error state, Pointer is NULL, Node not found! */
                Loc_u8ErrorState = ERR_TYPES_U8_NOT_FOUND;
            }
        }
    }

    return Loc_u8ErrorState;
}

/*
 Name: DLL_u8DeleteDLL
 Input: Address of DLL_Tag structure (head & tail)
 Output: u8 Error or No Error
 Description: Function to delete all DLL Nodes. It returns Error if list is empty,
              else it returns No Error.
*/
u8 DLL_u8DeleteDLL(DLL_Tag_st *Cpy_pstDLLTag)
{
    /* Define local variable to set the error state = No Error */
    u8 Loc_u8ErrorState = ERR_TYPES_U8_NO_ERROR;

    /* Check 1: DLL is empty */
    if (DLL_u8IsPtrNull(Cpy_pstDLLTag->head) == ERR_TYPES_U8_NULL_PTR)
    {
        /* Update error state, Pointer is NULL, List is Empty! */
        Loc_u8ErrorState = ERR_TYPES_U8_NULL_PTR;
    }
    /* Check 2: DLL is not empty */
    else
    {
        /* Define local pointer Current to Node = head */
        NodeDLL *Loc_pstCurrent = Cpy_pstDLLTag->head;

        /* Loop: Until the end of DLL */
        while (DLL_u8IsPtrNull(Loc_pstCurrent) != ERR_TYPES_U8_NULL_PTR)
        {
            /* Increment head Node */
            Cpy_pstDLLTag->head = Cpy_pstDLLTag->head->next;

            free(Loc_pstCurrent);
            /* Make current points to head Node */
            Loc_pstCurrent = Cpy_pstDLLTag->head;
        }
    }

    return Loc_u8ErrorState;
}