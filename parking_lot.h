#ifndef PARKING_LOT_H
#define PARKING_LOT_H


typedef struct Vehicle
{
    char license_plate[20]; //license plate of the vehicle
    int spot_number; //parking spot number
    char entry_time[10]; //entry time as a string for example 10:50
} Vehicle;

typedef struct ParkingLot
{
    struct Vehicle *vehicles; //pointer to an array of vehicles
    int total_spots; //total number of parking spots
    int occupied_spots; //numbers of currently occupied spots
    int available_spots;
} ParkingLot;

struct ParkingLot* initialize_parking_lot(int total_spots);
int allocate_spot(struct ParkingLot *lot, const char *license_plate, const char *entry_time); //allocate the next available parking spot to a vehicle with the guven license plate and entry time
void release_spot(struct ParkingLot *lot, int spot_number); //make specific parkig spot free
void display_available_spots(const  struct ParkingLot *lot);
void save_data(const struct ParkingLot *lot, const char *file_name);//save parking lot data
void load_data(struct ParkingLot *lot, const char *file_name);
void free_parking_lot(struct ParkingLot *lot);  // Declaration of the free function




#endif

