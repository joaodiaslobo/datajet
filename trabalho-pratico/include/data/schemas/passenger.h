#ifndef PASSENGER_H
#define PASSENGER_H

typedef struct passenger Passenger;

Passenger* create_passenger(char* user_id, char* flight_id);

void free_passenger(Passenger* passenger);

#endif