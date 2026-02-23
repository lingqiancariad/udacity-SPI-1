#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void SPI_initMaster(void); 
void SPI_initSlave(void);
void SPI_sendByte(const uint8 data);
uint8 SPI_recieveByte(void);

#endif
