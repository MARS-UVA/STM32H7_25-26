/*

 * util.h

 *

 *  Created on: Mar 9, 2025

 *      Author: Austen

 */



// For sending/receiving packets on CAN bus



#ifndef INC_CAN_H_

#define INC_CAN_H_



#include "main.h"



void sendCANMessage(FDCAN_HandleTypeDef *hfdcan, int identifier, char *message, uint8_t length);

void sendGlobalEnableFrame(FDCAN_HandleTypeDef *hfdcan);



#endif /* INC_CAN_H_ */
