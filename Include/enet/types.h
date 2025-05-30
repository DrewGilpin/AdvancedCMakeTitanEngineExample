/** 
 @file  types.h
 @brief type definitions for ENet
*/
#ifndef __ENET_TYPES_H__
#define __ENET_TYPES_H__

//typedef unsigned char enet_uint8;       /**< unsigned 8-bit type  */
//typedef unsigned short enet_uint16;     /**< unsigned 16-bit type */
//typedef unsigned int enet_uint32;      /**< unsigned 32-bit type */

//FOR ESENTHEL CHANGED ABOVE TO BELOW

typedef U8 enet_uint8;       /**< unsigned 8-bit type  */
typedef U16 enet_uint16;     /**< unsigned 16-bit type */
typedef U32 enet_uint32;      /**< unsigned 32-bit type */

/* Ensure ENet headers can be included before engine macros
   by providing a standard 8-bit character type. */
typedef char char8;

#endif /* __ENET_TYPES_H__ */

