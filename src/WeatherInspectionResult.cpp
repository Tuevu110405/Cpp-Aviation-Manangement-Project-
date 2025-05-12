#include "../include/WeatherInspectionResult.h"
using namespace std;

WeatherInspectionResult::WeatherInspectionResult() : isVisibility(true), isCrosswind(true), isTemperature(true), isThunderstorm(true) {}
WeatherInspectionResult::WeatherInspectionResult(bool isVisibility,bool isHorizontalVisibility, bool isCrosswind, bool isTailwind, bool isTemperature, bool isThunderstorm) : isVisibility(isVisibility),isHorizontalVisibility(isHorizontalVisibility), isCrosswind(isCrosswind),isTailwind(isTailwind), isTemperature(isTemperature), isThunderstorm(isThunderstorm) {}

//Getters
bool WeatherInspectionResult::getIsVisibility() const {
    return isVisibility;
}
bool WeatherInspectionResult::getIsCrosswind() const {
    return isCrosswind;
}
bool WeatherInspectionResult::getIsTemperature() const {
    return isTemperature;
}
bool WeatherInspectionResult::getIsThunderstorm() const {
    return isThunderstorm;
}
bool WeatherInspectionResult::getIsTailwind() const {
    return isTailwind;
}
bool WeatherInspectionResult::getIsHorizontalVisibility() const {
    return isHorizontalVisibility;
}
bool WeatherInspectionResult::getInspectionResult() const {
    return inspectionResult;
}

//Setters
void WeatherInspectionResult::setIsVisibility(bool isVisibility) {
    this->isVisibility = isVisibility;
}
void WeatherInspectionResult::setIsCrosswind(bool isCrosswind) {
    this->isCrosswind = isCrosswind;
}
void WeatherInspectionResult::setIsTemperature(bool isTemperature) {
    this->isTemperature = isTemperature;
}
void WeatherInspectionResult::setIsThunderstorm(bool isThunderstorm) {
    this->isThunderstorm = isThunderstorm;
}
void WeatherInspectionResult::setIsTailwind(bool isTailwind) {
    this->isTailwind = isTailwind;
}
void WeatherInspectionResult::setIsHorizontalVisibility(bool isHorizontalVisibility) {
    this->isHorizontalVisibility = isHorizontalVisibility;
}
void WeatherInspectionResult::setInspectionResult(bool inspectionResult) {
    this->inspectionResult = inspectionResult;
    
}

