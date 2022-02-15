#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "BatteryStatusMonitoring.h"

enum chosenLanguage language = English;

// Enum which contains the various operational states of the parameter
enum StatusOfParameter {WITHIN_OPERATING_RANGE = 0,
			  LOW_LIMIT = 1,
			  UPPER_LIMIT = 2,
			  LOW_WARNING_LIMIT = 3,
			  UPPER_WARNING_LIMIT = 4
			  };

//Warning messages for both breach and tolerance limits
const char* warningMessagesEnglish[] = {"Battery condition normal and within operating range",
				 "Battery at Risk: Lower limit exceeded for ",
				 "Battery at Risk: Upper limit exceeded for ",
				 "Battery abnormal: Approaching the lower warning limit for ",
				 "Battery abnormal: Approaching the upper warning limit for "
				 };

const char* warningMessagesGerman[] = {"Batteriezustand normal und innerhalb des Betriebsbereichs",
				 "Battery at Risk: Untergrenze überschritten für ",
				 "Battery at Risk: Obergrenze überschritten für ",
				 "Batterie abnormal: Annäherung an die untere Warngrenze für ",
				 "Batterie abnormal: Annäherung an die obere Warngrenze für "
				 };

//Structures to hold information regarding the parameters - Temp, SoC, ChargeRate
ParameterOperatingStructure tempOperatingLimits;
ParameterOperatingStructure socOperatingLimits;
ParameterOperatingStructure chargeRateOperatingLimits;

void printStatusOnConsole(const char* statement) {
	printf("%s \n", statement);
}

void setWarningMessage(const char* parameter, int statusOfParameter, char* warnMsg) {
       if(German){
	strcpy(warnMsg, warningMessagesEnglish[statusOfParameter]);
       } else{
	strcpy(warnMsg, warningMessagesGerman[statusOfParameter]);
       }
	strcat(warnMsg,  parameter);
}

int warnBatteryCondition(const char* parameter, int statusOfParameter) {
	char warnMsg[100];
	setWarningMessage(parameter, statusOfParameter, warnMsg);	
	printStatusOnConsole(warnMsg);
	return 0;
}

int checkIfParameterWithinSpecifiedRange(float value, float lowerLimit, float upperLimit){
      return value > lowerLimit && value < upperLimit;
}

int checkIfParameterWithinLowerLimit(ParameterOperatingStructure paramOperatingStructure, int statusOfParameterInCheck) {
	if (paramOperatingStructure.ParameterValue  > paramOperatingStructure.LowerLimit) {
		return warnBatteryCondition(paramOperatingStructure.ParameterName, statusOfParameterInCheck);
	}
	return 1;
}

int checkIfParameterWithinUpperLimit(ParameterOperatingStructure paramOperatingStructure, int statusOfParameterInCheck) {
	if (paramOperatingStructure.ParameterValue  > paramOperatingStructure.UpperLimit) {
		return warnBatteryCondition(paramOperatingStructure.ParameterName, statusOfParameterInCheck);
	}
	return 1;
}

//This function checks if the parameter value are in the warning zones (Both lower and upper)
int checkIfParameterInWarningZone(ParameterOperatingStructure parameterOperatingStructure){
	if(checkIfParameterWithinSpecifiedRange(parameterOperatingStructure.ParameterValue, parameterOperatingStructure.LowerLimit,
						parameterOperatingStructure.LowerWarningLimit)){
	       return warnBatteryCondition(parameterOperatingStructure.ParameterName, LOW_WARNING_LIMIT);
	 } else if(checkIfParameterWithinSpecifiedRange(parameterOperatingStructure.ParameterValue, parameterOperatingStructure.UpperWarningLimit,
							parameterOperatingStructure.UpperLimit)){
	       return warnBatteryCondition(parameterOperatingStructure.ParameterName, UPPER_WARNING_LIMIT);
	 }
	return 1;
}

//This function includes check for the tolerance range. If battery is within this range then its normal. Else check if the tolerance has exceeded
//in the upper or lower region.
int checkIfParameterWithinToleranceRange(ParameterOperatingStructure parameterOperatingStructure, int statusOfParameterInCheck) {
	if (parameterOperatingStructure.ParameterValue > parameterOperatingStructure.LowerWarningLimit 
	    && parameterOperatingStructure.ParameterValue < parameterOperatingStructure.UpperWarningLimit){
	         return !(warnBatteryCondition(parameterOperatingStructure.ParameterName, statusOfParameterInCheck));
	}else {
	         return checkIfParameterInWarningZone(parameterOperatingStructure);
	}
}

// This function triggers the check for tolerance only if the warning check flag is enabled for the corresponding parameter - Enable tunability
int checkForWarning(ParameterOperatingStructure paramOperatingStructure){
	int parameterStatus = 1;
	if(paramOperatingStructure.WarningCheck==1) {
		parameterStatus = checkIfParameterWithinToleranceRange(paramOperatingStructure, WITHIN_OPERATING_RANGE);
	}
	return parameterStatus;
}

//Check the battery status - Includes lower breach, high breach and tolerance warning check
int checkStatusOfParameter(ParameterOperatingStructure paramOperatingStructure) {
	return checkIfParameterWithinUpperLimit(paramOperatingStructure, UPPER_LIMIT) &&
		checkIfParameterWithinLowerLimit(paramOperatingStructure, LOW_LIMIT) &&
		checkForWarning(paramOperatingStructure);
}

//Sets up the structure for the corresponding parameter with all necessary attributes
void setupParameterOperatingStructure(ParameterOperatingStructure paramOperatingStructure, float parameterValue, float lowerLimit, float upperLimit,
				      float lowWarningLimit, float upperWarningLimit, const char* parameter, int warningCheck){
       paramOperatingStructure.ParameterValue = parameterValue;
       paramOperatingStructure.LowerLimit = lowerLimit;
       paramOperatingStructure.UpperLimit = upperLimit;
       paramOperatingStructure.LowerWarningLimit = lowWarningLimit;
       paramOperatingStructure.UpperWarningLimit = upperWarningLimit;
       paramOperatingStructure.ParameterName = parameter;
       paramOperatingStructure.WarningCheck = warningCheck;
}

//Checks the overall battery condition
int checkBatteryCondition(float stateOfCharge, float temp, float chargeRate){
	setupParameterOperatingStructure(tempOperatingLimits, temp, LOW_THRESHOLD_BATT_TEMP, UPP_THRESHOLD_BATT_TEMP, 
					 LOW_TOLERANCE_BATT_TEMP, HIGH_TOLERANCE_BATT_TEMP, "Temperature", TEMP_WARNING_CHECK);
	setupParameterOperatingStructure(socOperatingLimits, stateOfCharge, LOW_THRESHOLD_BATT_SOC , UPP_THRESHOLD_BATT_SOC , 
					 LOW_TOLERANCE_BATT_SOC, HIGH_TOLERANCE_BATT_SOC, "State of Charge", SOC_WARNING_CHECK);
	setupParameterOperatingStructure(chargeRateOperatingLimits, chargeRate, LOW_THRESHOLD_BATT_CHARGE_RATE, UPP_THRESHOLD_BATT_CHARGE_RATE, 
					 LOW_TOLERANCE_BATT_CHARGE_RATE, HIGH_TOLERANCE_BATT_CHARGE_RATE, "Charge Rate", CHARGE_RATE_WARNING_CHECK);
	int batteryStatus =  (checkStatusOfParameter(tempOperatingLimits) && checkStatusOfParameter(socOperatingLimits) && checkStatusOfParameter(chargeRateOperatingLimits));
	return batteryStatus;	
}
