#include <stdio.h>
#include <assert.h>
#include "BatteryStatusMonitoring.h"

void testCheckBatteryTemperature(float temp, int expStatus) {
	assert(checkBatteryTemperature(temp) == expStatus);
}

void testCheckBatteryChargeRate(float chargeRate, int expStatus){
	assert(checkBatteryChargeRate(chargeRate) == expStatus);
}
 
void testCheckBatteryStateOfCharge(float stateOfCharge, int expStatus) {
	assert(checkBatteryStateOfCharge(stateOfCharge) == expStatus);
}

void testCheckBatteryCondition(float stateOfCharge, float temp, float chargeRate, int expStatus){
	assert(checkBatteryCondition(stateOfCharge, temp, chargeRate) == expStatus);
}

int main() {
 testCheckBatteryTemperature(-25, 1);
 testCheckBatteryTemperature(50, 1);
 testCheckBatteryTemperature(25, 1);
}
