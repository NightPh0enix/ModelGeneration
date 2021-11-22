#include <iostream>
#include <fstream> // the class declarations for file stream objects
#include <vector>
#include <math.h>
#include <string>

int dataPoints = 16; // no of different parameters/data in the DDA output 

std::vector<double> move_data(dataPoints,0.0); 
std::vector<double> distanceVector;
std::vector<double> x_vector;
std::vector<double> y_vector;
std::vector<double> z_vector;



double startDist;

double x_startDist;
double y_startDist;
double z_startDist;

double totalLength;


double x_moveDistance;
double y_moveDistance;
double z_moveDistance;
double e_moveDistance;

double accelStopTime;
double steadyTime;
double decelStartTime;
double moveTime;
double startVelocity;
double topVelocity;
double endVelocity;
int direction;
double extrusion;

double accel_last_dist;
double steady_last_dist;
double decel_last_dist;

int N1;
int N2;
int N3;



//int movesDone = 0;
// int x_movesDone = 0;
// int y_movesDone = 0;
// int z_movesDone = 0;
// int e_movesDone = 0;

double T1;
double T2;
double T3;

// double y_T1;
// double y_T2;
// double y_T3;

double accel_P;
double decel_P;
double T1_P;
double T2_P;
double T3_P;
double F_P;

// double y_accel_P;
// double y_decel_P;
// double y_T1_P;
// double y_T2_P;
// double y_T3_P;
// double y_F_P;

double f_s,F,f_1e,f_2e,f_e,f_3e;

double s_1e;
double s_2e;
// double s_1e_y;
// double s_2e_y;
// double s_1e_z;
// double s_2e_z;
// double s_1e_e;
// double s_2e_e;

double clockRate=937500.0;
double clocksToSecMultiplier=1/clockRate;
double acceleration = 5.6889e-10; //mm/cks^2
double deceleration;
double time_interval=0.01;




double convertTimeToSeconds(double time)
{
    time=time*clocksToSecMultiplier;
    return time;
}

double convertAccToSec(double accel)
{
    accel=accel*clockRate*clockRate;
    return accel;
}

double convertVelToSec(double vel)
{
    vel=vel*clockRate;
    return vel;
}



/***************************************************************************************************************************************/
/***************************************************************************************************************************************/
/***************************************************************************************************************************************/
std::vector<double> make_distanceVector()
{
    double tau = 0;

    std::vector<int> kVector;

    for (int k=0; k<=N1+N2+N3;k++)
    {
        if (k<=N1)
        {
            tau = k*time_interval;
            double dist = startVelocity * tau + 0.5 * accel_P * tau * tau;
            x_vector.push_back(x_startDist+(x_moveDistance/totalLength)*dist);
            y_vector.push_back(y_startDist+(y_moveDistance/totalLength)*dist);
            z_vector.push_back(z_startDist+(z_moveDistance/totalLength)*dist);

            std::cout<<"A "<<"X = " <<x_startDist+(x_moveDistance/totalLength)*dist<<" Y = " <<y_startDist+(y_moveDistance/totalLength)*dist<<" Z = "<<z_startDist+(z_moveDistance/totalLength)*dist<<"\n";
        }

        if (k>=N1+1 && k<=N2+N2)
        {
            tau = k*time_interval;
            double dist = s_1e + F_P * (tau-N1*time_interval);
            x_vector.push_back(x_startDist+(x_moveDistance/totalLength)*dist);
            y_vector.push_back(y_startDist+(y_moveDistance/totalLength)*dist);
            z_vector.push_back(z_startDist+(z_moveDistance/totalLength)*dist);
            std::cout<<"A "<<"X = " <<x_startDist+(x_moveDistance/totalLength)*dist<<" Y = " <<y_startDist+(y_moveDistance/totalLength)*dist<<" Z = "<<z_startDist+(z_moveDistance/totalLength)*dist<<"\n";
        }

        else if (k>=N1+N2+1)
        {
            tau = k*time_interval;
            double dist = s_2e + F_P * (tau-(N1+N2)*time_interval) + 0.5 * decel_P * (tau-(N1+N2)*time_interval) * (tau-(N1+N2)*time_interval);
            distanceVector.push_back(dist); 
            x_vector.push_back(x_startDist+(x_moveDistance/totalLength)*dist);
            y_vector.push_back(y_startDist+(y_moveDistance/totalLength)*dist);
            z_vector.push_back(z_startDist+(z_moveDistance/totalLength)*dist); 
            std::cout<<"A "<<"X = " <<x_startDist+(x_moveDistance/totalLength)*dist<<" Y = " <<y_startDist+(y_moveDistance/totalLength)*dist<<" Z = "<<z_startDist+(z_moveDistance/totalLength)*dist<<"\n";         
        }
    }

    return distanceVector;
}

