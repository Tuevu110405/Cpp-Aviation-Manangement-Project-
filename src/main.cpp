#include "../include/Weather.h"
#include "../include/WeatherStandard.h"
#include "../include/Flight.h"
#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/WeatherInspectionResult.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    Weather weather;
    weather.setVisibility(300.0);
    weather.setCrosswind(10.0);
    weather.setTemperature(25.0);
    weather.setThunderstorm(1.0);
    weather.setTailwind(9);
    weather.setHorizontalVisibility(6000.0);

    cout << "Weather: " << weather << endl;

    // Using WeatherStandardVN
    WeatherStandardVN weatherStandardVN;
    cout << "Weather Standard: " << weatherStandardVN << endl;

    Flight flight;
    flight.setWeather(weather);
    WeatherInspectionResult weatherInspectionResult= FlightInspection::inspectWeather(flight, weatherStandardVN);
    flight.setWeatherInspectionResult(weatherInspectionResult);
    flight.getWeather().setVisibility(300.0);

    // Print the inspection results
    cout << "Weather Inspection Result: " << endl;
    cout << "Visibility: " << (flight.getWeatherInspectionResult().getIsVisibility() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Crosswind: " << (flight.getWeatherInspectionResult().getIsCrosswind() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Temperature: " << (flight.getWeatherInspectionResult().getIsTemperature() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Thunderstorm: " << (flight.getWeatherInspectionResult().getIsThunderstorm() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Tailwind: " << (flight.getWeatherInspectionResult().getIsTailwind() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Horizontal Visibility: " << (flight.getWeatherInspectionResult().getIsHorizontalVisibility() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Overall Inspection Result: " << (flight.getWeatherInspectionResult().getInspectionResult() ? "Acceptable" : "Not Acceptable") << endl;
    
    return 0;

}









    // if (flight.getWeatherInspectionResult().getIsVisibility()) {
    //     cout << "Visibility is acceptable for flight." << endl;
    // } else {
    //     cout << "Visibility is not acceptable for flight." << endl;
    // }
    // if (flight.getWeatherInspectionResult().getIsCrosswind()) {
    //     cout << "Crosswind is acceptable for flight." << endl;
    // } else {
    //     cout << "Crosswind is not acceptable for flight." << endl;
    // }
    // if (flight.getWeatherInspectionResult().getIsTemperature()) {
    //     cout << "Temperature is acceptable for flight." << endl;
    // } else {
    //     cout << "Temperature is not acceptable for flight." << endl;
    // }
    // if (flight.getWeatherInspectionResult().getIsThunderstorm()) {
    //     cout << "Thunderstorm is acceptable for flight." << endl;
    // } else {
    //     cout << "Thunderstorm is not acceptable for flight." << endl;
    // }
    // if (flight.getWeatherInspectionResult().getIsTailwind()) {
    //     cout << "Tailwind is acceptable for flight." << endl;
    // } else {
    //     cout << "Tailwind is not acceptable for flight." << endl;
    // }
    // if (flight.getWeatherInspectionResult().getIsHorizontalVisibility()) {
    //     cout << "Horizontal visibility is acceptable for flight." << endl;
    // } else {
    //     cout << "Horizontal visibility is not acceptable for flight." << endl;
    // }

    // if (flight.getWeatherInspectionResult().getInspectionResult()) {
    //     cout << "Overall inspection result: Weather is acceptable for flight." << endl;
    // } else {
    //     cout << "Overall inspection result: Weather is not acceptable for flight." << endl;
    // }
    // return 0;

    

