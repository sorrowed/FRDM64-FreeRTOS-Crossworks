#include "FreeRTOS.h"
#include "task.h"

#include "fsl_clock_manager.h"
#include "fsl_port_hal.h"
#include "fsl_gpio_hal.h"


#include <__cross_studio_io.h>

#include <stdbool.h>

static void DebugPrintTask( void* parms );
static void LedTask( void* args );

void main(void)
{
	xTaskCreate( DebugPrintTask, "DebugPrint", configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY, 0 );
	xTaskCreate( LedTask, "Led", configMINIMAL_STACK_SIZE, 0, tskIDLE_PRIORITY, 0 );

	vTaskStartScheduler();

	while( true );
}

void DebugPrintTask( void* args )
{
	while( true )
	{
		vTaskDelay(500);
		debug_printf( "Blaat\n" );
		vTaskDelay(500);
	}
}

void LedTask( void* args )
{
	CLOCK_SYS_EnablePortClock( HW_PORTB );
	PORT_HAL_SetMuxMode(PORTB_BASE,22,kPortMuxAsGpio);
	GPIO_HAL_SetPinDir( PTB_BASE, 22, kGpioDigitalOutput );

	CLOCK_SYS_EnablePortClock( HW_PORTE );
	PORT_HAL_SetMuxMode(PORTE_BASE,26,kPortMuxAsGpio);
	GPIO_HAL_SetPinDir( PTE_BASE, 26, kGpioDigitalOutput );

	CLOCK_SYS_EnablePortClock( HW_PORTB );
	PORT_HAL_SetMuxMode(PORTB_BASE,21,kPortMuxAsGpio);
	GPIO_HAL_SetPinDir( PTB_BASE, 21, kGpioDigitalOutput );

	while( true )
	{
		int i = rand( );
		GPIO_HAL_WritePinOutput(PTB_BASE, 22, i % 2 ? 0 : 1 );

		i = rand( );
		GPIO_HAL_WritePinOutput(PTE_BASE, 26, i % 2 ? 0 : 1 );

		i = rand( );
		GPIO_HAL_WritePinOutput(PTB_BASE, 21, i % 2 ? 0 : 1 );

		vTaskDelay( 500 );
	}
}