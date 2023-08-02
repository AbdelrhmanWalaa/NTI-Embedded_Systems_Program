/*
 * EMS_Interface.h
 *
 *   Created on: Aug 1, 2022
 *       Author: Abdelrhman Walaa
 *  Description: This file contains all EMS -Employee Management System- functions' prototypes and definitions (Macros) to avoid magic numbers.
 */

#ifndef EMS_INTERFACE_H_
#define EMS_INTERFACE_H_

/* STD -> Standard Library Layer */
#include <stdio.h>
#include <stdlib.h>

/* LIB -> Library Layer */
#include "../LIB/STD_TYPES.h"
#include "../LIB/ERR_TYPES.h"

/* SRV -> Service Layer */
#include "../SRV/CON_Interface.h"

/* DS -> Data Structure Layer */
#include "../DS/DLL_Interface.h"

enum enOptions{
    EMS_enIns = 1, EMS_enDel, EMS_enMod, EMS_enDsp, EMS_enDspAll, EMS_enExt
};

#define EMS_U8_NO_OF_EMPS_INIT      5

#define EMS_U8_MAX_NO_OF_DIGITS     3
#define EMS_U32_MAX_NO_OF_DIGITS    10

// Functions' Prototypes
extern vd EMS_vdStartProg  (void);
extern vd EMS_vdDefaultProg(void);
extern vd EMS_vdExitProg   (void);

extern vd EMS_vdInsertEmp     (void);
extern vd EMS_vdDeleteEmp     (void);
extern vd EMS_vdModifyEmp     (void);
extern vd EMS_vdDisplayEmp    (void);
extern vd EMS_vdDisplayAllEmps(void);

#endif /* EMS_INTERFACE_H_ */