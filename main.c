#include "parking_lot.h"
#include <stdio.h>

int main(){
    //initialize Parking lot
    ParkingLot *lot = initialize_parking_lot(10);
    if(!lot){
        printf("faild to initialize parking lot.\n");
        return 1;
    }

    //allocate parking spots
    printf("Allocating spots ...\n");
    allocate_spot(lot, "ABC123", "10:00");
    allocate_spot(lot, "ZXC456", "14:00");
    allocate_spot(lot, "UGO489", "18:48");

    //display available spots
    display_available_spots(lot);

    //save the parking lot data to file
    save_data(lot, "parking_lot_data.txt");

    //release a spot
    printf("\n Releasing spot 1...\n");
    release_spot(lot, 1);


    //Display available spots after releasing one
    display_available_spots(lot);

    //load parking lot data from file (simulation restarting the program)
    ParkingLot *new_lot = initialize_parking_lot(5);
    if(!new_lot){
        printf("Failed to initialize new parking lot.\n");
        return 1;
    }
    load_data(new_lot, "parking_lot_data.txt");

    //display available spots in the newly loaded parking lot
    display_available_spots(new_lot);

    //free the memory allocated for parking lots
    free_parking_lot(lot);
    free_parking_lot(new_lot);

    return 0;
}