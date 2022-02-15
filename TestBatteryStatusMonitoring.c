#include <stdio.h>
#include <assert.h>
#include "BatteryStatusMonitoring.h"


void testCheckBatteryCondition(float stateOfCharge, float temp, float chargeRate, enum chosenLanguage language, int expStatus){
	assert(checkBatteryCondition(stateOfCharge, temp, chargeRate, language) == expStatus);
}

int main() {
	testCheckBatteryCondition(45, 20, 0.6, English, 1);
	testCheckBatteryCondition(90, 54, 0.92, German, 0);
	testCheckBatteryCondition(90, 43, 0.6, English, 0);
	testCheckBatteryCondition(70, 2, 0.9, German, 0);
	testCheckBatteryCondition(92, 20, 0.63, English, 0);
	testCheckBatteryCondition(78, 22, 0.67, English, 0);
	testCheckBatteryCondition(22, 20, 0.59, English, 0);
	testCheckBatteryCondition(10, 22, 0.52, German, 0);
	testCheckBatteryCondition(45, 21, 0.91, English, 0);
	testCheckBatteryCondition(45, 25, 0.01, German, 0);
}
