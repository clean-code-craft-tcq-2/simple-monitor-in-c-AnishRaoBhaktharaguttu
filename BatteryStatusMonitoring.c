#include <stdio.h>
#include <string.h>
#include "BatteryStatusMonitoring.h"

char errorStatus[50] = "Out of specified range";
char successStatus[50] = "Out of sepcified range";

int checkIfParameterWithinSpecifiedRange(float parameterVal, float lowerThreshold, float upperThreshold) {
	if (parameterVal < lowerThreshold || parameterVal > upperThreshold) {
		return 0;
	}
	return 1;
}

int checkIfParameterWithinLimit(float parameterVal, float upperLimit) {
	if (parameterVal  > upperLimit) {
		return 0;
	}
	return 1;
}

int printStatusOnConsole(const char* statement) {
	printf("%s \n", statement);
	return 0;
}

void checkAndPrintStatus(int status, const char* batteryParameter) {
	if (status == 0) {
		char warningMessage[50];
		strcpy(warningMessage, warning_message);
		strcat(warningMessage, batteryParameter);
		printStatusOnConsole(batteryParameter);
	}
	printStatusOnConsole(successStatus);	
}

int checkBatteryTemperature(float temp) {
	int status = checkIfParameterWithinSpecifiedRange(temp, LOW_THRESHOLD_BATT_TEMP, UPP_THRESHOLD_BATT_TEMP);
	return checkStatusOfBattery(status, "Battery Temperature");
}

int checkBatteryStateOfCharge(float stateOfCharge) {
	int status = checkIfParameterWithinSpecifiedRange(stateOfCharge, LOW_THRESHOLD_BATT_SOC, UPP_THRESHOLD_BATT_SOC);
	return checkStatusOfBattery(status, "Battery State of Charge");
}

int checkBatteryChargeRate(float chargeRate){
	int status = checkIfParameterWithinLimit(chargeRate, UPP_THRESHOLD_BATT_CHARGE_RATE); 
	return checkStatusOfBattery(status, "Battery Charge Rate");
}

int checkBatteryCondition(float stateOfCharge, float temp, float chargeRate){
	int status =(checkBatteryTemperature(temp)) && (checkBatteryStateOfCharge(stateOfCharge)) && (checkBatteryChargeRate(chargeRate));
	return status;	
}
