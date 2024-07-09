/*
 * Copyright 2016-2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    MKL46Z4_LightSensor.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "MKL46Z4.h"
#include "interface.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

void main() {
	stateMode = MODE_START_UP;
	APP_Init();
	while(1){
		switch (stateMode){
		case MODE_START_UP:
			App_Sleep();
			break;
		case MODE_BUTTON_LED:
			BUTTON_LED();
			break;
		case MODE_LIGHTSENSOR_LED:
			LIGHTSENSOR_LED();
			break;
		case MODE_LIGHTSENSOR_USB_COMMS:
			LIGHTSENSOR_USB_COMMS();
			break;
		}

	}

}
