#include "classes.hpp"


Flight::Flight(string fn, string am, int cap, int mCap, int sb, string depC, string depAP, string depTime, string arrC, string arrAP, string atime)
{
    flightNumber = fn;
    airplaneModel = am;
    capacity = cap;
    maxCapacity = mCap;
    seatsBooked = sb;
    departureCountry = depC;
    departureAirport = depAP;
    departureTime = depTime;
    arrivalCountry = arrC;
    arrivalAirport = arrAP;
    arrivalTime = atime;
    
}

void Flight::capacityUpdate(int wantedTickets){
    if(seatsBooked + wantedTickets <= capacity){
        seatsBooked = seatsBooked + wantedTickets;
        capacity = capacity - seatsBooked;
    }else{
        cout << "Przepraszamy, niestety zostało nam " << capacity - seatsBooked << " wolnych miejsc." << endl;
    }
}

void Flight::ticketCancellation(int orderedTickets){
    if(capacity + orderedTickets <= maxCapacity){
        capacity = capacity + orderedTickets;
    }else
        capacity = maxCapacity;
}

Order::Order(int id, int numTickets, string fn){
    orderID = id;
    numberOfTickets = numTickets;
    flightNumber = fn;
    
}

Order::~Order(){
        
}


Customer::Customer(string l, string p, string n, string sn){
    login = l;
    password = p;
    name = n;
    surname = sn;
}

Customer::~Customer(){
    
}

void Customer::customerOrdersNew(int id){
    orderIDs.push_back(id);
}

void Customer::customerOrderDelete(int id){
    for(int i = 0; i < orderIDs.size(); i++){
        if(id == orderIDs[i]){
            orderIDs.erase(orderIDs.begin() + i);
        }
        
    }
}


