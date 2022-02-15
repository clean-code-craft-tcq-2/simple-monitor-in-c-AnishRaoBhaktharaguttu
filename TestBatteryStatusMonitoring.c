#include <stdio.h>
#include <assert.h>
#include "BatteryStatusMonitoring.h"


void testCheckBatteryCondition(float stateOfCharge, float temp, float chargeRate, int expStatus){
	assert(checkBatteryCondition(stateOfCharge, temp, chargeRate) == expStatus);
}

int main() {
 testCheckBatteryCondition(60, 30, 0.72, 1);
}
