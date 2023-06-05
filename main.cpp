#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <recount.h>
#include <algorithm>
#include <cstring>
#include <sys/time.h>
#include <omp.h>
//#include <recount.cpp>
#include <QDir>

using namespace std;

//PROTOTYPES
void calculate_p_participation(vector<recount> content, string mode="sequential");
void calculate_p_abstention(vector<recount> content, string mode="sequential");
int calculate_total_census(vector<recount> content, string comp_mode="sequential");
int calculate_total_abstention(vector<recount> content, string comp_mode="sequential");
recount get_min_census(vector<recount> content, string comp_mode="sequential");
recount get_max_census(vector<recount> content, string comp_mode="sequential");
float get_mean_p_participation(vector<recount> content, string mode="sequential");
float get_mean_p_abstention(vector<recount> content, string mode="sequential");

//MAIN
int main()
{
    // It can be used to know the execution path
    //cout << "[EXECUTION PATH]: " << QDir::currentPath().toStdString() + '\n';
    // Path and name of the csv file
    string fname = "D:/Inespelirroja/Documents/UniLeon/Asignaturas/Arquitectura de computadores/Practica/P6/project_base/elecciones_navarra_1999.csv";

    // Init variables
    vector<recount> content;
    vector<string> row;
    recount read_recount = recount();
    int count_row = 0;
    string line, word;


    //Read document
    ifstream file (fname, ios::in);
    if(file.is_open())
    {
        //Read each row of the file
        while(getline(file, line))
        {
            row.clear(); // Clear row array
            stringstream stream(line);
            // Divide the line by the separator (;) and each value is an element of the array row
            while(getline(stream, word, ';'))
                row.push_back(word);
            if (count_row>0){ //First row of the document correspond to the header
                // TO_DO: CREATE recount object and append to content
                //Create recount object
                read_recount = recount(row);
                //recount recountObject(row);
                content.push_back(read_recount);

                //read_recount.print(); //To see the information uncomment this line
            }

            count_row++;

        }
        cout<<"[OK]: "<< count_row << " lines read from the file and added to the list of contents" << "\n";
    }
    else{
        cout<<"[ERROR]: Could not open the file, check the file path\n";
    }

    //TO_DO: CALL TO FUNCTIONS AND MEASURE TIMES
    //Secuencial
    /*struct timeval begin, end;
    double wt1=0,wt2 = 0;
    wt1=omp_get_wtime();
    gettimeofday(&begin, 0);

*/
    //Sequencial------------------------------------------------------------------------------------------------------

    cout<<"Total census (sequential): " << calculate_total_census(content, "sequential")<<endl;
    cout<<" "<<endl;

    cout<<"Total abstention (sequential): " << calculate_total_abstention(content, "sequential")<<endl;
    cout<<" "<<endl;

    recount recountMiSeq = get_min_census(content, "sequential");
    cout<<" "<<endl;

    recount recountMxSeq = get_max_census(content, "sequential");
    cout<<" "<<endl;

    cout<<"Mean participation (sequential): " << get_mean_p_participation(content, "sequential")<<endl;
    cout<<" "<<endl;


    cout<<"Mean abstention (sequential): " << get_mean_p_abstention(content, "sequential")<<endl;
    cout<<" "<<endl;


    //Paralel-----------------------------------------------------------------------------------------------------------
    cout<<"Total census (parallel): " << calculate_total_census(content, "parallel")<<endl;
    cout<<" "<<endl;

    cout<<"Total abstention (parallel): " << calculate_total_abstention(content, "parallel")<<endl;
    cout<<" "<<endl;

    recount recountMiPa = get_min_census(content, "parallel");
    cout<<" "<<endl;

    recount recountMxPa = get_max_census(content, "parallel");
    cout<<" "<<endl;

    cout<<"Mean participation (parallel): " << get_mean_p_participation(content, "parallel")<<endl;
    cout<<" "<<endl;


    cout<<"Mean abstention (parallel): " << get_mean_p_abstention(content, "parallel")<<endl;
    cout<<" "<<endl;


    return 0;
}

//TO_DO: FUNCTIONS

/**
 * @brief calculate_total_census calculate total number of census people
 * @param content vector of recount elements
 * @param comp_mode is the computational mode, it can be: sequential or parallel
 * @return number of census people in total
 */
int calculate_total_census(vector<recount> content, string comp_mode){
        // Init variables
        recount r = recount();
        struct timeval begin, end;
        double wt1=0,wt2 = 0;
        int total = 0;
        int c=0;

        #ifdef _OPENMP
        wt1=omp_get_wtime();
        #endif
        gettimeofday(&begin, 0);

        // Sequential mode
        if(comp_mode=="sequential"){

            // TO_DO: calculate total in sequential mode
        for(int i = 0; i < (int)content.size(); i++){
            total = total + content.at(i).get_census();
            }


        // Parallel mode
        }else if(comp_mode=="parallel"){

            // TO_DO: calculate total in parallel mode
            for(int i = 0; i < (int)content.size(); i++){
                c = content.at(i).get_census();
                total = total + c;
            }


        }else{
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }
        gettimeofday(&end, 0);
        #ifdef _OPENMP
        wt2=omp_get_wtime();
        #endif

        //Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds*1e-6 + microseconds; //in microseconds
        printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);

        //#ifdef _OPENMP
        double omp_elapse = (wt2-wt1)*1e-6;
        printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), omp_elapse);
        //#endif

        return total;
}

