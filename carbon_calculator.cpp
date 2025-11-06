#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Function to calculate transport emissions
double calculateTransportEmission(string mode, double dailyDistance) {
    double factor = 0.0;

    if (mode == "car") factor = 0.21;
    else if (mode == "bus") factor = 0.10;
    else if (mode == "bike") factor = 0.12;
    else if (mode == "bicycle" || mode == "walk") factor = 0.0;
    else {
        cout << "Invalid transport mode. Assuming walk.\n";
        factor = 0.0;
    }

    return dailyDistance * 365 * factor; // yearly emission in kg
}

// Function to calculate electricity emissions
double calculateElectricityEmission(double monthlyKwh) {
    double factor = 0.85; // kg CO₂ per kWh
    return monthlyKwh * 12 * factor; // yearly emission
}

// Function to calculate food emissions
double calculateFoodEmission(string foodType) {
    if (foodType == "veg") return 500;
    else if (foodType == "nonveg") return 1000;
    else {
        cout << "Invalid food type. Assuming vegetarian.\n";
        return 500;
    }
}

// Function to display suggestions
void showSuggestion(double total) {
    cout << "--------------------------------------\n";
    if (total > 5000)
        cout << "High emission level: Try carpooling, saving electricity, or shifting to greener habits.\n";
    else if (total > 3000)
        cout << "Moderate emission level: You can further improve by small lifestyle changes.\n";
    else
        cout << "Low emission level: Great! Keep up your eco-friendly habits.\n";
    cout << "--------------------------------------\n";
}

int main() {
    string transportMode, foodType;
    double dailyDistance, monthlyElectricity;
    
    cout << "--------------------------------------\n";
    cout << "     CARBON EMISSION CALCULATOR       \n";
    cout << "--------------------------------------\n";

    // Taking user inputs
    cout << "Enter distance travelled daily (in km): ";
    cin >> dailyDistance;
    cout << "Enter transport mode (car/bus/bike/bicycle/walk): ";
    cin >> transportMode;
    cout << "Enter monthly electricity usage (in kWh): ";
    cin >> monthlyElectricity;
    cout << "Enter food preference (veg/nonveg): ";
    cin >> foodType;

    // Calculate emissions
    double transportEmission = calculateTransportEmission(transportMode, dailyDistance);
    double electricityEmission = calculateElectricityEmission(monthlyElectricity);
    double foodEmission = calculateFoodEmission(foodType);
    double totalEmission = transportEmission + electricityEmission + foodEmission;

    // Display result
    cout << fixed << setprecision(2);
    cout << "\nCalculating your annual carbon footprint...\n\n";
    cout << "Transport Emission : " << transportEmission << " kg CO2/year\n";
    cout << "Electricity Emission : " << electricityEmission << " kg CO2/year\n";
    cout << "Food Emission : " << foodEmission << " kg CO2/year\n";
    cout << "--------------------------------------\n";
    cout << "Total Carbon Emission : " << totalEmission << " kg CO2/year\n";

    showSuggestion(totalEmission);

    // Save data in a file
    ofstream file("carbon_data.txt", ios::app);
    if (file.is_open()) {
        file << "User Carbon Report\n";
        file << "-----------------------\n";
        file << "Transport Mode: " << transportMode << endl;
        file << "Daily Distance: " << dailyDistance << " km\n";
        file << "Electricity Usage: " << monthlyElectricity << " kWh/month\n";
        file << "Food Type: " << foodType << endl;
        file << "Total Emission: " << totalEmission << " kg CO2/year\n";
        file << "-----------------------\n\n";
        file.close();
        cout << "Data saved successfully to carbon_data.txt\n";
    } else {
        cout << "Error: Unable to open file for writing.\n";
    }

    return 0;
}
