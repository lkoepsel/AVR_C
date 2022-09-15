/* map(value, fromLow, fromHigh, toLow, toHigh)
*   Re-maps a number from one range to another.
*   Parameters 
*       value: the number to map.
*       in_min: the lower bound of the value’s current range.
*       in_max: the upper bound of the value’s current range.
*       out_min: the lower bound of the value’s target range.
*       out_max: the upper bound of the value’s target range.
*   Returns: int32_t mapped value
*/

#ifndef MAP_H
#define MAP_H

#include <stdint.h>

int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) ;

#endif
