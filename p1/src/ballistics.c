/**
 @author David Hines
 @file ballistics.c
 
 This program calculates the ballistics table for a given projectile
 based on the initial velocity as entered at the console by the user.
 The program will calculate the time the projectile is in flight as
 well as the distance traveled by the projectile at varying angles
 from 0 to 90 degrees.  The results of the calculations are printed
 to the console in a formatted table.
  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** Maximum angle of the projectile */
#define MAX_ANGLE 90
/** Acceleration of gravity */
#define GRAVITY 9.81


/**
 This function calculates the flight time for the projectile based
 on the angle of travel and returns the result as a double to the 
 calling function.
 @param angle the initial angle of the projectile begins travelling
 @param v0 the velocity of the projectile
 @return the flight time of the projectile as a double
  */
double flightTime( int angle, double v0 )
{   double radians = angle * M_PI / 180;
    double time = 2 * v0 * sin(radians) / GRAVITY;
    return time;
}

/**
 The function prints a table row with the ballistics calculations for
 the projectile which is used to build a formatted table.  
 @param angle the initial angle of the projectile begins travelling
 @param v0 the velocity of the projectile
 @param t the flight time of the projectile
  */
void tableRow( int angle, double v0, double t )
{
    double radians = angle * M_PI / 180;
    
    double d = v0 * t * cos(radians);
    
    printf("%10d%s", angle, " |");
    printf("%11.3lf%s", v0, " |");
    printf("%11.3lf%s", t, " |");
    printf("%11.3lf\n", d);
    
}

/**
 The main function for the ballistics program that creates the initial
 structure for the ballistics table and calls the other functions in
 order to complete the table based on the user input.
 
  */
int main()
{
    
    printf("V0: ");
    double val;
    int matches = scanf("%lf", &val);

    printf("\n");
    printf("%12s", "angle |");
    printf("%13s", "v0 |");
    printf("%13s", "time |");
    printf("%11s\n", "distance");
    printf("-----------+------------+------------+-----------\n");

    if (matches == 1) {
        for(int i = 0; i <= MAX_ANGLE; i+=5){
            tableRow(i, val, flightTime(i, val));
        }  
    } else {
        printf("Not a valid entry!");
    }

     
    
    return EXIT_SUCCESS;
}
