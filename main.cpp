#include <iostream>
#include <fstream>
#include <cmath> 
#include "slist.h"
#include <stdlib.h>
using namespace std;

void quickSort(LinkedList::node* first, LinkedList::node* last);
void simpleSortTotal(LinkedList a, double rlong, double rlat, int reference);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void getDistance(LinkedList a, Airport austin);

int main()
{
    ifstream infile;
    int i=0;
    char cNum[32] ;
    LinkedList a;
    int   airportCount;
    string header;
    string l;
    int austinAirport = 0;
    infile.open ("airport-codes_US.csv", ifstream::in);
    Airport austin;
    if (infile.is_open()) {
        int   c=0;
        getline(infile, header, '\n');
        while (infile.good()) {
            Airport newData;
            infile.getline(newData.code, 256, ',');
            infile.getline(newData.type, 256, ',');
            infile.getline(newData.name, 256, ',');
            infile.getline(cNum, 256, ',');
            newData.longitude = atof(cNum);
            infile.getline(cNum, 256, ',');
            newData.latitude = atof(cNum);
            getline(infile, l, ',');
          getline(infile, l, ',');
          getline(infile, l, ',');
          infile.getline(newData.region, 256, ',');
            getline(infile, l, '\n');
            if (strcmp(newData.code, "KAUS") == 0) {
              austinAirport = c;
              austin = newData;
            }
            a.add(newData);
            i++ ;
            c++;
        }
        airportCount = c-1;
        infile.close();
        LinkedList::node* first = a.getFirst();
        LinkedList::node* last = a.getLast();
        getDistance(a, austin);
        quickSort(first, last);
        cout << "done" << endl;
        LinkedList::node* head = a.getFirst();
        LinkedList::node* max = head;
        while (head !=NULL) {
          if (head->distance > max->distance) {
            max = head;
          }
        
          head = head->next;
        }
        cout << "airports under 100km away: " << endl;
        LinkedList::node* nearbyHead = a.getFirst();
        int nearbyAirports = 0;
        while (nearbyHead != NULL) {
          //cout << "distance: " << nearbyHead->distance << endl;
          if (strcmp(nearbyHead->data.code, "KAUS") != 0 && nearbyHead->distance <= 160.934) {
            //if (strcmp(nearbyHead->data.type, "airport") == 0 || strcmp(nearbyHead->data.type, "small_airport") == 0) {
              cout << nearbyHead->data.code << endl;
              nearbyAirports++;
            //}
            //cout << nearbyHead->data.type << endl;
          }
          nearbyHead = nearbyHead->next;
        }
        cout << "farthest airport from austin: " << max->data.code << " distance: " << max->distance << endl;
        cout << "total under 100 mile airports: " << nearbyAirports << endl;
    }
    else{
        cout << "Error opening file";
    }
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

void getDistance(LinkedList a, Airport austin) {
  LinkedList::node* head = a.getFirst();
  while (head != NULL) {
    head->distance = distanceEarth(head->data.latitude, head->data.longitude, austin.latitude, austin.longitude);
    if (head->distance <= 160.934) {
      //cout << "get distance: " << head->data.code << " " << head->distance << endl;
    }
    head = head->next;
  }
}


 LinkedList::node* partition(LinkedList::node* first, LinkedList::node* last) {
  LinkedList::node* pivot = first;
  LinkedList::node* front = first;
  Airport temp;
  double dis;
  while (front != NULL && front != last) {
    if (front->distance < last->distance) {
      pivot = first;
      temp = first->data;
      dis  = first->distance;
      first->data = front->data;
      first->distance = front->distance;

      front->data = temp;
      front->distance = dis;
      first = first->next;
    }
    front = front->next;
  }
  temp = first->data;
  dis = first->distance;
  first->data = last->data;
  first->distance = last->distance;
  last->data = temp;
  last->distance = dis;
  return pivot;
}

void quickSort(LinkedList::node* first, LinkedList::node* last) {
  if (first == last) { 
      return; 
  } 
  LinkedList::node* pivot = partition(first, last); 

  if (pivot != NULL && pivot->next != NULL) { 
      quickSort(pivot->next, last); 
  } 

  if (pivot != NULL && first != pivot) { 
      quickSort(first, pivot); 
  } 
}

