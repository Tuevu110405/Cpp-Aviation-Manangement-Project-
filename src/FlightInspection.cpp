#include "../include/FlightInspection.h"
#include "../include/WeatherStandardVN.h" 
#include "../include/WeatherStandard.h"
#include "../include/Flight.h"
#include "../include/Weather.h"
#include <bits/stdc++.h>
using namespace std;


/* 
FlightInspection::FlightInspection(const Flight& flight, const WeatherStandardVN& weatherStandard) {
    this->flight = flight;
    this->weatherStandard = weatherStandard;
}

Flight& FlightInspection::getFlight() {
    return this->flight;
}

WeatherStandardVN& FlightInspection::getWeatherStandard() { 
    return this->weatherStandard;
}

void FlightInspection::setFlight(const Flight& flight) {
    this->flight = flight;
}

void FlightInspection::setWeatherStandard(const WeatherStandardVN& weatherStandard) { 
    this->weatherStandard = weatherStandard;
}

// bool FlightInspection::inspectWeather(){
//     // Check if the weather is satisfactory each quality
//     if(flight.getWeather().getVisibility() < weatherStandard.getVisibility()){
//         flight.getWeatherInspectionResult().setIsVisibility(false);
//     }
//     if(flight.getWeather().getCrosswind() > weatherStandard.getCrosswind()){
//         flight.getWeatherInspectionResult().setIsCrosswind(false);
//     }
//     if(flight.getWeather().getTemperature() < weatherStandard.getTemperatureLowerBound() || flight.getWeather().getTemperature() > weatherStandard.getTemperatureUpperBound()){
//         flight.getWeatherInspectionResult().setIsTemperature(false);
//     }
//     if(flight.getWeather().getThunderstorm() > weatherStandard.getThunderstorm()){
//         flight.getWeatherInspectionResult().setIsThunderstorm(false);
//     }
//     if(flight.getWeather().getTailwind() > weatherStandard.getTailwind()){
//         flight.getWeatherInspectionResult().setIsTailwind(false);
//     }
//     if(flight.getWeather().getHorizontalVisibility() < weatherStandard.getHorizontalVisibility()){
//         flight.getWeatherInspectionResult().setIsHorizontalVisibility(false);
//     }
//     return weatherStandard.isWeatherAcceptable(flight.getWeather());
// }

void FlightInspection::inspectWeather() {
    // Kiểm tra từng điều kiện thời tiết
    if (flight.getWeather().getVisibility() >= weatherStandard.getVisibility()) {
        flight.getWeatherInspectionResult().setIsVisibility(true);
    } else {
        flight.getWeatherInspectionResult().setIsVisibility(false);
    }

    if (flight.getWeather().getCrosswind() <= weatherStandard.getCrosswind()) {
        flight.getWeatherInspectionResult().setIsCrosswind(true);
    } else {
        flight.getWeatherInspectionResult().setIsCrosswind(false);
    }

    if (flight.getWeather().getTemperature() >= weatherStandard.getTemperatureLowerBound() &&
        flight.getWeather().getTemperature() <= weatherStandard.getTemperatureUpperBound()) {
        flight.getWeatherInspectionResult().setIsTemperature(true);
    } else {
        flight.getWeatherInspectionResult().setIsTemperature(false);
    }

    if (flight.getWeather().getThunderstorm() <= weatherStandard.getThunderstorm()) {
        flight.getWeatherInspectionResult().setIsThunderstorm(true);
    } else {
        flight.getWeatherInspectionResult().setIsThunderstorm(false);
    }

    if (flight.getWeather().getTailwind() <= weatherStandard.getTailwind()) {
        flight.getWeatherInspectionResult().setIsTailwind(true);
    } else {
        flight.getWeatherInspectionResult().setIsTailwind(false);
    }

    if (flight.getWeather().getHorizontalVisibility() >= weatherStandard.getHorizontalVisibility()) {
        flight.getWeatherInspectionResult().setIsHorizontalVisibility(true);
    } else {
        flight.getWeatherInspectionResult().setIsHorizontalVisibility(false);
    }

    // Trả về kết quả tổng quát
    if(weatherStandard.isWeatherAcceptable(flight.getWeather())){
        flight.getWeatherInspectionResult().setIsWeather(true);
    } else {
        flight.getWeatherInspectionResult().setIsWeather(false);
    }
}


*/
WeatherInspectionResult& FlightInspection::inspectWeather(Flight& flight, WeatherStandardVN& weatherStandard) {
    WeatherInspectionResult& weatherInspectionResult = flight.getWeatherInspectionResult();
    // Check if the weather is satisfactory, if not, check and set status for each quality
    if(weatherStandard.isWeatherAcceptable(flight.getWeather())){
        weatherInspectionResult.setIsCrosswind(true);
        weatherInspectionResult.setIsTemperature(true);
        weatherInspectionResult.setIsThunderstorm(true);
        weatherInspectionResult.setIsTailwind(true);
        weatherInspectionResult.setIsHorizontalVisibility(true);
        weatherInspectionResult.setIsVisibility(true);
        weatherInspectionResult.setInspectionResult(true);
    }
    else{

        if(flight.getWeather().getVisibility() < weatherStandard.getVisibility()){
            weatherInspectionResult.setIsVisibility(false);
        }
        else{
            weatherInspectionResult.setIsVisibility(true);
        }

        if(flight.getWeather().getCrosswind() > weatherStandard.getCrosswind()){
            weatherInspectionResult.setIsCrosswind(false);
        }
        else{
            weatherInspectionResult.setIsCrosswind(true);
        }

        if(flight.getWeather().getTemperature() < weatherStandard.getTemperatureLowerBound() || flight.getWeather().getTemperature() > weatherStandard.getTemperatureUpperBound()){
            weatherInspectionResult.setIsTemperature(false);
        }
        else{
            weatherInspectionResult.setIsTemperature(true);
        }

        if(flight.getWeather().getThunderstorm() > weatherStandard.getThunderstorm()){
            weatherInspectionResult.setIsThunderstorm(false);
        }
        else{
            weatherInspectionResult.setIsThunderstorm(true);
        }

        if(flight.getWeather().getTailwind() > weatherStandard.getTailwind()){
            weatherInspectionResult.setIsTailwind(false);
        }
        else{
            weatherInspectionResult.setIsTailwind(true);
        }

        if(flight.getWeather().getHorizontalVisibility() < weatherStandard.getHorizontalVisibility()){
            weatherInspectionResult.setIsHorizontalVisibility(false);
        }
        else{
            weatherInspectionResult.setIsHorizontalVisibility(true);
        }
    }

    

    return weatherInspectionResult;

}
