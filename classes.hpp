#pragma once
#include <stdio.h>
#include <iostream>
#include <set>
#include <vector>
#include <string>



using namespace std;


class Flight;
class Customer;

/**
 *@brief Order - Klasa reprezentująca zamówienia
 */
class Order{
private:
    int orderID; /**@brief OrderID - zmienna przechowująca losowo generowany numer zamówienia*/
    int numberOfTickets; /**@brief numberOfTickets - zmienna przechowująca ilość zamówionych biletów*/
    string flightNumber; /**@brief flightNumber - zmienna przechowująca numer lotu*/
public:
    /**
     *@brief Order - konstruktor klasy Order
     *@param id - numer zamówienia
     *@param numTickets - ilość biletów
     *@param fn - numer lotu
     */
    Order(int id, int numTickets, string fn);
    
    /**
     *@brief ~Order - destruktor klasy Order
     */
    ~Order();
    
    friend void ordersToCSV(const vector<Order>& orders, const string& zamowienia);
    friend void cancellation(vector<Flight>& flights, vector<Order>& orders, vector<Customer>& customers, string login, string password);
};

/**
 *@brief Customer - klasa reprezentująca użytkownika
 */
class Customer{
private:
    string login; ///*
    string password;
    string name;
    string surname;
    vector<int> orderIDs;
public:
    /**
     *@brief Customer - konstruktor klasy Customer
     *@param l - login
     *@param p - hasło
     *@param n - imię
     *@param sn - nazwisko
     */
    Customer(string l, string p, string n, string sn);
    
    /**
     *@brief ~Customer - destruktor klasy Customer
     */
    ~Customer();
    
    /**
     *@brief customerOrderNew - metoda dodająca zamówienie do danego obiektu
     *@param id - numer zamówienia
     */
    void customerOrdersNew(int id);
    
    /**
     *@brief customerOrderDelete - metoda usuwająca zamówienie z danego obiektu
     *@param id - numer zamówienia
     */
    void customerOrderDelete(int id);
    friend void reservation(vector<Flight>& flights, vector<Order>& orders, vector<Customer>& customers, string chosen_flight, string login, string password, string name, string surname, int wantedTickets);
    friend void customersToCSV(vector<Customer>& customers, const string& customersList);
    friend void users_to_file(vector<Customer>& customers, const string& customersList);
    friend void readCustomers(const string& customersList, vector<Customer>& customers);
    friend void cancellation(vector<Flight>& flights, vector<Order>& orders, vector<Customer>& customers, string login, string password);
    friend pair<string, string> sign_in(vector<Customer>& customers, string login, string password, string name, string surname);
};

/**
 *@brief Flight - klasa reprezentująca poszczególne loty
 */
class Flight{
private:
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
    friend void departureCountriesPrinting(vector<Flight>& flights,set<string>& depCountries);
    friend void departureAirportsForEveryCountry(string chosen_depCountry, vector<Flight>& flights, set<string>& depAirports);
    friend void arrivalCountriesPrinting(vector<Flight>& flights, set<string>& arrCountries);
    friend void arrivalAirportsForEveryCountry(string chosen_arrCountry, vector<Flight>& flights, set<string>& arrAirports);
    friend void searchedFlights(vector<Flight>& flights, vector<Flight>& propositions, string chosen_depCountry, string chosen_depAirport,string chosen_arrCountry, string chosen_arrAirport, bool& didIfoundedSomethingForU);
    friend void reservation(vector<Flight>& flights, vector<Order>& orders, vector<Customer>& customers, string chosen_flight, string name, string surname, int wantedTickets);
    friend void flightsToCSV(const vector<Flight>& flights, const string& filename);
    friend void cancellation(vector<Flight>& flights, vector<Order>& orders, vector<Customer>& customers, string login, string password);

public:
    
    /**
     *@brief Flight - konstruktor klasy Flight
     *@param fn - numer lotu
     *@param am - model samolotu
     *@param cap - pojemność
     *@param mCap - max pojemność
     *@param sb - zabookowane miejsca
     *@param depC - kraj wylotu
     *@param depAP - lotnisko wylotu
     *@param depTime - czas wylotu
     *@param arrC - kraj przylotu
     *@param arrAP - lotnisko przylotu
     *@param atime - czas przylotu
     */
    Flight(string fn, string am, int cap, int mCap, int sb, string depC, string depAP, string depTime, string arrC, string arrAP, string atime);
    
    string flightNumber;
    
    /**
     *@brief capacityUpdate - metoda aktualizująca miejsce w samolocie
     *@param wantedTickets - ilość zarezerwowanych biletów
     */
    void capacityUpdate(int wantedTickets);
    
    
    /**
     *@brief ticketCancellation - metoda aktualizująca miejsce w samolocie
     *@param wantedTickets - ilość zamówionych biletów
     */
    void ticketCancellation(int orderedTickets);
    
};
