#ifndef SFMLDEMO_POINT_H
#define SFMLDEMO_POINT_H

#include <SFML/Graphics.hpp>
#include <iostream>

struct point{
    short id;
    int weight;
    short related_id;
    int top;
    int right;
    int bot;
    int left;
    point *next;
    int get_direction(int id){
        switch(id){
            case 0:
                return top;
            case 1:
                return right;
            case 2:
                return bot;
            case 3:
                return left;
        }
    }
    point *search(int n){
        point *nextWanted = next;
        if( n == 0 ){
            return nextWanted;
        }
        return nextWanted->search( n - 1 );
    }
};

point *from_head(int n, point *index){
    point *bufor = index->next;
    for(int i =0; i < n; i++){
        bufor = bufor->next;
    }
    return bufor;
}

int const numberOfPoints = 100;
int const pointsInRow = 10;
int const convertedWidth = 4;
int const convertedHeight = 30;

#endif