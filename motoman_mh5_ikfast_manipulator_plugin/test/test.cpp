/*
 * test to see if IKfast gives the same solution as FK 
 * To compile, run:
 * g++ -lstdc++ -llapack -o compute test.cpp -lrt
 * (need to link with 'rt' for gettime(), it must come after the source file name)
 *


*/
 
#define IKFAST_HAS_LIBRARY // Build IKFast with API functions
#define IKFAST_NO_MAIN // Don't include main() from IKFast

#include "motoman_mh5_manipulator_ikfast_solver.cpp"

//----------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> // for clock_gettime()

float SIGN(float x);
float NORM(float a, float b, float c, float d);

#define IKREAL_TYPE IkReal // for IKFast 56,61

int main(int argc, char** argv)
{
    IKREAL_TYPE eerot[9],eetrans[3];

    unsigned int num_of_joints = GetNumJoints();
    unsigned int num_free_parameters = GetNumFreeParameters();
 
    std::string cmd;
    if (argv[1]) cmd = argv[1];


    if (cmd.compare("ikcompare") == 0) // generate random joints and check ik soltution against fk
    {

        IkSolutionList<IKREAL_TYPE> solutions;
        std::vector<IKREAL_TYPE> vfree(num_free_parameters);

        srand( (unsigned)time(0) ); // seed random number generator
        float min = -3.14;
        float max = 3.14;
        float rnd;

        IKREAL_TYPE joints[num_of_joints];

        timespec start_time, end_time;
        unsigned int elapsed_time = 0;
        unsigned int sum_time = 0;

        unsigned int num_of_tests = 1000000; 

        unsigned int pass_cases = 0; 
        unsigned int failed_cases = 0; 
        unsigned int wrong_cases = 0; 
        float threshold = pow(10.0,-6);
        
        for (unsigned int i=0; i < num_of_tests; i++)
        {

            for (unsigned int i=0; i<num_of_joints; i++)
            {
                float rnd = (float)rand() / (float)RAND_MAX;
                joints[i] = min + rnd * (max - min);
            }

            ComputeFk(joints, eetrans, eerot);

            bool bSuccess = ComputeIk(eetrans, eerot, vfree.size() > 0 ? &vfree[0] : NULL, solutions);
            if( !bSuccess ) {
                failed_cases = failed_cases + 1;
            printf("Joint angles:  ");
            for (unsigned int l=0; l<num_of_joints; l++)
            {
                printf("%f  ", joints[l] );
            }
            printf("\n");
            }
            else{

            unsigned int num_of_solutions = (int)solutions.GetNumSolutions();

            std::vector<IKREAL_TYPE> solvalues(num_of_joints);
            

            for(unsigned int k = 0; k < num_of_solutions; ++k) {
                const IkSolutionBase<IKREAL_TYPE>& sol = solutions.GetSolution(k);
                int this_sol_free_params = (int)sol.GetFree().size(); 
                std::vector<IKREAL_TYPE> vsolfree(this_sol_free_params);

                sol.GetSolution(&solvalues[0],vsolfree.size()>0?&vsolfree[0]:NULL);
                float error = 0.0;
		for( std::size_t j = 0; j < solvalues.size(); ++j){
                    error = error + abs(solvalues[j] - joints[j]);
                   } 
                if (error <= threshold){
                    pass_cases = pass_cases + 1;
                    break;
               } else if(k == num_of_solutions-1 ){
                    wrong_cases = wrong_cases + 1;
/*
            printf("Joint angles:  ");
            for (unsigned int l=0; l<num_of_joints; l++)
            {
                printf("%f  ", joints[l] );
            }
            printf("\n");
*/
               }

            }

        } }// endfor

        printf("number of cases \n passed: %f \n failed: %f \n wrong: %f \n", (float)pass_cases, (float)failed_cases, (float)wrong_cases);

        return 1;
} else { 

            printf("\n "
                   "Usage: \n\n "
                   "         ./compute ikcompare \n\n"
                   "         For fixed number of iterations, generates random joint angles, then  \n"
                   "         calculates fk, calculates ik and compare the ik performance. %u \n\n", num_of_joints-1 );
            return 1;
}

    return 0;
}



