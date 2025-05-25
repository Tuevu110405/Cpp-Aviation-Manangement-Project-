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
#include "../include/StringManipulator.h"
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
void subprogram2(){
    string filepath;

    cout << "Enter the path to the flight data file: ";
    cin >> filepath;
    cout << "--- Loading data from file: " << filepath << " ---" << endl;

    //test fixed path
    // string filepath = "../data/flight_data.csv";
    bool loadOK = false;
    while(!loadOK){
    // Load flight data(try-catch for not being able to open file)
        try{
            DataLoader loader(filepath);
            cout << "Data loaded successfully." << endl;
            // Print the number of flights
            string key = "flightID";
            cout << "This data constains " << loader.getValueSize(key) << " flights." << endl;
            DataManagement::loadPilotStandard("pilot_standards.txt");
            WeatherStandardVN weatherStandard;
            //Using a loop to handle each flight
            for (int i = 0; i < loader.getValueSize(key); i++) {
                // Flight* flight = new Flight();
                string flightID = loader.getValue(key, i);
                // flight->setFlightID(flightID);
                string flightType = loader.getValue("flight_type", i);
                //processing flight type
                flightType = StringManipulator::lowerCase(flightType); // remove spaces
                flightType = StringManipulator::lowerCase(flightType); // Convert to lowercase 

                // if (flightType != "cargo" && flightType != "passenger") {
                //     cout << "Invalid flight type: " << flightType << endl;
                //     delete flight; // Free memory for the flight object
                //     continue; // Skip to the next iteration
                // }
                // flight->setFlightType(flightType);

                
                Weather* weather = new Weather();
                //Set weather data        
                weather->setVisibility(stof(loader.getValue("forward_visibility", i)));
                weather->setCrosswind(stof(loader.getValue("crosswind", i)));
                weather->setTailwind(stof(loader.getValue("tailwind", i)));            
                weather->setTemperature(stof(loader.getValue("temperature", i)));
                weather->setThunderstorm(stof(loader.getValue("thunderstorm", i)));
                weather->setHorizontalVisibility(stof(loader.getValue("horizontal_visibility", i)));
                // flight->setWeather(*weather);
                // delete weather;


                Pilot *pilot= new Pilot();
                //Set pilot data
                pilot->setName(loader.getValue("pilot_name", i));
                pilot->setPilotCompetence(PilotCompetence(stoi(loader.getValue("flight_hours", i)), stoi(loader.getValue("hours_in_command", i)),
                    stoi(loader.getValue("english_level", i)), stoi(loader.getValue("health_status", i))));
                Date expiryDate(loader.getValue("license_expiry_date", i));
                pilot->setPilotCertificate(PilotCertificate(loader.getValue("license_type", i), expiryDate));
                // flight->setPilot(*pilot);
                // delete pilot;

                
                // if(flightType == "cargo"){
                //     //Set cargoPlane data
                //     CargoPlane *plane = new CargoPlane();
                //     plane->setBaseInfo(stof(loader.getValue("fuel_consumption_rate", i)), stof(loader.getValue("speed_val", i)), 
                //         stof(loader.getValue("fuel_tank", i)), loader.getValue("model", i));
                //     plane->setPayload(stof(loader.getValue("capacity", i)));
                //     flight->setPlane(plane);
                    
                // }
                // else if(flightType == "passenger"){
                //     PassengerPlane *plane = new PassengerPlane();
                //     plane->setBaseInfo(stof(loader.getValue("fuel_consumption_rate", i)), stof(loader.getValue("speed_val", i)), 
                //         stof(loader.getValue("fuel_tank", i)), loader.getValue("model", i));
                //     plane->setSeatCapacity(stoi(loader.getValue("capacity", i)));
                //     plane->setNumOfPassenger(stoi(loader.getValue("passenger_number", i)));
                //     flight->setPlane(plane);
                    
                // }
                // else{
                //     cout << "Invalid flight type: " << flightType << endl;
                //     delete flight;
                //     continue; // Skip to the next iteration
                // }

                //New version of setting plane data
                // Get location.
                Location location;

                location.loadDestinationFromFile("../data/destinations.csv");

                // destination details.
                Destination departureLocationDetails;
                Destination arrivalLocationDetails;
                string departureCode;
                string arrivalCode;

                //Create a plane instance
                Plane *plane = nullptr;
                

                if(flightType == "cargo"){
                    plane = new CargoPlane(); // Create a CargoPlane
                    float current_fuel = stof(loader.getValue("fuel", i));
                    string model = loader.getValue("model", i);
                    int engine_status = stoi(loader.getValue("engine_status", i));
                    float payload = stof(loader.getValue("capacity", i));
                    cout << "Plane information: " << endl;
                    cout << "Current fuel: " << current_fuel << endl;
                    cout << "Model: " << model << endl;
                    cout << "Engine status: " << engine_status << endl;
                    cout << "Payload capacity: " << payload << endl;

                    
            
                    //Getting cargo plane details from laoder
                    plane->setCurrent_Fuel(current_fuel);
                    plane->setModel(model);
                    plane->setEngineStatus(engine_status);
                    plane->setPayload(payload);
                    plane->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");

                    
                }

                else if(flightType == "passenger"){
                    plane = new PassengerPlane(); // Create a PassengerPlane
                    
                    float current_fuel = stof(loader.getValue("fuel", i));
                    string model = loader.getValue("model", i);
                    int engine_status = stoi(loader.getValue("engine_status", i));
                    int  passengernum = stoi(loader.getValue("passenger_number", i));
                    cout << "Plane information: " << endl;
                    cout << "Current fuel: " << current_fuel << endl;
                    cout << "Model: " << model << endl;
                    cout << "Engine status: " << engine_status << endl;
                    cout << "Number of passengers: " << passengernum << endl;
            
                    plane->setCurrent_Fuel( current_fuel);
                    
                    plane->setModel(model);
                    plane->setEngineStatus(engine_status);
                    plane->setNumOfPassenger(passengernum);

                    plane->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");



                    
                }
                else{
                    cout << "Invalid flight type: " << flightType << endl;
                    // delete flight; // Free memory for the flight object
                    continue; // Skip to the next iteration
                }
                //load arrival and departure code
                departureCode = loader.getValue("departure_code", i);
                arrivalCode = loader.getValue("arrival_code", i);
                // initialize flight instance with parameters
                Flight *flight = new Flight(flightID, flightType, *pilot, *weather, plane);

                //set location for flight
                flight->setDepartureCode(departureCode);
                flight->setArrivalCode(arrivalCode);
                
                
                
        //         //Inspect pilot
        //         PilotStandard pilotStandard = DataManagement::findPilotStandard(plane->getModel());
        //         PilotInspectionResult pilotInspectionResult = FlightInspection::inspectPilot(flight->getPilot(), pilotStandard);
        //         flight->setPilotResult(pilotInspectionResult);
        //         //Inspect weather
        //         WeatherInspectionResult weatherInspectionResult = FlightInspection::inspectWeather(flight->getWeather(), weatherStandard);
        //         flight->setWeatherInspectionResult(weatherInspectionResult);
        //         //Inspect plane
        //         PlaneInspectionResult* planeInspectionResult = nullptr;
        //         if (plane && planeStandard) { 
        //             planeInspectionResult = FlightInspection::inspectPlane(*flight, planeStandard);
        // }       else {
        //             cerr << "Error: Plane or PlaneStandard is null. Skipping plane inspection." << endl;
        // }

        //         if (planeInspectionResult != nullptr) {
        //             flight->setPlaneInspectionResult(*planeInspectionResult);
        // }       else {
        //             cout << "Warning: Plane inspection failed or was skipped (result is nullptr)." << endl;
        // }
        //         //Store the flight in the relevant vector
        //         flight->updateFlightStatus();
        //         FlightManagement::addFlight(flight);
        //         cout << "Processing flight: " << flightID << " succesfully" << endl;

        
        // Taking pilot standard.
                PilotStandard pilotStandard;
                pilotStandard = DataManagement::findPilotStandard(plane->getModel());

                // Inspceting pilot
                PilotInspectionResult pilotResult;
                pilotResult = FlightInspection::inspectPilot(*pilot, pilotStandard);
                flight->setPilotResult(pilotResult);

                // Inspect weather.
                WeatherInspectionResult weatherResult;
                weatherResult = FlightInspection::inspectWeather(*weather, weatherStandard);
                flight->setWeatherInspectionResult(weatherResult);
                
                // Inspecting plane.
                if(flight->getFlightType() == "passenger"){
                    DataManagement::loadPassengerStandard("../data/Aircraft seat capacity.csv");
                    PlaneInspectionResult* planeResult = nullptr;
                    PassengerPlaneStandard passengerStandard;
                    PlaneStandard *planeStandard = nullptr;
                    passengerStandard = DataManagement::findPassengerStandard(plane->getModel()); 
                    planeStandard = &passengerStandard;
                    planeResult = FlightInspection::inspectPlane(*flight, planeStandard);
                    flight->setPlaneInspectionResult(*planeResult);
                }
                else if(flight->getFlightType() == "cargo"){
                    DataManagement::loadCargoStandard("../data/Aircraft payload.csv");
                    PlaneInspectionResult* planeResult = nullptr;
                    CargoPlaneStandard cargoStandard;
                    PlaneStandard *planeStandard = nullptr;
                    cargoStandard = DataManagement::findCargoStandard(plane->getModel()); 
                    planeStandard = &cargoStandard;
                    planeResult = FlightInspection::inspectPlane(*flight, planeStandard);
                    flight->setPlaneInspectionResult(*planeResult);
                }
                else{
                    cout << "Invalid flight type: " << flightType << endl;
                    delete flight; // Free memory for the flight object
                    continue; // Skip to the next iteration
                }

                flight->updateFlightStatus();
                delete weather; // Free memory for the weather object
                delete pilot; // Free memory for the pilot object
                FlightManagement::addFlight(flight); // Store the flight in the relevant vector
                cout << "Processing flight: " << flightID << " successfully." << endl;

                



            }
            loadOK = true; 
            
            //

        }
        catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
            cout << "Please check the file path and format." << endl;
            cout << "Enter the path to the flight data file again: ";
            cin >> filepath; 
            
        }
}
    cout << "---Data loaded and handled successfully---" << endl;
    // catch (const exception& e) {
    //     cout << "An unexpected error occurred: " << e.what() << endl;
        
    // }
    cout << "---Data is handled successfully---" << endl;
    // FlightManagement::writeEligibleFlights("eligible_flights.txt");
    // try{
    //     FlightManagement::writeEligibleFlights("eligible_flights.txt");
    //     FlightManagement::writeIneligibleFlights("ineligible_flights.txt");
    // }
    // catch(const exception& e){
    //     cout << "Error writing to file: " << e.what() << endl;
    //     return;
    // }

    // vector <Flight *> ineligibleList = FlightManagement::getIneligibleFlightList();
    // for (int count = 0; count < ineligibleList.size(); count++)
    // {
    //     cout << ineligibleList[count]->getPlaneInspectionResult()->getInspectionResult() << endl;
    // }
    FlightManagement::writeIneligibleFlights("ineligible_flights.txt");
    FlightManagement::writeSummary("summary.txt");

    //Options allowing user to adjust and validate the invalid flights
    
    // Free memory
    FlightManagement::deleteFlights();
    cout << "All data is written to file successfully." << endl;
    cout <<"---Program finished successfully---" << endl;
    




    
}




int main(){
    loadDataAndHandle(); 
    return 0;
    

}