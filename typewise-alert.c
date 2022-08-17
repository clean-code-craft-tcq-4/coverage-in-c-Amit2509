#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0;
  switch(coolingType) {
    case PASSIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 35;
      break;
    case HI_ACTIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 45;
      break;
    default:
      lowerLimit = 0;
      upperLimit = 40;
      break;
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

int checkAndAlert( AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  int AlertSent = 0;
  BreachType breachType = classifyTemperatureBreach( batteryChar.coolingType, temperatureInC);

  switch(alertTarget) {
    case TO_CONTROLLER:
      AlertSent = sendToController(breachType);
      break;
    case TO_EMAIL:
      AlertSent = sendToEmail(breachType);
      break;
  }
  
  return result;
}

int sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return 1;
}

int sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  int alertSent = 0;
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      alertSent = 1;
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      alertSent = 1;
      break;
    default:
      break;
  }
  return alertSent;
}
