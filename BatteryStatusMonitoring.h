#define LOW_THRESHOLD_BATT_TEMP 0
#define UPP_THRESHOLD_BATT_TEMP 45
#define LOW_THRESHOLD_BATT_SOC 20
#define UPP_THRESHOLD_BATT_SOC 80
#define UPP_THRESHOLD_BATT_CHARGE_RATE 0.8

const char *ALERT_WARN_MSG = "Out of sepcified range";

extern int checkBatteryTemperature(float temp);
extern int checkBatteryStateOfCharge(float stateOfCharge);
extern int checkBatteryChargeRate(float chargeRate);
extern int checkBatteryCondition(float stateOfCharge, float temperature, float chargeRate);
extern int printWarningMessage (char*);
