#include <stdio.h>
#include <string.h>
#include "BatteryStatusMonitoring.h"

// Enum which contains the various states of the parameter
enum StatusOfParameter = {WITHIN_OPERATING_RANGE = 0,
			  LOW_LIMIT = 1,
			  UPPER_LIMIT = 2,
			  LOW_WARNING_LIMIT = 3,
			  UPPER_WARNING_LIMIT = 4
			  };

const char* warningMessages[] = {"Battery condition normal and within operating range",
				 "Battery at Risk: Lower limit exceeded for ",
				 "Battery at Risk: Upper limit exceeded for ",
				 "Battery abnormal: Approaching the lower warning limit for ",
				 "Battery abnormal: Approaching the upper warning limit for "
				 }

ParameterOperatingStructure tempOperatingLimits;

void setWarningMessage(int StatusOfParameter statusOfParameter, char* warnMsg) {
	strcpy(warnMsg, warningMessages[statusOfParameter]);
	strcat(warnMsg,  parameter);
}

int warnBatteryCondition(const char* parameter, int StatusOfParameter statusOfParameter) {
	char warnMsg[100];
	setWarningMessage(parameter, statusOfParameter, warnMsg);	
	printStatusOnConsole(warnMsg);
	return 0;
}

int checkIfParameterInWarningZone(ParameterOperatingStructure parameterOperatingStructure){
         if(parameterOperatingStructure.ParameterValue > parameterOperatingStructure.LowerLimit && 
	    parameterOperatingStructure.ParameterValue < parameterOperatingStructure.LowerWarningLimit){
		 
	       return warnBatteryCondition(parameterOperatingStructure.ParameterName, LOW_WARNING_LIMIT);
		 
	 } else if(parameterOperatingStructure.ParameterValue > parameterOperatingStructure.LowerLimit && 
	    parameterOperatingStructure.ParameterValue < parameterOperatingStructure.LowerWarningLimit){
		 
	       return warnBatteryCondition(parameterOperatingStructure.ParameterName, UPPER_WARNING_LIMIT);
	 }
	return 1;
}

int checkIfParameterWithinToleranceRange(ParameterOperatingStructure parameterOperatingStructure, int parameterStateChecked) {
	if (parameterOperatingStructure.ParameterValue > parameterOperatingStructure.LowerWarningLimit 
	    && parameterOperatingStructure.ParameterValue < parameterOperatingStructure.UpperWarningLimit){
	         return warnBatteryCondition(parameterOperatingStructure.ParameterName, parameterStateChecked);
	}else {
	         return checkIfParameterInWarningZone(parameterOperatingStructure);
	}
}

int checkIfParameterWithinLowerLimit(ParameterOperatingStructure paramOperatingStructure, int statusOfParameterInCheck) {
	if (paramOperatingStructure.ParameterVal  > paramOperatingStructure.LowerLimit) {
		warnBatteryCondition(parameterOperatingStructure.ParameterName, statusOfParameterInCheck);
		return 0;
	}
	return 1;
}

int checkIfParameterWithinUpperLimit(ParameterOperatingStructure paramOperatingStructure, int statusOfParameterInCheck) {
	if (paramOperatingStructure.ParameterVal  > paramOperatingStructure.UpperLimit) {
		warnBatteryCondition(parameterOperatingStructure.ParameterName, statusOfParameterInCheck);
		return 0;
	}
	return 1;
}

int printStatusOnConsole(const char* statement) {
	printf("%s \n", statement);
	return 0;
}

int checkStatusOfParameter(ParameterOperatingStructure paramOperatingStructure) {
	int parameterStatus;
	parameterStatus = checkIfParameterWithinUpperLimit(paramOperatingStructure, UPPER_LIMIT) &&
		checkIfParameterWithinLowerLimit(paramOperatingStructure, LOW_LIMIT);
        
	if(paramOperatingStructure.WarningCheck==1) {
		parameterStatus = parameterStatus && checkIfParameterWithinToleranceRange(paramOperatingStructure.ParameterValue, WITHIN_OPERATING_RANGE)
	}
	

	return parameterStatus;
}

void setupParameterOperatingStructure(ParameterOperatingStructure paramOperatingStructure, float parameterValue, float lowerLimit, float upperLimit,
				      float lowWarningLimit, float upperWarningLimit, const char* parameter, int warningCheck){
       paramOperatingStructure.ParameterValue = temperatureValue;
       paramOperatingStructure.LowerLimit = lowerLimit;
       paramOperatingStructure.UpperLimit = upperLimit;
       paramOperatingStructure.LowerWarningLimit = lowWarningLimit;
       paramOperatingStructure.UpperWarningLimit = upperWarningLimit;
       paramOperatingStructure.ParameterName = parameter;
       paramOperatingStructure.WarningCheck = warningCheck;
}

int checkBatteryCondition(float stateOfCharge, float temp, float chargeRate){
	setupParameterOperatingStructure(tempOperatingLimits, temp, LOW_THRESHOLD_BATT_TEMP, UPP_THRESHOLD_BATT_TEMP, 
					 LOW_TOLERANCE_BATT_TEMP, HIGH_TOLERANCE_BATT_TEMP, "Temperature" TEMP_WARNING_CHECK);
	int batteryStatus =  (checkStatusOfParameter(tempOperatingLimits));
	return batteryStatus;	
}
