#include "api_misc.h"
#include "app_process.h"
uint32_t g_led_heart_timer_cnt = 1;



void _mcu_heart_process(void)
{
			if(TIMER_TRIG(g_led_heart_timer_cnt))
			{
				HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
				OPEN_TIMER(g_led_heart_timer_cnt,100);
			}
}



