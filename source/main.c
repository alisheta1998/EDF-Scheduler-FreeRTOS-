/*****Graduation Project******/

/*
	*EDF Scheduler
	*/


/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"
#include "semphr.h"
#include "event_groups.h"
#include "queue.h"




/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )


/*Task Handlers*/
TaskHandle_t Task1Handler = NULL;
TaskHandle_t Task2Handler = NULL;
TaskHandle_t Task3Handler = NULL;

/* Variables for timing calculations*/
int task_1_in_time = 0 , task_1_out_time = 0, task_1_total_time;
int task_2_in_time = 0 , task_2_out_time = 0, task_2_total_time;
int task_3_in_time = 0 , task_3_out_time = 0, task_3_total_time;
int system_time = 0;
int cpu_load =0 ;

char runTimeStatsBuf[190];

/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/

/* Task to be created. */
void Task_1( void * pvParameters )
{
		int i=0;
		int xLastWakeTime = xTaskGetTickCount();
	
		vTaskSetApplicationTaskTag(NULL,(void *) 1);
    for( ;; )
    {
			/* Task code goes here. */
			for(i=0;i<1000000;i++)
			{
				/*Simulate heavy load*/
			}
			vTaskDelayUntil(&xLastWakeTime,1000);
		}
}

/* Task to be created. */
void Task_2( void * pvParameters )
{
		int i=0;
		int xLastWakeTime = xTaskGetTickCount();
	
		vTaskSetApplicationTaskTag(NULL,(void *) 2);
    for( ;; )
    {
			/* Task code goes here. */
			for(i=0;i<100000;i++)
			{
				/*Simulate heavy load*/
			}
			vTaskDelayUntil(&xLastWakeTime,100);
		}
}

/* Task to be created. */
void Task_3( void * pvParameters )
{
		int i=0;
		int xLastWakeTime = xTaskGetTickCount();
	
		vTaskSetApplicationTaskTag(NULL,(void *) 3);
    for( ;; )
    {
			/* Task code goes here. */
			for(i=0;i<1000000;i++)
			{
				/*Simulate heavy load*/
			}
			vTaskDelayUntil(&xLastWakeTime,500);
		}
}


/*Implementation of Tick Hook*/
void vApplicationTickHook(void)
{
	GPIO_write(PORT_0,PIN1,PIN_IS_HIGH);
	GPIO_write(PORT_0,PIN1,PIN_IS_LOW);
}

/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();
	/*Creating the Queue*/
	
	
	/* Create the task, storing the handle. */
    xTaskPeriodicCreate(
										Task_1,      		/* Function that implements the task. */
                    "Task 1",        /* Text name for the task. */
                    100,      						/* Stack size in words, not bytes. */
                    ( void * ) 0,    			/* Parameter passed into the task. */
                    1,										/* Priority at which the task is created. */
                    &Task1Handler,
										1000); /* Used to pass out the created task's handle. */
    xTaskPeriodicCreate(
										Task_2,      		/* Function that implements the task. */
                    "Task 2",        /* Text name for the task. */
                    100,      						/* Stack size in words, not bytes. */
                    ( void * ) 0,    			/* Parameter passed into the task. */
                    1,										/* Priority at which the task is created. */
                    &Task2Handler,
										100); /* Used to pass out the created task's handle. */
		xTaskPeriodicCreate(
										Task_3,      		/* Function that implements the task. */
                    "Task 3",        /* Text name for the task. */
                    100,      						/* Stack size in words, not bytes. */
                    ( void * ) 0,    			/* Parameter passed into the task. */
                    1,										/* Priority at which the task is created. */
                    &Task3Handler,				/* Used to pass out the created task's handle. */
										500); 								/* Period and Deadline of the task*/
		
    /* Create Tasks here */

	/* Now all the tasks have been started - start the scheduler.*/
	
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Configure Trace timer 1 and read T1TC to get current tick*/
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/


