#ifndef _PROTOCOL_H
#define _PROTOCOL_H

#include "stdint.h"
#include "string.h"

uint8_t ProtocolParse(uint8_t *mess,uint8_t len);

uint8_t ProtocolPackage(uint8_t *buf,uint8_t cmd);


#endif

