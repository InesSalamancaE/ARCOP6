#include "recount.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <omp.h>

/**
 * @brief recount::recount empty constructor
 */
recount::recount()
{
    this->code = -1;
}

//TO_DO: all methods of the class
recount::recount(vector<string> data){
    this->code = atoi(data[0].c_str());
    this->municipal = data[1];
    this->zone = atoi(data[2].c_str());
    this->section = atoi(data[3].c_str());
    this->name = atoi(data[4].c_str());
    this->census = atoi(data[5].c_str());
    this->abstentions = atoi(data[6].c_str());
    this->v_cast = atoi(data[7].c_str());
    this->v_invalid = atoi(data[8].c_str());
    this->v_valid = atoi(data[9].c_str());
    this->v_white = atoi(data[10].c_str());
}
//GETTERS

int recount::get_v_cast(){
    return this->v_cast;
}
int recount::get_abstentions(){
    return this->abstentions;
}
int recount::get_census(){
    return this->census;
}


/**
     * @brief Print information of the
     */
void recount::print(){
    cout<<"Code: " << this->code <<endl;
    cout<<"Municipal: " << this->municipal <<endl;
    cout<<"Zone: " << this->zone <<endl;
    cout<<"Section: " << this->section <<endl;
    cout<<"Name: " << this->name <<endl;
    cout<<"Census: " << this->census <<endl;
    cout<<"Abstentions: " << this->abstentions <<endl;
    cout<<"v_cast: " << this->v_cast <<endl;
    cout<<"v_invalid: " << this->v_invalid <<endl;
    cout<<"v_valid: " << this->v_valid <<endl;
    cout<<"V_WHITE: " << this->v_white <<endl;
};


//SETTERS
/**
     * @brief recount::set_p_participation SETTER
     * @param p_participation value between 0 and 100
     */
void recount::set_p_participation(float p_participation){
    this->p_participation = p_participation;
}

/**
     * @brief recount::set_p_abstention SETTER
     * @param p_abstention value between 0 and 100
     */
void recount::set_p_abstention(float p_abstention){
    this->p_abstention = p_abstention;
}



