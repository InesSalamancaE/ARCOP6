#ifndef RECOUNT_H
#define RECOUNT_H

#include <iostream>
#include <vector>
using namespace std;

class recount
{
public:
    //CONSTRUCTORS

    recount();

    /**
     * @brief recount::recount constructor
     * @param Vector of 11 elements which correspond with a line of the csv file
     */
    recount(vector<string> data);
    //GETTERS
    int get_v_cast();
    int get_abstentions();
    int get_census();
    /**
     * @brief Print information of the
     */
    void print();

    //SETTERS
    /**
     * @brief recount::set_p_participation SETTER
     * @param p_participation value between 0 and 100
     */
    void set_p_participation(float p_participation);

    /**
     * @brief recount::set_p_abstention SETTER
     * @param p_abstention value between 0 and 100
     */
    void set_p_abstention(float p_abstention);


private:
    int code; //unique identifier
    string municipal; //name of the municipal place
    int zone; //number of the zone in the municipal
    int section; //number of the section in the zone
    char name; //character to identify the voting table
    // census = v_cast + abstentions
    int census; //number of people registered at the voting table
    int abstentions; //number of people who have not voted
    int v_cast; //number of people who have voted
    int v_invalid; //number of invalid votes
    int v_valid; //number of valid votes
    int v_white; //number of white votes

    //TO_DO: variables to calculate
    float p_participation; //percentage of participation
    float p_abstention; //percentage of abstention
};

#endif // RECOUNT_H
