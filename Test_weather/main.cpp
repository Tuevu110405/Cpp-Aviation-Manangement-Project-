#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/DataManagement.h"
#include "../include/PilotInspectionResult.h"
#include "../include/PilotStandard.h"
#include "../include/Pilot.h"
#include "../include/PilotCompetence.h"
#include "../include/PilotCertificate.h"
#include "../include/WeatherInspectionResult.h"
#include "../include/WeatherStandardVN.h"
#include "../include/Weather.h"
#include "../include/Flight.h"
#include "../include/DataLoader.h"
#include "../include/Plane.h"
#include "../include/CargoPlane.h"
#include "../include/PassengerPlane.h"
#include "../include/Date.h"
#include "../include/PlaneInspectionResult.h"
#include <string>
#include <iostream>
using namespace std;

int main(){
    Flight flight;
    Weather weather;
    weather.setVisibility(310);
    weather.setCrosswind(5);
    weather.setTemperature(-100);
    weather.setThunderstorm(0);
    weather.setTailwind(15);
    weather.setHorizontalVisibility(6000);
    flight.setWeather(weather);
    cout << "Weather data: " << flight.getWeather() << endl;
    
    WeatherStandardVN weatherStandardVN;
    cout << "Weather standard data: " << weatherStandardVN << endl;
    
    WeatherInspectionResult weatherInspectionResult ;
    cout << "current visibility: " << weather.getVisibility() << endl;
    cout << "standard visibility: " << weatherStandardVN.getVisibility() << endl;
    if(weather.getVisibility() < weatherStandardVN.getVisibility()){
        cout << "Visibility is not acceptable" << endl;
    }
    else{
        cout << "Visibility is acceptable" << endl;
    }

    if(weather.getHorizontalVisibility() < weatherStandardVN.getHorizontalVisibility()){
        cout << "Horizontal visibility is not acceptable" << endl;
    }
    else{
        cout << "Horizontal visibility is acceptable" << endl;
    }

    if(weather.getCrosswind() > weatherStandardVN.getCrosswind()){
        cout << "Crosswind is not acceptable" << endl;
    }
    else{
        cout << "Crosswind is acceptable" << endl;
    }

    if(weather.getTailwind() > weatherStandardVN.getTailwind()){
        cout << "Tailwind is not acceptable" << endl;
    }
    else{
        cout << "Tailwind is acceptable" << endl;
    }
    if(weather.getTemperature() < weatherStandardVN.getTemperatureLowerBound() || weather.getTemperature() > weatherStandardVN.getTemperatureUpperBound()){
        cout << "Temperature is not acceptable" << endl;
    }
    else{
        cout << "Temperature is acceptable" << endl;
    }
    if(weather.getThunderstorm() > weatherStandardVN.getThunderstorm()){
        cout << "Thunderstorm is not acceptable" << endl;
    }
    else{
        cout << "Thunderstorm is acceptable" << endl;
    }
    return 0;
    

}