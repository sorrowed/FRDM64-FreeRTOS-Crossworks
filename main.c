#include "FreeRTOS.h"
#include "task.h"

#include <__cross_studio_io.h>

#include <stdbool.h>

static void DebugPrintTask( void* parms );

void main(void)
{
	xTaskCreate( DebugPrintTask, "DebugPrint", configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY, 0 );

	vTaskStartScheduler();

	while( true );
}

void DebugPrintTask( void* parms )
{
	while( true )
	{
		vTaskDelay(500);
		debug_printf( "Blaat\n" );
		vTaskDelay(500);
	}
}