void calculateTimeIntervals()
{
    // CALCULATE T1 T2 T3

    T1 = (F - f_s)/acceleration;

    double onebyf = 1/F;
    double oneby2a = 1/(2*acceleration);
    double oneby2d = 1/(2*deceleration);
    double Fsquare = F * F;
    double feSqByTwoD = f_e * f_e *oneby2d;
    double fsSqByTwoA = startVelocity * startVelocity*oneby2a;

    T2 = onebyf * (totalLength - (oneby2a-oneby2d)*Fsquare - (feSqByTwoD-fsSqByTwoA));
    T3 = (f_e - F)/deceleration;

    // std::cout<<"f_s " <<f_s <<"\n";
    // std::cout<<"F " <<F <<"\n";
    // std::cout<<"accel "<<acceleration<<"\n";
    // std::cout<<"T1 : " <<T1<<"\n";
    // std::cout<<"T2 : " <<T2<<"\n";
    // std::cout<<"T3 : " <<T3<<"\n";

    // CALCULATE T1` T2` T3`

    N1 = ceil(T1/time_interval);
    N2 = ceil(T2/time_interval);
    N3 = ceil(T3/time_interval);

    // std::cout<<"N1 : " <<N1<<"\n";
    // std::cout<<"N2 : " <<N2<<"\n";
    // std::cout<<"N3 : " <<N3<<"\n";

    T1_P = N1*time_interval;
    T2_P = N2*time_interval;
    T3_P = N3*time_interval;

    // std::cout<<"T1_P : " <<T1_P<<"\n";
    // std::cout<<"T2_P : " <<T2_P<<"\n";
    // std::cout<<"T3_P : " <<T3_P<<"\n";

}




void calculateModifiedParameters(std::vector<double> d_vector)
{

    F_P = (2 * totalLength - f_s * T1_P - f_e * T3_P) / (T1_P + 2*T2_P + T3_P);
    accel_P = (F_P - f_s)/T1_P;

    if (accel_P == -1.0 / 0.0) // checking for minus infinity 
    {
        accel_P = 0;
    }

    decel_P = (f_e - F_P)/T3_P;

    // if (move_data[dataPoints-1]==1) // +ve direction move 
    // {
        // if (movesDone == 0)
        // {
        //     s_1e = f_s * T1_P + 0.5 * accel_P * T1_P * T1_P;
        // }
        // else 
        // {
        //     s_1e =  distanceVector.back() + f_s * T1_P + 0.5 * accel_P * T1_P * T1_P;
        // }

        s_1e = f_s * T1_P + 0.5 * accel_P * T1_P * T1_P;

        // if (s_1e==0)
        // {
        //     s_1e = distanceVector.back();
        // }

        s_2e = s_1e + F_P*T2_P;
    //}    
}


void eraseFileLine(std::string path, std::string eraseLine) 
{
    std::string line;
    std::ifstream fin;
    
    fin.open(path);
    // contents of path must be copied to a temp file then
    // renamed back to the path file
    std::ofstream temp;
    temp.open("temp.txt");

    while (getline(fin, line)) 
    {
        // write all lines to temp other than the line marked for erasing
        if (line != eraseLine)
        {
            temp << line << std::endl;
        }        
    }

    temp.close();
    fin.close();

    // required conversion for remove and rename functions
    const char * p = path.c_str();
    remove(p);
    rename("temp.txt", p);
}

bool x_fmd = 0;
bool y_fmd = 0;
bool z_fmd = 0;

