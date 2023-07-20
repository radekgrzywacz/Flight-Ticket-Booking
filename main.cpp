#include <iostream>
#include "functions.hpp"
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main() {
    string isEnd;
    string inputFile = "wyjscie.txt";  //name of file that stores data base input
    string filename = "wyjscie.txt";   //name of file that stores data base output
    string customersList = "klienci.txt";       //name of file that stores clients list
    string ordersList = "zamowienia.txt";       //name of file that stores orders list
    ifstream file(inputFile);
    vector<Flight> flights;         //vector storing all Flight objects
    vector<Customer> customers;     //vector storing all Customer objects
    vector<Order> orders;           //vector storing all Order objects
    set<string> depCountries;
    set<string> depAirports;
    set<string> arrCountries;
    set<string> arrAirports;
    string chosen_depCountry;
    string chosen_depAirport;
    string chosen_arrCountry;
    string chosen_arrAirport;
    string chosen_flight;
    vector<Flight> propositions;
    bool didIfoundSomethingForU = false;    //variable that lets the user to try again after negative search
    
    //reservation user data:
    string login;
    string password;
    string name;
    string surname;
    int wantedTickets;
    
    
   do{
        cout << "\n=====================================================================================" << endl;
        cout << "\n                    WITAMY W SYSTEMIE REZERWACJI BILETÓW LOTNICZYCH" << endl;
        cout << "             naciśnij 1 aby wyszukać nowy lot lub 2 aby anulować rezerwacje" << endl;
        cout << "\n=====================================================================================" << endl;
        int input;
        do{
            readDataBase(file, flights);
            readOrders(ordersList, orders);
            readCustomers(customersList, customers);
            cin >> input;
            if(input == 1){
                int choice1;    //departure country
                int choice2;    //departure airport
                int choice3;    //arrival country
                int choice4;    //arrival airport
                bool validInput = false;    //input error handling
                
                //User choses the destination country
                cout << "Proszę wybrać kraj z którego chcesz lecieć.\nLista dostępnych państw:" << endl;
                departureCountriesPrinting(flights, depCountries);
                cout << "\n\nWybierz numer przy wybranym państwie: ";
                while (!validInput) {
                    if (!(cin >> choice1)) { // check if choice1 is intiger
                        cin.clear();
                        cin.ignore();
                        cout << "Niepoprawne dane. Wprowadź ponownie: ";
                    }
                    else if (choice1 < 1 || choice1 > depCountries.size()) { // check if choice1 is in range
                        cout << "Niepoprawny numer. Wprowadź ponownie: ";
                    }
                    else { // Valid input
                        validInput = true;
                    }
                }
                auto it1 = depCountries.begin();
                advance(it1, choice1 - 1);       //iteration to the selected country
                chosen_depCountry = *it1;
                cout << endl;
                validInput = false;
                
                //User choses the destination airport
                cout << "Lotniska dostępne w wybranym kraju: " << endl;
                departureAirportsForEveryCountry(chosen_depCountry, flights, depAirports);
                cout << "\n\nWybierz numer przy wybranym lotnisku: ";
                while (!validInput) {
                    if (!(cin >> choice2)) { // check if choice2 is intiger
                        cin.clear();
                        cin.ignore();
                        cout << "Niepoprawne dane. Wprowadź ponownie: ";
                    }
                    else if (choice2 < 1 || choice2 > depAirports.size()) { // check if choice2 is in range
                        cout << "Niepoprawny numer. Wprowadź ponownie: ";
                        
                    }
                    else { // Valid input
                        validInput = true;
                    }
                }
                auto it2 = depAirports.begin();
                advance(it2, choice2 - 1);
                chosen_depAirport = *it2;
                cout << endl;
                validInput = false;
                
                //User choses the arrival country
                cout << "Proszę wybrać kraj docelowy.\nLista dostępnych państw:" << endl;
                arrivalCountriesPrinting(flights, arrCountries);
                cout << "\n\nWybierz numer przy wybranym państwie: ";
                while (!validInput) {
                    if (!(cin >> choice3)) { // check if choice3 is intiger
                        cin.clear();
                        cin.ignore();
                        cout << "Niepoprawne dane. Wprowadź ponownie: ";
                    }
                    else if (choice3 < 1 || choice3 > arrCountries.size()) { // check if choice3 is in range
                        cout << "Niepoprawny numer. Wprowadź ponownie: ";
                        
                    }
                    else { // Valid input
                        validInput = true;
                    }
                }
                auto it3 = arrCountries.begin();
                advance(it3, choice3-1);
                chosen_arrCountry = *it3;
                cout << endl;
                validInput = false;
                
                //User choses the arrival airport
                cout << "Lotniska dostępne w wybranym kraju: " << endl;
                arrivalAirportsForEveryCountry(chosen_arrCountry, flights, arrAirports);
                cout << "\n\nWybierz numer przy wybranym lotnisku: ";
                while (!validInput) {
                    if (!(cin >> choice4)) { // check if choice4 is intiger
                        cin.clear();
                        cin.ignore();
                        cout << "Niepoprawne dane. Wprowadź ponownie: ";
                    }
                    else if (choice4 < 1 || choice4 > arrAirports.size()) { // check if choice4 is in range
                        cout << "Niepoprawny numer. Wprowadź ponownie: ";
                        
                    }
                    else { // Valid input
                        validInput = true;
                    }
                }
                auto it4 = arrAirports.begin();
                advance(it4, choice4 - 1);
                chosen_arrAirport = *it4;
                cout << endl;
                validInput = false;
                
                
                searchedFlights(flights, propositions, chosen_depCountry, chosen_depAirport, chosen_arrCountry, chosen_arrAirport, didIfoundSomethingForU);
                if(!didIfoundSomethingForU){
                    break;
                }
                
                //User choses flight
                int finalChoice;
                cout << "Wprowadź numer wybranego lotu: ";
                while (!validInput) {
                    if (!(cin >> finalChoice)) { // check if finalChoice is intiger
                        cin.clear();
                        cin.ignore();
                        cout << "Niepoprawne dane. Wprowadź ponownie: ";
                    }
                    else if (finalChoice < 1 || finalChoice > propositions.size()) { // check if finalChoice is in range
                        cout << "Niepoprawny numer. Wprowadź ponownie: ";
                        
                    }
                    else { // Valid input
                        validInput = true;
                    }
                }
                
                chosen_flight = propositions[finalChoice - 1].flightNumber;
                propositions.clear();
                cout << "\n=====================================================================================" << endl;
                cout << "\n              Cieszymy się, że udało ci się znaleźć poszukiwany bilet." << endl;
                cout << "                    Rozpoczynamy etap składania rezerwacji." << endl;
                cout << "\n=====================================================================================" << endl;
                
                reservation(flights, orders, customers, chosen_flight,login, password, name, surname, wantedTickets);
                
                
            }//CANCELLATION
            else if (input == 2){
                cout << "Przykro nam, że chcesz anulować swój lot. Mamy nadzieję, że jeszcze do nas wrócisz." << endl;
                cancellation(flights, orders, customers, login, password);
                
            }
            else{
                cin.clear();
                cin.ignore();
                cout << "Proszę wprowadzić odpowiedni znak: ";
            }
        }while(input != 1 && input != 2);
         
        //Saving changes:
        flightsToCSV(flights, filename);
        customersToCSV(customers, customersList);
        ordersToCSV(orders, ordersList);
       customers.clear();
       orders.clear();
        
       cout << "Naciśnij 'q' aby wyłączyć system lub dowolny przycisk aby wrócić do panelu początkowego. Dziękujemy!" << endl;
       cout << "Wprowadź znak: ";
       cin >> isEnd;
    }while(isEnd != "q");
    return 0;
}
