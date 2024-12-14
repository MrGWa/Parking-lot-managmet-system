#include "parking_lot.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//function to initialize the parking lot
 ParkingLot* initialize_parking_lot(int total_spots)
{
     ParkingLot *lot = ( ParkingLot *)malloc(sizeof( ParkingLot));
    // if (lot == NULL){
    //     return NULL;
    // }
    lot -> vehicles = ( Vehicle *)calloc(total_spots, sizeof( Vehicle));
    // if(lot -> vehicles == NULL){
    //     free(lot);
    //     return NULL;
    // }
    lot -> total_spots = total_spots;
    // lot -> occupied_spots = 0;
    lot->available_spots = total_spots;
    return lot;
}

//function to allocate a parking spot
int allocate_spot( ParkingLot *lot, const char *license_plate, const char *entry_time)
{
    if(lot -> occupied_spots >= lot -> total_spots)
        return -1; // no available spots
    
    for(int i = 0; i < lot -> total_spots; i++){
        //spot is free
        if(lot -> vehicles[i].spot_number == 0){
            lot -> vehicles[i].spot_number = i + 1;
            strcpy(lot -> vehicles[i].license_plate, license_plate);
            strcpy(lot -> vehicles[i].entry_time, entry_time);
            lot -> occupied_spots++;

            return i + 1; //return allocated spot number 
        }
    }

    return -1; //no available spots
}

// function to release a parking spot
void release_spot( ParkingLot *lot, int spot_number)
{
    if(spot_number <= 0 || spot_number > lot -> total_spots)
        return; //invalid spot number

    for(int i = 0; i < lot -> total_spots; i++){
        if(lot -> vehicles[i].spot_number == spot_number){
            lot -> vehicles[i].spot_number = 0;
            lot -> vehicles[i].license_plate[0] = '\0';
            lot -> vehicles [i].entry_time[0] = '\0';
            lot -> occupied_spots--;
            break;
        }
    }
}

void display_available_spots(const  ParkingLot *lot)
{
    printf("Available parking spots: \n");
    for(int i = 0; i < lot -> total_spots; i++){
        if(lot -> vehicles[i].spot_number == 0){//if the spot is free
        printf("spot %d is available.\n", i + 1);
        }
    }
}

void save_data(const  ParkingLot *lot, const char *file_name)
{
    FILE *file = fopen(file_name, "w");
    if (!file) {
        perror("Failed to open file");
        return;  // Return if file can't be opened
    }


    //Write total spots and occupied spots
    fprintf(file, "Total Spots : %d\n", lot -> total_spots);
    fprintf(file, "Occupied Spots : %d\n", lot -> occupied_spots);

    //Write details of each occupied spot
    fprintf(file, "Occupied Spot details:\n");
    fprintf(file, "--------------------------------\n");
    for(int i = 0 ; i < lot -> total_spots; i++){
        if(lot -> vehicles[i].spot_number != 0){
            //spot is occupied
            fprintf(file, "Spot Number: %d\n License Plate: %s\n Entry Time: %s\n", lot -> vehicles[i].spot_number, lot -> vehicles[i].license_plate, lot -> vehicles[i].entry_time);
            fprintf(file, "--------------------------------\n");
        }
    }
    fclose(file);
}

// Function to load parking lot data from a text file
void load_data( ParkingLot *lot, const char *file_name)
{
    FILE *file = fopen(file_name, "r"); //Open file for reading
    if(file == NULL){
        printf("No data file found, starting with an empty parking lot.\n");
        return;
    }

    //Read total spots and occupied spots
    fscanf(file, "Total Spots : %d\n", &lot -> total_spots);
    fscanf(file, "Occupied Spots : %d\n", &lot -> occupied_spots);

    //allocate memory for vehicles
    lot -> vehicles = ( Vehicle *)calloc(lot -> total_spots, sizeof( Vehicle));
    if(lot -> vehicles == NULL){
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    //read vehicle details
    for(int i = 0 ; i < lot -> occupied_spots; i++){
        int spot_number;
        fscanf(file, "Spot Number: %d\n License Plate: %19s\n Entry Time: %9s\n", &spot_number, lot -> vehicles[i].license_plate, lot -> vehicles[i].entry_time);
        lot -> vehicles[i].spot_number = spot_number;
    }

    fclose(file);
}

void free_parking_lot( ParkingLot *lot){
    if(lot != NULL){
        free(lot -> vehicles);
        free(lot);
    }
}