//PROTOTYPES
void calculate_p_participation(vector<recount> content, string mode){
        // Init variables
        recount r = recount();
        struct timeval begin, end;
        double wt1 = 0,wt2 = 0;
        float participation = 0;

        #ifdef _OPENMP
        wt1=omp_get_wtime();
        #endif
        gettimeofday(&begin, 0);
        // Sequential mode
        if(mode=="sequential"){

            // TO_DO: calculate total in sequential mode
            for(int i = 0; i < (int)content.size(); i++){
                participation = (content.at(i).get_v_cast()*100)/content.at(i).get_census();
                content.at(i).set_p_participation(participation);
            }


            // Parallel mode
        }else if(mode=="parallel"){

            // TO_DO: calculate total in parallel mode
            for(int i = 0; i < (int)content.size(); i++){
                participation = (content.at(i).get_v_cast()*100)/content.at(i).get_census();
                content.at(i).set_p_participation(participation);
            }


        }else{
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }
        gettimeofday(&end, 0);

        #ifdef _OPENMP
        wt2=omp_get_wtime();
        #endif

        //Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds*1e-6 + microseconds; //in microseconds
        printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, mode.c_str(), elapsed);
        double omp_elapse = (wt2-wt1)*1e-6;
        printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, mode.c_str(), omp_elapse);



}
void calculate_p_abstention(vector<recount> content, string mode){
        // Init variables
        recount r = recount();
        struct timeval begin, end;
        double wt1 = 0,wt2 = 0;
        float participation = 0;


        #ifdef _OPENMP
        wt1=omp_get_wtime();
        #endif

        gettimeofday(&begin, 0);
        // Sequential mode
        if(mode=="sequential"){

            // TO_DO: calculate total in sequential mode
            for(int i = 0; i < (int)content.size(); i++){
                participation = (content.at(i).get_abstentions()*100)/content.at(i).get_census();
                content.at(i).set_p_abstention(participation);
            }


            // Parallel mode
        }else if(mode=="parallel"){

            // TO_DO: calculate total in parallel mode
            for(int i = 0; i < (int)content.size(); i++){
                participation = (content.at(i).get_abstentions()*100)/content.at(i).get_census();
                content.at(i).set_p_abstention(participation);
            }



        }else{
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }
        gettimeofday(&end, 0);
        #ifdef _OPENMP
        wt2=omp_get_wtime();
        #endif

        //Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds*1e-6 + microseconds; //in microseconds
        printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, mode.c_str(), elapsed);
        double omp_elapse = (wt2-wt1)*1e-6;
        printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, mode.c_str(), omp_elapse);


}
//int calculate_total_census(vector<recount> content, string comp_mode="sequential");
int calculate_total_abstention(vector<recount> content, string comp_mode){
        // Init variables
        recount r = recount();
        struct timeval begin, end;
        double wt1 = 0,wt2 = 0;
        int a =0;
        int total = 0;

        #ifdef _OPENMP
        wt1=omp_get_wtime();
        #endif
        gettimeofday(&begin, 0);

        // Sequential mode
        if(comp_mode=="sequential"){

            // TO_DO: calculate total in sequential mode
            for(int i = 0; i < (int)content.size(); i++){
                total = total + content.at(i).get_abstentions();
            }


            // Parallel mode
        }else if(comp_mode=="parallel"){

            // TO_DO: calculate total in parallel mode
            for(int i = 0; i < (int)content.size(); i++){
                a = content.at(i).get_abstentions();
                total = total + a;
            }

        }else{
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }
        gettimeofday(&end, 0);
        #ifdef _OPENMP
        wt2=omp_get_wtime();
        #endif

        //Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds*1e-6 + microseconds; //in microseconds
        printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);
        double omp_elapse = (wt2-wt1)*1e-6;
        printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), omp_elapse);
        return total;
}
recount get_min_census(vector<recount> content, string comp_mode){
        // Init variables
        recount r = recount();
        struct timeval begin, end;
        double wt1 = 0,wt2 = 0;
        int minCensus = 100;

        #ifdef _OPENMP
        wt1=omp_get_wtime();
        #endif
        gettimeofday(&begin, 0);
        // Sequential mode
        if(comp_mode=="sequential"){

            // TO_DO: calculate total in sequential mode
            for(int i = 0; i < (int)content.size(); i++){
                if (content[i].get_census() < minCensus){
                    minCensus = content.at(i).get_census();;
                    r = content.at(i);
                }
            }
            r.print();



            // Parallel mode
        }else if(comp_mode=="parallel"){

            // TO_DO: calculate total in parallel mode

            for(int i = 0; i < (int)content.size(); i++){
                int c = content.at(i).get_census();
                if (c < minCensus){
                    minCensus = c;
                r = content.at(i);
                }
            }
            r.print();

        }else{
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }
        gettimeofday(&end, 0);
        #ifdef _OPENMP
        wt2=omp_get_wtime();
        #endif

        //Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds*1e-6 + microseconds; //in microseconds
        printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);
        double omp_elapse = (wt2-wt1)*1e-6;
        printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), omp_elapse);

        return r;


}
recount get_max_census(vector<recount> content, string comp_mode){
        // Init variables
        recount r = recount();
        struct timeval begin, end;
        double wt1 = 0,wt2 = 0;
        int maxCensus = 0;

        #ifdef _OPENMP
        wt1=omp_get_wtime();
        #endif
        gettimeofday(&begin, 0);
        // Sequential mode
        if(comp_mode=="sequential"){

            // TO_DO: calculate total in sequential mode
            for(int i = 0; i < (int)content.size(); i++){
                if (content.at(i).get_census() > maxCensus){
                maxCensus = content.at(i).get_census();;
                r = content.at(i);
                }
            }

            r.print();

            // Parallel mode
        }else if(comp_mode=="parallel"){

            // TO_DO: calculate total in parallel mode
            for(int i = 0; i < (int)content.size(); i++){
                int c = content.at(i).get_census();
                if (c > maxCensus){
                    maxCensus = c;
                r = content.at(i);
                }
            }
            r.print();


        } else {
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }

        gettimeofday(&end, 0);
        #ifdef _OPENMP
        wt2=omp_get_wtime();
        #endif

        //Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds*1e-6 + microseconds; //in microseconds
        printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), elapsed);
        double omp_elapse = (wt2-wt1)*1e-6;
        printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, comp_mode.c_str(), omp_elapse);

        return r;
}
float get_mean_p_participation(vector<recount> content, string mode){
        // Init variables
        recount r = recount();
        struct timeval begin, end;
        double wt1 = 0,wt2 = 0;
        float voted;
        float total;
        float result = 0;

        #ifdef _OPENMP
        wt1=omp_get_wtime();
        #endif
        gettimeofday(&begin, 0);
        // Sequential mode
        if(mode=="sequential"){

            // TO_DO: calculate total in sequential mode
            for(int i = 0; i < (int)content.size(); i++){
                voted = voted + content.at(i).get_v_cast();
                total = total + content.at(i).get_census(); //NOT SURE --------------------------------------------------------------------
            }

            result = voted/total;

            // Parallel mode
        }else if(mode=="parallel"){

            // TO_DO: calculate total in sequential mode
            for(int i = 0; i < (int)content.size(); i++){
                int vC = content.at(i).get_census();
                voted = voted + vC;
                total = total + vC; //NOT SURE --------------------------------------------------------------------
            }

            result = voted/total;


        }else{
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }
        gettimeofday(&end, 0);
        #ifdef _OPENMP
        wt2=omp_get_wtime();
        #endif

        //Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds*1e-6 + microseconds; //in microseconds
        printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, mode.c_str(), elapsed);
        double omp_elapse = (wt2-wt1)*1e-6;
        printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, mode.c_str(), omp_elapse);

        return result;
}
float get_mean_p_abstention(vector<recount> content, string mode){
        // Init variables
        recount r = recount();
        struct timeval begin, end;
        double wt1 = 0,wt2 = 0;
        float noVoted;
        float total;
        float result = 0;

        #ifdef _OPENMP
        wt1=omp_get_wtime();
        #endif
        gettimeofday(&begin, 0);
        // Sequential mode
        if(mode=="sequential"){

            // TO_DO: calculate total in sequential mode
            for(int i = 0; i < (int)content.size(); i++){
                noVoted = noVoted + content.at(i).get_abstentions();
                total = total + content.at(i).get_census(); //NOT SURE --------------------------------------------------------------------
            }

            result = noVoted/total;

            // Parallel mode
        }else if(mode=="parallel"){

            // TO_DO: calculate total in sequential mode
            for(int i = 0; i < (int)content.size(); i++){
                int gA = content.at(i).get_census();
                noVoted = noVoted + gA;
                total = total + gA; //NOT SURE --------------------------------------------------------------------
            }

            result = noVoted/total;


        }else{
            printf("[ERROR]: Not valid computational mode in %s. Only: sequential and parallel\n", __FUNCTION__);
            throw ("ERROR");
        }
        gettimeofday(&end, 0);
        #ifdef _OPENMP
        wt2=omp_get_wtime();
        #endif

        //Print results
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds*1e-6 + microseconds; //in microseconds
        printf("[CPU_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, mode.c_str(), elapsed);
        double omp_elapse = (wt2-wt1)*1e-6;
        printf("[OMP_TIME]: %s \tComputational mode: %s  \t%.2f microseconds \n", __FUNCTION__, mode.c_str(), omp_elapse);

        return result;
}
