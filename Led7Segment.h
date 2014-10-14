/*-----------------------------------------------------------------------------
 * Name:    Led7Segment.h
 * Purpose: Low level Led7Segment definitions
 *----------------------------------------------------------------------------*/

#ifndef __LED7SEGMENT_H
#define __LED7SEGMENT_H

#include <stdint.h>

void Led7Segment_Initialize (void);
void Led7Segment_Uninitialize (void);
void Led7Segment_On (uint32_t);
void Led7Segment_Off (uint32_t);
void Led7Segment_Out (uint32_t);
uint32_t Led7Segment_Num (void);
void Led7Segment_Write(short, short);
void Led7Segment_PrintNumber (int, short);
void Led7Segment_PrintDecNumber (int);
void Led7Segment_PrintHexNumber (int);

#endif /* __LED7SEGMENT_H */
