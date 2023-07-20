#include <stdio.h>
#include <string>
#include "classes.hpp"


using namespace std;

/**
 *@file
 */

/*! \mainpage System rezerwacji biletów lotniczych
 *\section intro_sec Wstęp
 *  Program będący prostym systemem rezerwacji biletów lotniczych
 *
 *\section test_sec Plik wejściowy
 *W załączonych plikach jest drobna baza danych, służąca do demonstracji działania programu, oraz odpowiednio nazwane pliki wejścia/wyjścia.
 *
 *\author Radosław Grzywacz
 *
 *
*/
 

/**
 *@brief readDataBase - funkcja wczytująca bazę lotów i tworząca odpowiednie obiekty klasy Flight
 *@param file - plik wejściowy z bazą lotów
 *@param flights - wektor obiektów klasy Flight, do którego będą trafiać wczytane loty
 */
void readDataBase(ifstream& file, vector<Flight>& flights);//function that takes every flight from the input file and creates new objects of Flight class

/**
 *@brief readOrders - funkcja wczytująca plik przechowujący informacje o istniejących już zamówieniach
 *@param orderList - nazwa pliku wejściowego
 *@param orders - wektor przechowujący obiekty klasy Order, do którego będą trafiać wczytane z pliku zamówienia
 */
void readOrders(string& ordersList, vector<Order>& orders);     //function that reads previous orders from data base

/**
 *@brief readCustomers - funkcia wczytująca z pliku przechowującego informacje o istniejących już klientach systemu
 *@param customersList - nazwa pliku przechowującego liste klientów
 *@param customers - wektor przechowujący obiekty klasy Customer, do którego będą trafiać wczytani z pliku użytkownicy
 */
void readCustomers(const string& customersList, vector<Customer>& customers);   //function that reads customers from data base

/**
 *@brief departureCountriesPrinting - funkcja wyświetlająca wszystkie dostępne państwa wylotu
 *@param flights - wektor obiektów klasy Flight
 *@param depCountries - kontener przechowujący nazwy dostępnych państw
 */
void departureCountriesPrinting(vector<Flight>& flights,set<string>& depCountries); //function that shows every available departure country

/**
 *@brief departureAirportsForEveryCountry - funkcja która rozdziela dostępne lotniska pomiędzy państwami, w których się znajdują
 *@param chosen_depCountry - zmienna przechowująca wybrane przez użytkownika państwo
 *@param flights - wektor obiektów klasy Flight
 *@param depAirports - kontener przechowujący nazwy dostępnych lotnisk
 */
void departureAirportsForEveryCountry(string chosen_depCountry, vector<Flight>& flights, set<string>& depAirports); //function that takes only airports in selected country

/**
 *@brief arrivalCountriesPrinting - funkcja wyświetlająca wszystkie dostępne państwa przylotu
 *@param flights - wektor obiektów klasy Flight
 *@param arrCountries - kontener przechowujący dostępne państwa przylotu
 */
void arrivalCountriesPrinting(vector<Flight>& flights, set<string>& arrCountries); //function that shows every available arrival country

/**
 *@brief arrivalAirportsForEveryCountry - funkcja która rozdziela dostępne lotniska pomiędzy państwami, w których się znajdują
 *@param chosen_arrCountry - zmienna przechowująca wybrane przez użytkownika państwo
 *@param flights - wektor obiektów klasy Flight
 *@param arrAirports - kontener przechowujący nazwy dostępnych lotnisk
 */
void arrivalAirportsForEveryCountry(string chosen_arrCountry, vector<Flight>& flights, set<string>& arrAirports); //function that takes only airports in selected country


/**
 *@brief searchedFlights - funkcja wyszukująca loty spełniające wymagania użytkownika
 *@param flights - wektor obiektów klasy Flight
 *@param propositions - wektor do którego trafiają pasujące loty
 *@param chosen_depCountry - zmienna przechowująca wybrane przez użytkownika państwo wylotu
 *@param chosen_depAirport - zmienna przechowująca wybrane lotnisko
 *@param chosen_arrCountry - zmienna przechowująca wybrane przez użytkownika państwo przylotu
 *@param chosen_arrAirport - zmienna przechowująca wybrane lotnisko
 *@param didIfoundedSomethingForU - zmienna boolowska określająca czy zostały znalezione jakiekolwiek loty
  */
void searchedFlights(vector<Flight>& flights, vector<Flight>& propositions, string chosen_depCountry, string chosen_depAirport,string chosen_arrCountry, string chosen_arrAirport, bool& didIfoundedSomethingForU); //With all geathered information this function founds perfect flight

/**
 *@brief reservation - funkcja rezerwująca wybrany lot
 *@param flights - wektor obiektów klasy Flight
 *@param orders - wektor przechowujący obiekty klasy Order
 *@param customers - wektor przechowujący obiekty klasy Customer
 *@param chosen_flight - zmienna przechowująca numer wybranego lotu
 *@param login - zmienna przechowująca login użytkownika
 *@param password - zmienna przechowująca hasło użytkownika
 *@param name - zmienna przechowująca imie użytkownika
 *@param surname - zmienna przechowująca nazwisko użytkownika
 *@param wantedTickets - zmienna przechowująca wybraną przez klienta ilość biletów
 */
void reservation(vector<Flight>& flights, vector<Order>& orders, vector<Customer>& customers, string chosen_flight, string login, string password, string name, string surname, int wantedTickets);

/**
 *@brief sign_in - funkcja służąca zalogowaniu się lub utworzeniu konta
 *@param customers - wektor przechowujący obiekty klasy Customer
 *@param login - zmienna przechowująca login użytkownika
 *@param password - zmienna przechowująca hasło użytkownika
 *@param name - zmienna przechowująca imie użytkownika
 *@param surname - zmienna przechowująca nazwisko użytkownika
 */
pair<string, string> sign_in(vector<Customer>& customers, string login, string password, string name, string surname);


/**
 *@brief cancellation - funkcja służąca anulowaniu zamówienia
 *@param flights - wektor obiektów klasy Flight
 *@param orders - wektor przechowujący obiekty klasy Order
 *@param customers - wektor przechowujący obiekty klasy Customer
 *@param login - zmienna przechowująca login użytkownika
 *@param password - zmienna przechowująca hasło użytkownika
 */
void cancellation(vector<Flight>& flights, vector<Order>& orders, vector<Customer>& customers, string login, string password);


//these functions save every important information to files so they can be read in the next session

/**
 *@brief flightsToCSV - funkcja zapisująca zaaktualizowane dane lotów
 *@param flights - wektor obiektów klasy Flight
 *@param filename - zmienna przechowująca nazwe pliku wyjściowego
 */
void flightsToCSV(const vector<Flight>& flights, const string& filename);

/**
 *@brief customersToCSV - funkcja zapisująca zaaktualizowane dane użytkowników
 *@param customers - wektor obiektów klasy Customer
 *@param customersList - zmienna przechowująca nazwe pliku wyjściowego
 */
void customersToCSV(vector<Customer>& customers, const string& customersList);

/**
 *@brief ordersToCSV - funkcja zapisująca zaaktualizowane dane zamówień
 *@param orders - wektor obiektów klasy Order
 *@param zamowienia - zmienna przechowująca nazwe pliku wyjściowego
 */
void ordersToCSV(const vector<Order>& orders, const string& zamowienia);


