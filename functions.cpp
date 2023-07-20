#include "functions.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <random>

using namespace std;

void readDataBase(ifstream& file, vector<Flight>& flights){
    if (file.is_open()){
        string line;
        
        while(getline(file, line)){
            stringstream ss(line);  //here are the temporary variables that store data until the object is created
            string flightNumber;
            string airplaneModel;
            int capacity;
            int maxCapacity;
            int seatsBooked;
            string departureCountry;
            string departureAirport;
            string departureTime;
            string arrivalCountry;
            string arrivalAirport;
            string arrivalTime;
            
            //getting informations between comas
            getline(ss, flightNumber, ',');
            getline(ss, airplaneModel, ',');
            ss >> capacity;
            ss.ignore(1);
            ss >> maxCapacity;
            ss.ignore(1);
            ss >> seatsBooked;
            getline(ss.ignore(1), departureCountry, ',');
            getline(ss, departureAirport, ',');
            getline(ss, departureTime, ',');
            getline(ss, arrivalCountry, ',');
            getline(ss, arrivalAirport, ',');
            getline(ss, arrivalTime, ',');

            flights.emplace_back(flightNumber, airplaneModel, capacity, maxCapacity, seatsBooked, departureCountry, departureAirport, departureTime, arrivalCountry, arrivalAirport, arrivalTime);
        
        }
        file.close();
    }
}


void readOrders(string& ordersList, vector<Order>& orders){
    ifstream file(ordersList);
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            stringstream ss(line);
            int orderID;
            int numberOfTickets;
            string flightNumber;
            
            ss >> orderID;
            ss.ignore(1);
            ss >> numberOfTickets;
            ss.ignore(1);
            getline(ss, flightNumber, 's');
                
            orders.emplace_back(orderID, numberOfTickets, flightNumber);
            
        }
    }
    file.close();
}


void readCustomers(const string& customersList, vector<Customer>& customers) {
    ifstream file(customersList);
    if(file.is_open()){
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string login, password, name, surname, orderIDs_str;
            vector<int> orderIDs;
            
            getline(ss, login, ',');
            getline(ss, password, ',');
            getline(ss, name, ',');
            getline(ss, surname, ',');
            
            // read the rest of the line into orderIDs_str
            getline(ss, orderIDs_str);
            
            // parse the integers from orderIDs_str
            stringstream ss_orderIDs(orderIDs_str);
            int orderID;
            while (ss_orderIDs >> orderID) {
                orderIDs.push_back(orderID);
                if (ss_orderIDs.peek() == ',') {
                    ss_orderIDs.ignore();
                }
            }
            
            Customer customer(login, password, name, surname);
            for (int i = 0; i < orderIDs.size(); i++) {
                customer.customerOrdersNew(orderIDs[i]);
            }
            customers.push_back(customer);
        }
    }
    file.close();
}



void departureCountriesPrinting(vector<Flight>& flights, set<string>& depCountries){
    //deleting duplicates out of country list
    for(int i = 0; i < flights.size() - 1; i++){
        if(depCountries.find(flights[i].departureCountry) == depCountries.end()){
            depCountries.insert(flights[i].departureCountry);
        }
    }
    int i = 1;
    
    //printing countries
    for(auto const &country : depCountries){
        cout << i << "." << country << "\t";
        i++;
    }
}

void departureAirportsForEveryCountry(string chosen_depCountry, vector<Flight>& flights, set<string>& depAirports){
    //deleting duplicates out of airport list
    for(int i = 0; i < flights.size() - 1; i++){
        if(flights[i].departureCountry == chosen_depCountry && depAirports.find(flights[i].departureAirport) == depAirports.end()){
            depAirports.insert(flights[i].departureAirport);
        }
    }
    int i = 1;
    
    //printing countries
    for(auto const &str : depAirports){
        cout << i << "." << str << "\t";
        i++;
    }
}


void arrivalCountriesPrinting(vector<Flight>& flights, set<string>& arrCountries){
    //deleting duplicates out of country list
    for(int i = 0; i < flights.size() - 1; i++){
        if(arrCountries.find(flights[i].arrivalCountry) == arrCountries.end()){
            arrCountries.insert(flights[i].arrivalCountry);
        }
    }
    int i = 1;
    
    //printing countries
    for(auto const &str : arrCountries){
        cout << i << "." << str << "\t";
        i++;
    }
}


