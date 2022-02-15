#include <stdio.h>
#include <assert.h>
#include "BatteryStatusMonitoring.h"


void testCheckBatteryCondition(float stateOfCharge, float temp, float chargeRate, enum chosenLanguage language, int expStatus){
	assert(checkBatteryCondition(stateOfCharge, temp, chargeRate, language) == expStatus);
}

int main() {
	testCheckBatteryCondition(45, 20, 0.6, English, 1);
	testCheckBatteryCondition(90, 43, 0.6, English, 0);
	testCheckBatteryCondition(92, 20, 0.63, English, 0);
}
