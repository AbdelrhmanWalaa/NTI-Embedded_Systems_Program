/*
 * DLL_Interface.h
 *
 *   Created on: Aug 1, 2022
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all DLL -Double Linked List- functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef DLL_INTERFACE_H_
#define DLL_INTERFACE_H_

/* STD -> Standard Library Layer */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* LIB -> Library Layer */
#include "../LIB/STD_TYPES.h"
#include "../LIB/ERR_TYPES.h"

/* DLL Node structure, to store sort of data */
typedef struct nodeDLL {
  u8  Age;
  u32 ID;
  u32 Salary;  
  u8  Name[30];
  u8  Title[30];   
  struct nodeDLL *next;
  struct nodeDLL *prev;
} NodeDLL;

/* DLL_Tag Structure, to store main pointers of DLL; head and tail */
typedef struct DLL_Tag {
  NodeDLL *head;
  NodeDLL *tail;
} DLL_Tag_st;

#define DLL_U8_FLAG_DOWN    0
#define DLL_U8_FLAG_UP      1

#define DLL_U8_BEG_OF_LIST  0
#define DLL_U8_END_OF_LIST  1

// Functions' Prototypes
extern vd DLL_vdDLLInit(DLL_Tag_st *Copy_pstDLLTag);

extern u8 DLL_u8DisplayDLL       (DLL_Tag_st *Cpy_pstDLLTag);
extern u8 DLL_u8DisplayReverseDLL(DLL_Tag_st *Cpy_pstDLLTag);

extern u8 DLL_u8SearchDLLByVal(DLL_Tag_st *Cpy_pstDLLTag, NodeDLL *Cpy_pstRetSrchNode, u32 Cpy_u32NodeID);

extern u8 DLL_u8CountDLLNodes(DLL_Tag_st *Cpy_pstDLLTag, u32 *Cpy_pu32RetCount);

extern u8 DLL_u8InsertDLLNodeByPos(DLL_Tag_st *Cpy_pstDLLTag, NodeDLL *Cpy_pstNewNode, u32 Cpy_u32NodePos);

extern u8 DLL_u8ModifyDLLNodeByVal(DLL_Tag_st *Cpy_pstDLLTag, NodeDLL *Cpy_pstNewNode, u32 Cpy_u32NodeID);

extern u8 DLL_u8DeleteDLLNodeByVal(DLL_Tag_st *Cpy_pstDLLTag, u32 Cpy_u32NodeID);
extern u8 DLL_u8DeleteDLLNodeByPos(DLL_Tag_st *Cpy_pstDLLTag, u32 Cpy_u32NodePos);
extern u8 DLL_u8DeleteDLL         (DLL_Tag_st *Cpy_pstDLLTag);

#endif /* DLL_INTERFACE_H_ */