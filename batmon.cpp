/*
  Battery Monitoring

 Monitors battery LiPo state / level.

 created 19 april 2025
 by gcuadrado
 */
#include <BQ24195.h>
#include "batmon.h"

#define ADC_NB_BITS    (12U)

typedef struct {
  float rawADC;
  float voltADC;
  float voltBat;
} batt_data_t;

int R1 =  330000;
int R2 = 1000000;
int maxVoltage;

const float batteryEmptyVoltage = 3.5;
const float batteryFullVoltage  = 4.2;
const float batteryCapacity     = 0.75;

batt_data_t battData;

// Static function prototypes
static void configurePMIC(void);

// PUBLIC FUNCTIONS
/**
 * @brief Initialize Battery Monitoring
 */
void batmon_init(void)
{
  battData = {.rawADC = 0, .voltADC = 0, .voltBat = 0};

  analogReference(AR_DEFAULT);
  analogReadResolution(ADC_NB_BITS);

  configurePMIC();
}

/**
 * @brief Battery state getter
 * @return int Battery level in percentage
 */
int batmon_getBattData(void)
{
  battData.rawADC = analogRead(ADC_BATTERY);
  battData.voltADC = battData.rawADC * (3.3 / 4095.0);
  battData.voltBat = battData.voltADC * (maxVoltage / 3.3);

  return (battData.voltBat - batteryEmptyVoltage) * 100 / (batteryFullVoltage - batteryEmptyVoltage);  // Battery level in percentage
}

// PRIVATE FUNCTIONS
/**
 * @brief Configure PMIC
 */
static void configurePMIC(void)
{
  PMIC.begin();
  PMIC.enableBoostMode();
  PMIC.setMinimumSystemVoltage(batteryEmptyVoltage);
  PMIC.setChargeVoltage(batteryFullVoltage);
  PMIC.setChargeCurrent(batteryCapacity / 2);
  PMIC.enableCharge();

  maxVoltage = (3.3 * (R1 + R2)) / R2;
}
