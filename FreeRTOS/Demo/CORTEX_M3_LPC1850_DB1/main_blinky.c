/*
 * FreeRTOS V202011.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://www.gihub.com/FreeRTOS
 *
 * 1 tab == 4 spaces!
 */

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>

#include "LPC18xx.h"
#include "lpc1850_db1.h"
#include "lpc18xx_gpio.h"
#include "lpc18xx_scu.h"

static void prvQueueReceiveTask( void *pvParameters );
static void prvQueueSendTask( void *pvParameters );
//extern int _write(int file, char *ptr, int len);

#define mainQUEUE_RECEIVE_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )
#define mainQUEUE_LENGTH					( 1 )
//#define mainQUEUE_SEND_FREQUENCY_MS			( 200 / portTICK_PERIOD_MS )
/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;

void main_blinky( void )
{
	SystemInit();

	scu_pinmux(D3_SCU_CONFIG);
	scu_pinmux(D4_SCU_CONFIG);
	GPIO_SetDir(D3_GPIO_PORT, D3_GPIO_MASK, 1);
	GPIO_SetDir(D4_GPIO_PORT, D4_GPIO_MASK, 1);
	GPIO_ClearValue(D3_GPIO_PORT, D3_GPIO_MASK);
	GPIO_ClearValue(D4_GPIO_PORT, D4_GPIO_MASK);

	/* Create the queue. */
	xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( uint32_t ) );

	if( xQueue != NULL )
	{
		/* Start the two tasks as described in the comments at the top of this
		file. */
		xTaskCreate( prvQueueReceiveTask,				/* The function that implements the task. */
					"Rx", 								/* The text name assigned to the task - for debug only as it is not used by the kernel. */
					configMINIMAL_STACK_SIZE, 			/* The size of the stack to allocate to the task. */
					NULL, 								/* The parameter passed to the task - not used in this case. */
					mainQUEUE_RECEIVE_TASK_PRIORITY, 	/* The priority assigned to the task. */
					NULL );								/* The task handle is not required, so NULL is passed. */

		xTaskCreate( prvQueueSendTask,
		            "TX",
		            configMINIMAL_STACK_SIZE,
		            NULL,
		            mainQUEUE_SEND_TASK_PRIORITY,
		            NULL );

		/* Start the tasks and timer running. */
		vTaskStartScheduler();
	}

	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the Idle and/or
	timer tasks to be created.  See the memory management section on the
	FreeRTOS web site for more details on the FreeRTOS heap
	http://www.freertos.org/a00111.html. */
	for( ;; );
}

static void prvQueueSendTask( void *pvParameters )
{
TickType_t xNextWakeTime;
const uint32_t ulValueToSend = 100UL;

	/* Remove compiler warning about unused parameter. */
	( void ) pvParameters;

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		GPIO_ToggleValue(D3_GPIO_PORT, D3_GPIO_MASK);
	}
}

volatile uint32_t ulRxEvents = 0;
static void prvQueueReceiveTask( void *pvParameters )
{
uint32_t ulReceivedValue;
const uint32_t ulExpectedValue = 100UL;

	/* Remove compiler warning about unused parameter. */
	( void ) pvParameters;

	for( ;; )
	{
		GPIO_ToggleValue(D4_GPIO_PORT, D4_GPIO_MASK);
	}
}
/*-----------------------------------------------------------*/
