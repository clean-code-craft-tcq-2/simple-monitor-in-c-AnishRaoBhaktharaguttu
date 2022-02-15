#define LOW_THRESHOLD_BATT_TEMP 0
#define UPP_THRESHOLD_BATT_TEMP 45
#define LOW_THRESHOLD_BATT_SOC 20
#define UPP_THRESHOLD_BATT_SOC 80
#define UPP_THRESHOLD_BATT_CHARGE_RATE 0.8
#define LOW_THRESHOLD_BATT_CHARGE_RATE 0.5

//Define the Parameter Operating Structure
typedef struct {
  float ParameterValue;
  float LowerLimit;
  float UpperLimit;
  float LowerWarningLimit;
  float UpperWarningLimit;
  int WarningCheck;
  const char* ParameterName;
} ParameterOperatingStructure;

//Tolerance levels
#define TOLERANCE_PERCENTAGE 0.05

//Warning checks enabled/disabled
#define TEMP_WARNING_CHECK 1

//Temperature tolerance
#define TOLERANCE_BATT_TEMP (TOLERANCE_PERCENTAGE * UPP_THRESHOLD_BATT_TEMP)
#define HIGH_TOLERANCE_BATT_TEMP (UPP_THRESHOLD_BATT_TEMP - TOLERANCE_BATT_TEMP)
#define LOW_TOLERANCE_BATT_TEMP (LOW_THRESHOLD_BATT_TEMP + TOLERANCE_BATT_TEMP)

extern int checkBatteryCondition(float stateOfCharge, float temp, float chargeRate);
void printStatusOnConsole(const char* statement);