void arrivalAirportsForEveryCountry(string chosen_arrCountry, vector<Flight>& flights, set<string>& arrAirports){
    //deleting duplicates out of airport list
    for(int i = 0; i < flights.size() - 1; i++){
        if(flights[i].arrivalCountry == chosen_arrCountry && arrAirports.find(flights[i].arrivalAirport) == arrAirports.end()){
            arrAirports.insert(flights[i].arrivalAirport);
        }
    }
    int i = 1;
    
    //printing countries
    for(auto const &str : arrAirports){
        cout << i << "." << str << "\t";
        i++;
    }
}


void searchedFlights(vector<Flight>& flights, vector<Flight>& propositions, string chosen_depCountry, string chosen_depAirport,string chosen_arrCountry, string chosen_arrAirport, bool& didIfoundedSomethingForU){
    for(int i = 0; i < flights.size(); i++){
        if(flights[i].departureCountry == chosen_depCountry && flights[i].departureAirport == chosen_depAirport && flights[i].arrivalCountry == chosen_arrCountry && flights[i].arrivalAirport == chosen_arrAirport){
            propositions.push_back(flights[i]);
        }
    }
    
    //printing best results
    if(propositions.size() > 0){
        cout << "Znaleźliśmy dla ciebie następujące loty: " << endl;
        for(int i = 0; i < propositions.size(); i++){
            cout << "\n" << i + 1 <<". \tKraj wylotu: " << propositions[i].departureCountry << "\n\tLotnisko wylotu: " << propositions[i].departureAirport << "\n\tData wylotu: " << propositions[i].departureTime << "\n\tKraj przylotu: " << propositions[i].arrivalCountry << "\n\tLotnisko przylotu: " << propositions[i].arrivalAirport << "\n\tData przylotu: " << propositions[i].arrivalTime << "\n" <<endl;
            didIfoundedSomethingForU = true;
        }
    }else{
        cout << "Przykro nam, ale aktualnie nie oferujemy poszukiwanego przez ciebie lotu. Zachęcamy jednak do zmiany kryteriów wyszukiwania i spróbowania ponownie." << endl;
        
    }
}

pair<string, string> sign_in(vector<Customer>& customers, string login, string password, string name, string surname){
    int input;
    bool is_valid = true;
    do{
        cout << "Naciśnij 1 aby się zalogować lub 2 aby stworzyć konto: ";
        cin >> input;
        switch(input) {
            case 1:
                while(name.empty()){
                    cout << "Wprowadź nazwę użytkownika: ";
                    cin >> login;
                    cout << "\nWprowadź hasło: ";
                    cin >> password;
                    for(int i = 0; i < customers.size(); i++){
                        if(customers[i].login == login && customers[i].password == password){
                            name = customers[i].name;
                            surname = customers[i].surname;
                            break;
                        }
                    }
                    if(name.empty()){
                        cout << "Przykro nam, nie znaleziono twojego konta. Spróbuj ponownie." << endl;
                    }
                }
                
                break;
                
            case 2:
                cout << "Wprowadź nazwę użytkownika: ";
                cin >> login;
                cout << "\nWprowadź hasło: ";
                cin >> password;
                cout << "Wprowadź swoje imię: ";
                cin >> name;
                cout << "Wprowadź swoje nazwisko: ";
                cin >> surname;
                customers.emplace_back(login, password, name, surname);
                break;
                
            default:
                cout << "Wpisz poprawną cyfrę.";
                is_valid = false;
                break;
        }
    }while(!is_valid);
    return make_pair(login, password);
    
}

void reservation(vector<Flight>& flights, vector<Order>& orders, vector<Customer>& customers, string chosen_flight, string login, string password, string name, string surname, int wantedTickets){
    //sign_in(customers, login, password, name, surname);
    pair<string, string> loginData = sign_in(customers, login, password, name, surname);
    login = loginData.first;
    password = loginData.second;
    cout << "\nWprowadź liczbę biletów: ";
    cin >> wantedTickets;
    for(int i = 0; i < flights.size(); i++){
        if(chosen_flight == flights[i].flightNumber){
            flights[i].capacityUpdate(wantedTickets);
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(100000, 1000000);
            int id = dis(gen);
            orders.emplace_back(id, wantedTickets, chosen_flight);
            // orders[i].setFlighNumber(chosen_flight);
            for(int j = 0; j < customers.size(); j++){
                if(customers[j].login == login && customers[j].password == password){
                    customers[j].orderIDs.push_back(id);
                    break;
                }
            }
            cout << "Dziękujemy za złożenie rezerwacji. Twój unikatowy numer rezerwacji to " << id << ". Prosimy o zachowanie tego numeru w razie potrzeby zmian w rezerwacji." << endl;
        }else{
            break;
        }
    }
}


