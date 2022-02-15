#include <stdio.h>
#include <assert.h>
#include "BatteryStatusMonitoring.h"


void testCheckBatteryCondition(float stateOfCharge, float temp, float chargeRate, enum chosenLanguage language, int expStatus){
	assert(checkBatteryCondition(stateOfCharge, temp, chargeRate, language) == expStatus);
}

int main() {
	testCheckBatteryCondition(45, 20, 0.6, English, 1);
	testCheckBatteryCondition(90, 43, 0.6, English, 0);
	testCheckBatteryCondition(92, 20, 0.63, German, 0);
	testCheckBatteryCondition(2, 72, 0.9, German, 0);
	testCheckBatteryCondition(21, 90, 0.63, English, 0);
	testCheckBatteryCondition(23, 78, 0.67, English, 0);
	testCheckBatteryCondition(21, 22, 0.59, English, 0);
	testCheckBatteryCondition(22, 10, 0.52, German, 0);
	testCheckBatteryCondition(21, 45, 0.91, German, 0);
	testCheckBatteryCondition(25, 45, 0.01, German, 0);
}
