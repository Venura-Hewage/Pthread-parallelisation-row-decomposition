#include <iostream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <pthread.h>
#include <stdio.h>
using namespace std::chrono;
using namespace std;
int Matrix_Size = 100000000;
#define num_of_pieces 100



struct thread_data {

  int  id;
  int start;
  int end;
  int  *v1;
  int  *v2;
  int  *v3;
 

};



void randomVector(int vector[], int size)
{
    for (int i = 0; i < size; i++)
    {
       
        vector[i] = rand() % 100;
    }
}

//External Code Citation [1]
//Title: Parallel Matrix Multiplication in Pthreads
///Availability:http://multicoredays.blogspot.com/2014/05/parallel-matrix-multiplication-in.html
// Author:Joyrider

void *multiplyVector(void *arguments)
{
    struct thread_data *args;
    args=(struct thread_data *) arguments;
    int proportion;    
    int diff= args->id;
    proportion = Matrix_Size/num_of_pieces;
    int _start=diff * proportion;
    int _end= _start + proportion;
    
    for (int i = _start; i < _end; i++)
    {
              
        args->v3[i] =  args->v1[i] *  args->v2[i];
       
    }
    return args;
    pthread_exit(NULL);


}

/////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){


    pthread_t threads[num_of_pieces];
    pthread_t thread,thread2;
    struct thread_data td[num_of_pieces];

  



  

    srand(time(0));

    int *v1, *v2, *v3;
    int rc;

    //ToDo: Add Comment
   

    //ToDo: Add Comment
    v1 = (int *) malloc(Matrix_Size * sizeof(int *));
    v2 = (int *) malloc(Matrix_Size * sizeof(int *));
    v3 = (int *) malloc(Matrix_Size * sizeof(int *));


    randomVector(v1, Matrix_Size);

    randomVector(v2, Matrix_Size);




    //ToDo: Add Comment
for(int i=0;i<num_of_pieces;i++)
    {
        td[i].id =i;
        td[i].v1=v1;
        td[i].v2=v2;
        td[i].v3=v3;
       
    }
  
 auto start = high_resolution_clock::now();
    for(int i=0;i<num_of_pieces;i++)
    {
        //cout << "main() : creating thread, " << i << endl;
        rc=pthread_create(&threads[i], NULL, *multiplyVector,(void *)&td[i]);     
        if(rc){
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }
    for (int i = 0; i < num_of_pieces; i = i + 1)
    {
        pthread_join(threads[i], NULL);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);


    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    

    return 0;





}