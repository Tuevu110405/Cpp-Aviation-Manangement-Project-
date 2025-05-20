#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 
#include "../include/Location.h" // Assuming Location.h is in the same directory or include path

using namespace std; // Added this line

int main() {
    Location locManager;
    string filename = "airports.csv";

    // 1. Load destinations from file
    locManager.loadDestinationFromFile(filename);
    cout << "Loaded destinations from " << filename << endl;

    // 2. Get and display all loaded destinations
    const vector<Destination>& allDestinations = locManager.getDestinations();
    if (allDestinations.empty()) {
        cerr << "No destinations were loaded. Please check airports.csv." << endl;
        return 1;
    }

    cout << "\n--- All Loaded Airports ---" << endl;
    for (const auto& dest : allDestinations) {
        cout << "City: " << dest.city
                  << ", Code: " << dest.airport_code
                  << ", Lat: " << dest.latitude
                  << ", Lon: " << dest.longitude << endl;
    }

    // 3. Get a specific destination by code
    cout << "\n--- Search for Specific Airports ---" << endl;
    string codesToTest[] = {"JFK", "HND", "NONEXISTENT"};
    for (const string& code : codesToTest) {
        Destination foundDest;
        if (locManager.getDestinationByCode(code, foundDest)) {
            cout << "Found airport with code " << code << ":" << endl;
            cout << "  City: " << foundDest.city
                      << ", Lat: " << foundDest.latitude
                      << ", Lon: " << foundDest.longitude << endl;
        } else {
            cout << "Airport with code " << code << " not found." << endl;
        }
    }

    // 4. Calculate distance between two airports & 5. Convert to Nautical Miles
    cout << "\n--- Distance Calculations ---" << endl;
    Destination lhr, jfk, hnd, lax, cdg;
    bool lhr_found = locManager.getDestinationByCode("LHR", lhr);
    bool jfk_found = locManager.getDestinationByCode("JFK", jfk);
    bool hnd_found = locManager.getDestinationByCode("HND", hnd);
    bool lax_found = locManager.getDestinationByCode("LAX", lax);
    bool cdg_found = locManager.getDestinationByCode("CDG", cdg);

    cout << fixed << setprecision(2); // Set output for floating points

    if (lhr_found && jfk_found) {
        double distLHR_JFK_km = locManager.calculateDistanceInKM(lhr.latitude, lhr.longitude, jfk.latitude, jfk.longitude);
        double distLHR_JFK_nm = locManager.distanceInNM(distLHR_JFK_km);
        cout << "Distance LHR (" << lhr.city << ") to JFK (" << jfk.city << "): "
                  << distLHR_JFK_km << " km (" << distLHR_JFK_nm << " NM)" << endl;

        // 6. Test isOceanicFlight
        bool isLHR_JFK_Oceanic = locManager.isOceanicFlight(lhr.latitude, lhr.longitude, jfk.latitude, jfk.longitude);
        cout << "  Is LHR to JFK oceanic? " << (isLHR_JFK_Oceanic ? "Yes" : "No") << endl;
    } else {
        cerr << "Could not find LHR or JFK for distance calculation." << endl;
    }

    if (hnd_found && lax_found) {
        double distHND_LAX_km = locManager.calculateDistanceInKM(hnd.latitude, hnd.longitude, lax.latitude, lax.longitude);
        double distHND_LAX_nm = locManager.distanceInNM(distHND_LAX_km);
        cout << "Distance HND (" << hnd.city << ") to LAX (" << lax.city << "): "
                  << distHND_LAX_km << " km (" << distHND_LAX_nm << " NM)" << endl;
        
        bool isHND_LAX_Oceanic = locManager.isOceanicFlight(hnd.latitude, hnd.longitude, lax.latitude, lax.longitude);
        cout << "  Is HND to LAX oceanic? " << (isHND_LAX_Oceanic ? "Yes" : "No") << endl;
    } else {
        cerr << "Could not find HND or LAX for distance calculation." << endl;
    }
    
    if (lhr_found && cdg_found) {
        double distLHR_CDG_km = locManager.calculateDistanceInKM(lhr.latitude, lhr.longitude, cdg.latitude, cdg.longitude);
        double distLHR_CDG_nm = locManager.distanceInNM(distLHR_CDG_km);
        cout << "Distance LHR (" << lhr.city << ") to CDG (" << cdg.city << "): "
                  << distLHR_CDG_km << " km (" << distLHR_CDG_nm << " NM)" << endl;

        bool isLHR_CDG_Oceanic = locManager.isOceanicFlight(lhr.latitude, lhr.longitude, cdg.latitude, cdg.longitude);
        cout << "  Is LHR to CDG oceanic? " << (isLHR_CDG_Oceanic ? "Yes" : "No") << endl;
    } else {
        cerr << "Could not find LHR or CDG for oceanic check." << endl;
    }

    // Example with arbitrary coordinates for isOceanicFlight
    cout << "\n--- Oceanic Flight Test (Arbitrary Coords) ---" << endl;
    // Test Asia (e.g., Shanghai PVG approx: 31.14 N, 121.80 E) to America (e.g. SFO approx: 37.62 N, -122.37 W)
    bool testOceanic1 = locManager.isOceanicFlight(31.14, 121.80, 37.62, -122.37);
    cout << "Flight from (31.14, 121.80) to (37.62, -122.37) oceanic? " << (testOceanic1 ? "Yes" : "No") << endl;

    // Test Europe (e.g., Madrid MAD approx: 40.49 N, -3.56 W) to America (e.g., Miami MIA approx: 25.79 N, -80.29 W)
    bool testOceanic2 = locManager.isOceanicFlight(40.49, -3.56, 25.79, -80.29);
    cout << "Flight from (40.49, -3.56) to (25.79, -80.29) oceanic? " << (testOceanic2 ? "Yes" : "No") << endl;
    
    // Test within Europe (e.g., Madrid MAD to Rome FCO approx: 41.80 N, 12.23 E)
    bool testNonOceanic = locManager.isOceanicFlight(40.49, -3.56, 41.80, 12.23);
    cout << "Flight from (40.49, -3.56) to (41.80, 12.23) oceanic? " << (testNonOceanic ? "Yes" : "No") << endl;


    return 0;
}