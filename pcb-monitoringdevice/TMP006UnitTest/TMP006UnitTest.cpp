// University of Southampton, 2012
// EMECS Group Design Project

#include <stdint.h>
#include <stdbool.h>
#include "efm32.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "trace.h"
#include "gbee.h"
#include "gbee-util.h"
#include "xbee_if.h"
#include "uartmanager.h"
#include "rtc.h"

// include files for sensors
#include "temperaturesensor.h"

#define	SENSOR_TEMP_READ_PERIOD	2

Sensor * temp_Sensor;

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
	TRACE_SWOSetup();
	
	TemperatureSensor * tmp = new TemperatureSensor(1000);
	printf("TS device id %x manid %x \n", tmp->getDeviceID(), tmp->getManufacturerID());
	temp_Sensor = tmp;
	
	uint16_t size;
	SensorMessage *msg;
	TemperatureMessage *tempMsg;
	
	while (1)
	{
		RTC_Trigger(100, NULL);
		EMU_EnterEM2(true);
		
				printf("sample and read for Temperature sensor \n");
				temp_Sensor->sampleSensorData();
				
					msg = (SensorMessage *) temp_Sensor->readSensorData(&size);
		
					tempMsg = (TemperatureMessage *) msg->sensorMsgArray;
					 printf("TMP: %f \n", tempMsg->Tobj);
					
	}

}
