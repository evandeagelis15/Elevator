//
//  main.cpp
//  Elevator
//
//  Created by Evan DeAngelis on 2/8/23.
//

#include <iostream>
#include <vector>
#include <chrono>

#define TIME_PER_FLOOR 10

using namespace std;

std::vector<int> FloorsToVisit = {};
std::vector<int> PrioritizedFloors = {};

///Sorts the floor vector into a vector representing the prioritzed travel plan
///returns an int representing the time it took to travel to all floors
int SortFloorVisits()
{
    //Store the starting floor
    const int Start = FloorsToVisit.front();
    
    //sort the floors from lowest to highest
    sort(FloorsToVisit.begin(), FloorsToVisit.end());
    
    //Store the min and max
    const int min =FloorsToVisit.front();
    const int max = FloorsToVisit.back();
    
    //Find the current index of the starting floor
    int StartIndex = 0;
    for (int i = 0; i<FloorsToVisit.size(); i++)
    {
        if (FloorsToVisit[i] == Start)
        {
            StartIndex = i;
            break;
        }
    }
    
    //if there is a shorter distance between starting floor and lowest floor go that way
    if ((Start - min) <= (max-Start))
    {
        //Loop backwards adding the floors to the prioritized vector
        for (int i = StartIndex; i>=0; i--)
        {
            PrioritizedFloors.push_back(FloorsToVisit[i]);
        }
        //loop forward to grab the remaining floors
        for (int i = StartIndex + 1; i<FloorsToVisit.size(); i++)
        {
            PrioritizedFloors.push_back(FloorsToVisit[i]);
        }
        return (Start-min)*2*TIME_PER_FLOOR + (max-Start)*TIME_PER_FLOOR;
    }
    //else go to the higher floors first
    else
    {
        //Loop forward adding the floors to the prioritized vector
        for (int i = StartIndex +1; i<FloorsToVisit.size(); i++)
        {
            PrioritizedFloors.push_back(FloorsToVisit[i]);
        }
        //loop backwards to grab the remaining floors
        for (int i = StartIndex; i>=0; i--)
        {
            PrioritizedFloors.push_back(FloorsToVisit[i]);
        }
        return(Start-min)*TIME_PER_FLOOR + (max-Start)*TIME_PER_FLOOR*2;
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
    int TimeTaken = 0;

    
    HandleInput(argc, argv);
    auto start = chrono::high_resolution_clock::now();
    
    //if there are valid floors, sort visit order and calculate time
    if (FloorsToVisit.size()>0)
    {
        TimeTaken = SortFloorVisits();
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << duration.count() << endl;
    
    //Output Time taken to travel and the order of floors
    cout<<TimeTaken<< " ";
    for (auto itr : PrioritizedFloors)
    {
        cout<<itr<<", ";
    }
    cout<<endl;
    return 0;
}
