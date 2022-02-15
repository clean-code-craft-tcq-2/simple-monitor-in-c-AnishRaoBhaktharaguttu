#include <stdio.h>
#include <assert.h>
#include "BatteryStatusMonitoring.h"


void testCheckBatteryCondition(float stateOfCharge, float temp, float chargeRate, enum chosenLanguage language, int expStatus){
	assert(checkBatteryCondition(stateOfCharge, temp, chargeRate, language) == expStatus);
}

int main() {
 testCheckBatteryCondition(60, 30, 0.72, English, 1);
 //testCheckBatteryCondition(90, 35, 0.72, German, 0);
 //testCheckBatteryCondition(60, 53, 0.85, English, 0);
 //testCheckBatteryCondition(60, 35, 0.78, English, 0);
 //testCheckBatteryCondition(60, 35, 0.52, German, 0);
}
