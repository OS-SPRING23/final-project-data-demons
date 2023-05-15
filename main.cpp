#include <iostream>
#include <fstream>
#include "Quick_Sort.cpp"
#include "Selection_Sort.cpp"
#include "Merge_Sort.cpp"

int main(){

  int size[6] = { 100, 1000, 10000, 100000, 1000000, 10000000 } ;
  int SQS[6], OQS[6] ,PQS[6] ;
  int SSS[4], OSS[4] ,PSS[4] ;
  int SMS[5], OMS[5] ,PMS[5] ;
  int arr[3] ;

  srand(time(0)) ;


    int* t1 = new int[size[0]] ;
    int* t2 = new int[size[1]] ;
    int* t3 = new int[size[2]] ;
    int* t4 = new int[size[3]] ;
    int* t5 = new int[size[4]] ;
    int* t6 = new int[size[5]] ;
    int* u1 = new int[size[0]] ;
    int* u2 = new int[size[1]] ;
    int* u3 = new int[size[2]] ;
    int* u4 = new int[size[3]] ;
    int* v1 = new int[size[0]] ;
    int* v2 = new int[size[1]] ;
    int* v3 = new int[size[2]] ;
    int* v4 = new int[size[3]] ;
    int* v5 = new int[size[4]] ;
    int* v6 = new int[size[5]] ;

    cout << "\n\n\t\t Algorithm speed Comparison between OpenMP, POSIX and Serial methods \n\n" ;
    cout << "\n\t\t Default Dataset Sizes :\n\t\t Selection Sort = {" ;
    
    for(int i = 0 ; i < 4 ; i++){
      cout << size[i] ; if( i != 3 ) cout << ", " ; }
    
    cout <<"} \n\t\t Quick Sort = {" ;


    for(int i = 0 ; i < 6 ; i++){
      cout << size[i] ; if( i != 5 ) cout << ", " ; }


    cout <<"} \n\t\t Merge Sort = {" ;


    for(int i = 0 ; i < 5 ; i++){
      cout << size[i] ; if( i != 4 ) cout << ", " ; }
    
    cout <<"} \n\n" ;



    for( int i = 0 ; i < size[0] ; i++ )
      v1[i] = u1[i] = t1[i] = rand()%(size[0]+1) ;

    for( int i = 0 ; i < size[1] ; i++ )
      v2[i] = u2[i] = t2[i] = rand()%(size[1]+1) ;

    for( int i = 0 ; i < size[2] ; i++ )
      v3[i] = u3[i] = t3[i] = rand()%(size[2]+1) ;
 
    for( int i = 0 ; i < size[3] ; i++ )
      v4[i] = u4[i] = t4[i] = rand()%(size[3]+1) ;

    for( int i = 0 ; i < size[4] ; i++ )
      v5[i] = t5[i] = rand()%(size[4]+1) ;

    for( int i = 0 ; i < size[5] ; i++ )
      t6[i] = rand()%(size[5]+1) ;


  for( int i = 0 ; i < 4 ; i++ ){
      
      switch (i) {
       
    case 0:
        Get_SelectionSort_Times(size[0], arr, u1) ;
        break ;
        
    case 1:
        Get_SelectionSort_Times(size[1], arr, u2) ;
        break ;

    case 2:
        Get_SelectionSort_Times(size[2], arr, u3) ;
        break ;
    
    case 3:
        Get_SelectionSort_Times(size[3], arr, u4) ;
        break ;

    default :
        break ;
      }
      
        SSS[i] = arr[0] ;
        OSS[i] = arr[1] ;
        PSS[i] = arr[2] ;
    }


  cout << "\n\n\n" ;
  cout << "Selection-Sort Times(microseconds) \n\n" ;
  cout << "DataSize \tSerial \t\tOpenMP \t\tPOSIX \n" ;
  for( int i = 0 ; i < 3 ; i++ )
  cout << size[i] << "\t\t" << SSS[i] << "\t\t" << OSS[i] << "\t\t" << PSS[i] << endl ;
  cout << size[3] << "\t\t" << SSS[3] << "\t" << OSS[3] << "\t\t" << PSS[3] << endl ;
  

  cout << "\n\n\n" ;





  for( int i = 0 ; i < 6 ; i++ ){
      
      switch (i) {
       
    case 0:
        Get_QuickSort_Times(size[0], arr, t1) ;
        break ;
        
    case 1:
        Get_QuickSort_Times(size[1], arr, t2) ;
        break ;

    case 2:
        Get_QuickSort_Times(size[2], arr, t3) ;
        break ;
    
    case 3:
        Get_QuickSort_Times(size[3], arr, t4) ;
        break ;
    
    case 4:
        Get_QuickSort_Times(size[4], arr, t5) ;
        break ;

    case 5:
        Get_QuickSort_Times(size[5], arr, t6) ;
        break ;


    default :
        break ;
      }
      
        SQS[i] = arr[0] ;
        OQS[i] = arr[1] ;
        PQS[i] = arr[2] ;
    }



  cout << "\n\n\n" ;
  cout << "Quick-Sort Times(microseconds) \n\n" ;
  cout << "DataSize \tSerial \t\tOpenMP \t\tPOSIX \n" ;
  for( int i = 0 ; i < 5 ; i++ )
  cout << size[i] << "\t\t" << SQS[i] << "\t\t" << OQS[i] << "\t\t" << PQS[i] << endl ;
  cout << size[5] << "\t" << SQS[5] << "\t\t" << OQS[5] << "\t\t" << PQS[5] << endl ;



  for( int i = 0 ; i < 6 ; i++ ){
      
      switch (i) {
       
    case 0:
        Get_MergeSort_Times(size[0], arr, v1) ;
        break ;
        
    case 1:
        Get_MergeSort_Times(size[1], arr, v2) ;
        break ;

    case 2:
        Get_MergeSort_Times(size[2], arr, v3) ;
        break ;
    
    case 3:
        Get_MergeSort_Times(size[3], arr, v4) ;
        break ;

    case 4:
        Get_MergeSort_Times(size[4], arr, v5) ;
        break ;


    default :
        break ;
      }
      
        SMS[i] = arr[0] ;
        OMS[i] = arr[1] ;
        PMS[i] = arr[2] ;
    }


  cout << "\n\n\n" ;
  cout << "Merge-Sort Times(microseconds) \n\n" ;
  cout << "DataSize \tSerial \t\tOpenMP \t\tPOSIX \n" ;

  for( int i = 0 ; i < 5 ; i++ )
  cout << size[i] << "\t\t" << SMS[i] << "\t\t" << OMS[i] << "\t\t" << PMS[i] << endl ;



  cout << "\n\n\n" ;

  ofstream file("Results.csv") ;

  file << " ,, Selection Sort ,,,, Quick Sort ,,,, Merge Sort\n" ;
  file << " DataSize ,  Serial, OpenMP, POSIX,,  Serial, OpenMP, POSIX,,  Serial, OpenMP, POSIX \n";

  for( int i = 0 ; i < 6 ; i++ ){
    if( i < 4 )
      file << size[i] << "," <<SSS[i] << "," << OSS[i] << "," << PSS[i] << ",," << SQS[i] << "," << OQS[i] << "," << PQS[i] << ",," <<  SMS[i] << "," << OMS[i] << "," << PMS[i] << endl ;

    else if( i == 4 )
      file << size[i] << ",,,,," << SQS[i] << "," << OQS[i] << "," << PQS[i] << ",," << SMS[i] << "," << OMS[i] << "," << PMS[i] << endl ;  
  
    else

      file << size[i] << ",,,,," << SQS[i] << "," << OQS[i] << "," << PQS[i] << endl ;  
  }

  
}

