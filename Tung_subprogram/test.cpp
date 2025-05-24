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
#include "../include/CargoPlaneInspectionResult.h"
#include "../include/PassengerPlaneInspectionResult.h"  
#include "../include/PlaneStandard.h"
#include "../include/CargoPlaneStandard.h"
#include "../include/PassengerPlaneStandard.h"
#include "../include/Location.h"
#include <string>
#include <iostream>


void mixedDataHandle(){
    Pilot pilot;                            // A Pilot object with default values.
    Weather actualWeather;                  // A Weather object with default values.
    WeatherStandardVN weatherStandardVN;    // A WeatherStandard object with default values.
    Plane *plane;                        // A pointer to a Plane object.
    
    Flight *flight = new Flight();          // A pointer to a Flight object.
    string flightID;
    string flightType;                      // The type of the flight.
    string departure_airport;
    string arrival_airport;                        // The string of flight ID.

    PilotInspectionResult pilotResult;
    WeatherInspectionResult weatherResult;
    PlaneInspectionResult* planeInspectionResult; // A pointer to a PlaneInspectionResult object.   
    
    cout <<"You'll need to enter the information of the plane and load data from file for weather and pilot:\n";

    cout << "Please enter the filght information fist!\n";

    // cout << "\nEnter the data for a flight.\n";
    //                 // Prompt user for flightID.
    //     while (true)
    //     {
    //         try
    //         {
    //             cout << "Enter the flight ID: ";
    //             getline(cin, flightID);
    //             flight->setFlightID(flightID);
    //             break;
    //         }
    //         catch (Flight::InvalidID id)
    //         {
    //             cout << "ERROR: The ID " << id.getID()
    //                 << " is invalid for a Vietnam Airline flight.";
    //             cout << "\nEnter again.\n";
    //         }
    //     }
    // while(true){
    //     try
    //     {
    //     cout <<"\nEnter flight type (cargo/passenger): ";
    //     cin >> flightType;
    //     }
    //     catch ()
    // }




        flight->setFlightType(flightType);


        cout << "Enter the departure airport code: ";
        cin >> departure_airport;
        cout << "Enter the arrival airport code: ";
        cin >> arrival_airport;
        flight->setDepartureCode(departure_airport);
        flight->setArrivalCode(arrival_airport);

}