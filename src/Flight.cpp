#include "../include/Flight.h"
#include "../include/Weather.h"
#include "../include/WeatherStandard.h"
using namespace std;

Flight::Flight() : weather(0, 0, 0, 0,0,0), weatherInspectionResult(false, false, false,false, false, false) {
    // Constructor initialization

}
//Getters
WeatherInspectionResult& Flight::getWeatherInspectionResult() {
    return this->weatherInspectionResult;
}
Weather& Flight::getWeather()  {
    return this->weather;
}
//Setters
void Flight::setWeatherInspectionResult(const WeatherInspectionResult& weatherInspectionResult) {
    this->weatherInspectionResult = weatherInspectionResult;
}
void Flight::setWeather(const Weather& weather){
    this->weather = weather;
}