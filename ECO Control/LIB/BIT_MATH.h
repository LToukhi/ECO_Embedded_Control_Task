/*
 *  Created on: 11 Aug 2023
 *      Author: Youssef
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

///////////////////////

#define SET_BIT(Reg,bit_number)     Reg |= 1<<bit_number
#define CLR_BIT(Reg,bit_number)     Reg &= ~(1<<bit_number)
#define TOG_BIT(Reg,bit_number)  Reg ^= 1<<bit_number
#define GET_BIT(Reg,bit_number)     (Reg>>bit_number) & 0x01
#define SET_BYTE(Reg,Value)         (Reg = Value)

//////////////////////


#endif /* BIT_MATH_H_ */
