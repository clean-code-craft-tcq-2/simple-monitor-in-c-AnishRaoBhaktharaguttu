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
 testCheckBatteryTemperature(-25, 0);
 testCheckBatteryTemperature(50, 0);
 testCheckBatteryTemperature(25, 1);
 testCheckBatteryStateOfCharge(10, 0);
 testCheckBatteryStateOfCharge(85, 0);
 testCheckBatteryStateOfCharge(50,1);
 testCheckBatteryChargeRate(0.92, 0);
 testCheckBatteryChargeRate(0.53, 1);
 testCheckBatteryCondition(60, 30, 0.72, 3);
 testCheckBatteryCondition(90, 23, 0.7, 2);
 testCheckBatteryCondition(95, 47, 0.61, 1);
 testCheckBatteryCondition(85, 70, 0.92, 0);
}