int main ()
{
    
    bool moveAvailable = 0;
    double num;
    int iteratorPosition = 1;

    int movesDone =0;

    acceleration = convertAccToSec(acceleration);
    deceleration = acceleration*(-1);
    
    // eraseFileLine("Input.txt","ok "); // remove 'ok' from file 
    std::ifstream my_input_file("Input.txt"); // an input file stream object
    std::ofstream my_output_file("Output.txt"); // an input file stream object
    
    if (my_input_file.is_open()) 
    {
        std::cout<<"File Opened Successfully\n";
        std::string line;

        while (my_input_file >> num)
        {
           // std::cout<<"Data "<<num<<"\n";
            switch(iteratorPosition) 
            {
                case 1 :
                    move_data[0] = num;
                    break;

                case 2 :
                    move_data[1] = num;
                    break;
                    
                case 3 :
                    move_data[2] = num;
                    break;

                case 4 :
                    move_data[3] = num;
                    break;

                case 5 :
                    move_data[4] = num;
                    break;

                case 6 :
                    move_data[5] = num;
                    break;

                case 7 :
                    move_data[6] = num;
                    break;

                case 8 :
                    move_data[7] = num;
                    break;

                case 9 :
                    move_data[8] = num;
                    break;

                case 10 :
                    move_data[9] = num;
                    break;                   
                case 11 :
                    move_data[10] = num;
                    break;
                    
                case 12 :
                    move_data[11] = num;
                    break;
                case 13 :
                    move_data[12] = num;
                    break;
                case 14 :
                    move_data[13] = num;
                    break;
                case 15 :
                    move_data[14] = num;
                    break;

                case 16 :
                    move_data[15] = num;
                    break;
                     
                default :
                    std::cout << "Invalid iteratorPosition" << std::endl;
            }

            if (iteratorPosition==dataPoints) // there are 8 nums in a line
            {
                moveAvailable = 1;
                std::cout<<"Move available "<<"\n";
            }

            if (moveAvailable)
            {
                //std::cout<<"Moves Done "<<movesDone<< "\n";

                totalLength = move_data[0];

                x_startDist = move_data[1];
                y_startDist = move_data[2];
                z_startDist = move_data[3];

                x_moveDistance = move_data[4];
                y_moveDistance = move_data[5];
                z_moveDistance = move_data[6];

                accelStopTime = move_data[7];
                steadyTime = move_data[8];
                decelStartTime = move_data[9];
                moveTime = move_data[10];

                startVelocity = move_data[11];
                topVelocity = move_data[12];
                endVelocity = move_data[13]; 
                
                direction = move_data[14];
                extrusion = move_data[15];

                startVelocity = convertVelToSec(startVelocity);
                endVelocity = convertVelToSec(endVelocity);
                topVelocity = convertVelToSec(topVelocity);

                accelStopTime = convertTimeToSeconds(accelStopTime);
                steadyTime = convertTimeToSeconds(steadyTime);
                decelStartTime = convertTimeToSeconds(decelStartTime);
                moveTime = convertTimeToSeconds(moveTime); 

                f_s = startVelocity;
                f_e = endVelocity;
                F = topVelocity;





                calculateTimeIntervals(); 
                calculateModifiedParameters(distanceVector); 
                distanceVector = make_distanceVector();
                
                movesDone++;

                // if (movesDone>0)
                // {
                //     startDist = distanceVector.back();
                // }
    
                // std::cout<<"accelStopTime : "<<accelStopTime<<"\n";
                // std::cout<<"steadyTime : "<<steadyTime<<"\n";
                // std::cout<<"decelStartTime : "<<decelStartTime<<"\n";
                // std::cout<<"moveTime : "<<moveTime<<"\n";
                // std::cout<<"startVelocity : "<<startVelocity<<"\n";
                // std::cout<<"startDist : "<<startDist<<"\n";
                // std::cout<<"setup.acceleration : "<<acceleration<<"\n";
                // std::cout<<"T1 : " <<T1<<"\n";
                // std::cout<<"T2 : " <<T2<<"\n";
                // std::cout<<"T3 : " <<T3<<"\n";
                // std::cout<<"F = f_1e = f_2e " <<F <<"\n";
                // std::cout<<"s_1e : "<<s_1e<<"\n";
                // std::cout<<"s_2e : "<<s_2e<<"\n";
                
            }

            iteratorPosition++;
            if (iteratorPosition>dataPoints)
            {
                iteratorPosition = 1;
                moveAvailable = 0;
            }
        }
    }
    std::cout<<"********************************************\n";


    for (int c=0; c<=x_vector.size()-1;c++)
    {
        //std::cout<<"DIS : "<<distanceVector[c]<<"\n";
        
    //     // x_vector.push_back(x_startDist+(x_moveDistance/totalLength)*distanceVector[c]); //TODO : Add the start distance refer to notes Chi
    //     // y_vector.push_back((y_startDist+(y_moveDistance/totalLength)*distanceVector[c]));
    //     // z_vector.push_back(z_startDist+(z_moveDistance/totalLength)*distanceVector[c]);
            my_output_file <<x_vector[c]<<" "<<y_vector[c]<<" "<<z_vector[c]<<" "<<extrusion<<"\n"; 
    }
    
    my_output_file.close();    
}
