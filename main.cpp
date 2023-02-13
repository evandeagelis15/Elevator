//
//  main.cpp
//  Elevator
//
//  Created by Evan DeAngelis on 2/8/23.
//

#include <iostream>
#include <vector>
#include <algorithm>

#define TIME_PER_FLOOR 10

using namespace std;

std::vector<int> FloorsToVisit = {};
std::vector<int> PrioritizedFloors = {};

///Sorts the floor vector into a vector representing the prioritzed travel plan
///returns an int representing the time it took to travel to all floors
int SortFloorVisits()
{
    //Store the starting floor
    const int start = FloorsToVisit.front();
    
    //Put in the first floor
    PrioritizedFloors.push_back(FloorsToVisit[0]);
    
    //sort the floors from lowest to highest
    sort(FloorsToVisit.begin(), FloorsToVisit.end());
    
    //Store the min and max
    const int min = FloorsToVisit.front();
    const int max = FloorsToVisit.back();

    //Case for one entry
    if (min == max)
        return 0;
    
    int direction = ((start - min) - (max-start) )/ abs((start - min) - (max - start));
    
    //Find the current index of the starting floor
    int StartIndex = 0;
    for (int i = 0; i<FloorsToVisit.size(); i++)
    {
        if (FloorsToVisit[i] == start)
        {
            StartIndex = i;
            break;
        }
    }

    //Loop through both halves of the list
    for (int i = 0; i<2; i++)
    {
        //Start at index either side of the starting index
        int j = StartIndex + direction;
        
        //Loop until both ends of the
        while (j>=0 && j <FloorsToVisit.size() && direction !=0 )
        {
            cout << j << endl;
            PrioritizedFloors.push_back(FloorsToVisit[j]);
            j+=direction;
        }
        
        //Switch directions
        direction *= -1;
    }
    
    //if there is a shorter distance between starting floor and lowest floor go that way
    if (direction)
    {
        return ((start-min)*2 + (max-start))*TIME_PER_FLOOR;
    }
    //else go to the higher floors first
    else
    {
        return((start-min)+ (max-start)*2)*TIME_PER_FLOOR;
    }
}

///Validate that input can be turned into an int representing a floor
void HandleInput(int argc, const char *argv[])
{
    //Loop through arguments
    for (int i = 1; i< argc; i++)
    {
        //Validate that all input are ints
        int floor = atoi(argv[i]);
        if (floor>0 )
        {
            //add input to vector of floors
            FloorsToVisit.push_back(floor);
        }
    }
}

int main(int argc, const char * argv[]) {
    //Make sure at least one floor was passed in
    if (argc <=1)
    {
        cerr<<"No input entered. Please pass floors numbers through command line."<<endl;
        return -1;
    }

    HandleInput(argc, argv);
    
    //if there are valid floors, sort visit order and calculate time
    if (FloorsToVisit.size()>0)
    {
        cout << SortFloorVisits()<< " ";
    }
    
    //Output Time taken to travel and the order of floors
    for (auto itr : PrioritizedFloors)
    {
        cout<<itr<<", ";
    }
    cout<<endl;
    return 0;
}