void cancellation(vector<Flight>& flights, vector<Order>& orders, vector<Customer>& customers, string login, string password){
    bool is_valid = true;
    int index;
    do{
        cout << "Proszę wprowadzić swój login: ";
        cin >> login;
        cout << "\nProszę wprowadzić hasło: ";
        cin >> password;
        for(int i = 0; i < customers.size(); i++){
            if(customers[i].login == login && customers[i].password == password){
                is_valid = false;
                index = i;
                break;
            }
        }
        if(is_valid == true){
            cout << "Nie ma takiego konta. Spróbuj ponownie." << endl;
        }
    }while(is_valid);
    
    cout << "Oto twoje zamówienia:" << endl;
    for(int i = 0; i < customers[index].orderIDs.size(); i++){
        cout << "\t" << customers[index].orderIDs[i] << endl;
    }
    int id; //order id
    int orderedTickets; //amount of tickets
    cout << "Proszę wprowadzić numer rezerwacji, którą chcesz anulować: ";
    cin >> id;
    
    //searching for order
    for(int i = 0; i < orders.size(); i++){
        if(id == orders[i].orderID){
            //searching for flight
            for(int h = 0; h < flights.size();h++){
                if(orders[i].flightNumber == flights[h].flightNumber){
                    cout << "Czy na pewno chcesz anulować rezerwacje na następujący lot?:"<< endl;
                    cout << "\n" << "\tKraj wylotu: " << flights[h].departureCountry << "\n\tLotnisko wylotu: " << flights[h].departureAirport << "\n\tData wylotu: " << flights[h].departureTime << "\n\tKraj przylotu: " << flights[h].arrivalCountry << "\n\tLotnisko przylotu: " << flights[h].arrivalAirport << "\n\tData przylotu: " << flights[h].arrivalTime << "\n" <<endl;
                    
                    cout << "Naciśnij 1 aby anulować lub 2 jeśli się rozmyśliłeś: ";
                    int yes_or_no;
                    is_valid = true;
                    do{
                        cin >> yes_or_no;
                        switch (yes_or_no){
                            case 1:
                                //deleting from orders
                                orderedTickets = orders[i].numberOfTickets;
                                for(int j = 0; j < flights.size(); j++){
                                    if(flights[j].flightNumber == orders[i].flightNumber){
                                        flights[i].ticketCancellation(orderedTickets);
                                        orders[i].~Order();
                                        orders.erase(orders.begin() + i);
                                        break;
                                    }
                                }
                                customers[index].customerOrderDelete(id); //deleting from customer
                                break;
                            case 2:
                                cout << "Cieszymy się, że zostajesz z nami" << endl;
                                break;
                            default:
                                cout << "Wpisz poprawną cyfrę: ";
                                is_valid = false;
                                break;
                        }
                    }while(!is_valid);
                }
                break;
            }
        }
    }
}

void flightsToCSV(const vector<Flight>& flights, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        // Write data rows
        for (const Flight& flight : flights) {
            file << flight.flightNumber << ","
                 << flight.airplaneModel << ","
                 << flight.capacity << ","
                 << flight.maxCapacity << ","
                 << flight.seatsBooked << ","
                 << flight.departureCountry << ","
                 << flight.departureAirport << ","
                 << flight.departureTime << ","
                 << flight.arrivalCountry << ","
                 << flight.arrivalAirport << ","
                 << flight.arrivalTime << endl;
        }
        file.close();
    } else {
        cerr << "Nie można otworzyć pliku" << filename << " do zapisu" << endl;
    }
}


void customersToCSV(vector<Customer>& customers, const string& customersList) {
    ofstream file(customersList);
    if (file.is_open()) {
        for (const Customer& customer : customers) {
            file << customer.login << ","
            << customer.password << ","
            << customer.name << ","
            << customer.surname << ",";
            // Write orderIDs as comma-separated list
            for (size_t i = 0; i < customer.orderIDs.size(); i++) {
                if (i > 0) {
                    file << ",";
                }
                file << customer.orderIDs[i];
            }
            file << endl;
        }
        file.close();
    }
}

void ordersToCSV(const vector<Order>& orders, const string& zamowienia){
    ofstream file(zamowienia);
    if (file.is_open()) {
        // Write data rows
        for (const Order& order : orders) {
            file << order.orderID << "," << order.numberOfTickets << "," << order.flightNumber << endl;
        }
        file.close();
    }
}
