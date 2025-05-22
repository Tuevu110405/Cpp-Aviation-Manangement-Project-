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
/*
flightID,VN310,VN150
flight_type,cargo,passenger
forward_visibility,310,275
horizontal_visibility,6000,5550
crosswind,5,20
tailwind,5,30
temperature,30,3
thunderstorm,3,0
pilot_name,Jonh,Tung
flight_hours,5000,3500
hours_in_command,2000,1500
license_type,ATPL,ATPL
license_expiry_date,12/31/2027,12/31/2028
english_level,4,4
health_status,2,2
fuel_tank,101300,113000
fuel_consumption_rate,5400,5800
speed_val,903,903
model,boeing787,airbusa350
capacity,300,100
passenger_number,0,3

*/



//Function for program of loading data and handle data
void loadDataAndHandle(){
    string filepath;

    // cout << "Enter the path to the flight data file: ";
    // cin >> filepath;
    // cout << "--- Loading data from file: " << filepath << " ---" << endl;

    //test fixed path
    filepath = "../data/data.csv";
    // Load flight data(try-catch for not being able to open file)
    try{
        DataLoader loader(filepath);
        cout << "Data loaded successfully." << endl;
        // Print the number of flights
        string key = "flightID";
        cout << "This data constains " << loader.getValueSize(key) << " flights." << endl;
        DataManagement::loadPilotStandard("pilot_standards.txt");
        //Using a loop to handle each flight
        for (int i = 0; i < loader.getValueSize(key); i++) {
            Flight* flight = new Flight();
            string flightID = loader.getValue(key, i);
            flight->setFlightID(flightID);
            string flightType = loader.getValue("flight_type", i);
            flight->setFlightType(flightType);


            Weather* weather = new Weather();
            //Set weather data
            weather->setVisibility(stof(loader.getValue("forward_visibility", i)));
            weather->setCrosswind(stof(loader.getValue("crosswind", i)));
            weather->setTailwind(stof(loader.getValue("tailwind", i)));
            weather->setTemperature(stof(loader.getValue("temperature", i)));
            weather->setThunderstorm(stof(loader.getValue("thunderstorm", i)));
            weather->setHorizontalVisibility(stof(loader.getValue("horizontal_visibility", i)));
            flight->setWeather(*weather);
            delete weather;


            Pilot *pilot= new Pilot();
            //Set pilot data
            pilot->setName(loader.getValue("pilot_name", i));
            pilot->setPilotCompetence(PilotCompetence(stoi(loader.getValue("flight_hours", i)), stoi(loader.getValue("hours_in_command", i)),
                stoi(loader.getValue("english_level", i)), stoi(loader.getValue("health_status", i))));
            Date expiryDate(loader.getValue("license_expiry_date", i));
            pilot->setPilotCertificate(PilotCertificate(loader.getValue("license_type", i), expiryDate));
            flight->setPilot(*pilot);
            delete pilot;


            if(flightType == "cargo"){
                //Set cargoPlane data
                CargoPlane *plane = new CargoPlane();
                plane->setBaseInfo(stof(loader.getValue("fuel_consumption_rate", i)), stof(loader.getValue("speed_val", i)), 
                    stof(loader.getValue("fuel_tank", i)), loader.getValue("model", i));
                plane->setPayload(stof(loader.getValue("capacity", i)));
                flight->setPlane(plane);
                
            }
            else if(flightType == "passenger"){
                PassengerPlane *plane = new PassengerPlane();
                plane->setBaseInfo(stof(loader.getValue("fuel_consumption_rate", i)), stof(loader.getValue("speed_val", i)), 
                    stof(loader.getValue("fuel_tank", i)), loader.getValue("model", i));
                plane->setSeatCapacity(stoi(loader.getValue("capacity", i)));
                plane->setNumOfPassenger(stoi(loader.getValue("passenger_number", i)));
                flight->setPlane(plane);
                
            }
            else{
                cout << "Invalid flight type: " << flightType << endl;
                delete flight;
                continue; // Skip to the next iteration
            }



            // flight inspection
            WeatherStandardVN weatherStandard;
            //load the pilot standard
            
            PilotStandard pilotStandard = DataManagement::findPilotStandard(flight->getPlane()->getModel());
            PilotInspectionResult pilotInspectionResult = FlightInspection::inspectPilot(flight->getPilot(), pilotStandard);
            flight->setPilotResult(pilotInspectionResult);
            WeatherInspectionResult weatherInspectionResult = FlightInspection::inspectWeather(*flight, weatherStandard);
            flight->setWeatherInspectionResult(weatherInspectionResult);
            flight->setPlaneInspectionResult(PlaneInspectionResult());
            //Store the flight in the relevant vector
            FlightManagement::addFlight(flight);
            cout << "Processing flight: " << flightID << " succesfully" << endl;




        }
        
        //

    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
        cout << "Please check the file path and format." << endl;
        return;
        
    }
    // catch (const exception& e) {
    //     cout << "An unexpected error occurred: " << e.what() << endl;
        
    // }
    cout << "---Data is handled successfully---" << endl;
    FlightManagement::writeEligibleFlights("eligible_flights.txt");
    FlightManagement::writeIneligibleFlights("ineligible_flights.txt");
    FlightManagement::writeSummary("summary.txt");
    
    // Free memory
    FlightManagement::deleteFlights();
    cout << "All data is written to file successfully." << endl;
    cout <<"---Program finished successfully---" << endl;
    




    
}




int main(){
    loadDataAndHandle(); 
    return 0;
    

}