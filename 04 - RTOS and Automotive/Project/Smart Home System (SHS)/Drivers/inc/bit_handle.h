/*
 * bit_handle.h
 *
 * Created: 7/7/2021 9:24:44 AM
 *  Author: MahmoudH
 */ 


#ifndef BIT_HANDLE_H_
#define BIT_HANDLE_H_

#define setBit(REG,BN)							((REG) |=  (1<<(BN)))
#define clearBit(REG,BN)						((REG) &= ~(1<<(BN)))
#define toggleBit(REG,BN)						((REG) ^=  (1<<(BN)))

#define setBits(REG,BM)							((REG) |=  (BM))
#define clearBits(REG,BM)						((REG) &= ~(BM))
#define toggleBits(REG,BM)						((REG) ^=  (BM))

#define setAllBits(REG)							((REG)  =  (0xFF))
#define clearAllBits(REG)						((REG)  =  (0x00))
#define toggleAllBits(REG)						((REG) ^=  (0xFF))

#define readBit(REG,BN)							(((REG)>>(BN))&0x01)

#endif /* BIT_HANDLE_H_ */