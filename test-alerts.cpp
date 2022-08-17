#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("classify the breach according to type of cooling and temperature") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 42) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 42) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 42) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -3) == TOO_LOW);
   
}

TEST_CASE("testing alert send to controller") {
  REQUIRE(sendToController(TOO_LOW) == 1);
  REQUIRE(sendToController(TOO_HIGH) == 1);
  REQUIRE(sendToController(NORMAL) == 1);
}

TEST_CASE("testing alert send to email") {
  REQUIRE(sendToEmail(TOO_LOW) == 1);
  REQUIRE(sendToEmail(TOO_HIGH) == 1);
  REQUIRE(sendToEmail(NORMAL) == 0);
}

TEST_CASE("testing check and alert") {
  BatteryCharacter batteryChar;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChar, 38) == 1);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 38) == 0);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChar, 41) == 1);

} 
