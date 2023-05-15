#include <iostream>
#include <chrono>
#include <omp.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>


using namespace std ;
using namespace std :: chrono ;

auto Get_Avg( int S[2] ){

return ( S[0] + S[1] )/2 ;
}




int lim = 0 ;

void set_lim( int size ){

if( size >= 12500 )   lim = 12500 ;

else lim = (size-1) ;

}


void check( int* arr, int n ){

  for( int i = 0 ; i < n-1 ; i++ ){
    if(arr[i] > arr[i+1]){
      cout << "\n\nFalse\n\n" ;
      break ;

    }

//    cout << arr[i] << "  " ;
 //   if( i % 13 == 0 && i != 0 ) cout << endl ;
  }
}

void swap( int* a, int* b ){

int s = *a ;
*a = *b ;
*b = s ;
}



int Serial_partition( int* x, int l, int h ){

int piv = x[h] ;
int i = l-1 ;

for( int j = l; j <= h ; j++ ){
		
		if( x[j] < piv ){
    
			i++ ;
	    swap( &x[i], &x[j] ) ;
		}
	}

	swap( &x[i+1], &x[h] ) ;
  return i+1 ;
}


void Serial_Quick_Sort( int* arr, int l, int h ){

	if( l < h ){

		int half = Serial_partition( arr, l, h ) ;
		Serial_Quick_Sort( arr, l, half - 1 ) ;
		Serial_Quick_Sort( arr, half+1, h ) ;
	
  }
}


int OpenMP_thrds = 0 ;

void OpenMP_Quick_Sort( int* arr, int l, int h ){

  OpenMP_thrds++ ;
  if(  (h - l)/lim > OpenMP_thrds ){

	if( l < h ){
    int half ;
		half = Serial_partition( arr, l, h ) ;

#pragma omp task
      OpenMP_Quick_Sort( arr, l, half-1  ) ;
		
#pragma omp task
      OpenMP_Quick_Sort( arr, half+1, h ) ;

  }
  }

  else Serial_Quick_Sort( arr, l, h ) ;

}





void* POSIX_QS( void* i) ;
int s, POSIX_thrds = 0 ;

class Data{

  public:
    int* arr ;
    int l ;
    int h ;

    Data(){
  
    arr = new int[s] ;
    l = 0 ;
    h = 0 ;
    }

    Data( int* a, int L, int H ){

    arr = a ;
    l = L ;
    h = H ;
    }

};


void POSIX_Quick_Sort( int* arr, int l, int h ){

  s = h+1 ;

  Data d( arr, l, h ) ;

  pthread_t t ;

  pthread_create( &t, NULL, POSIX_QS, &d ) ;
  pthread_join( t, NULL ) ;
}

void* POSIX_QS( void* i ){

  POSIX_thrds++ ;
  Data* a = (Data*) i ;
  int* arr = new int[s] ;

  if( (a->h - a->l)/lim > POSIX_thrds  ){

  arr = a->arr ;
  int L = a->l ;
  int H = a->h ;
  if( L < H ){
    pthread_t t1, t2 ;
    Data* x = new Data ;
    Data* y = new Data ;

    int half = Serial_partition(a->arr, L, H) ;

    x -> arr = a -> arr ;
    y -> arr = a -> arr ;

    x->h = half - 1 ;
    x->l = L ;
    pthread_create( &t1, NULL, POSIX_QS, x ) ;

    y->h = H ;
    y->l = half + 1 ;
    pthread_create( &t2, NULL, POSIX_QS, y ) ;

    pthread_join(t1, NULL) ;
    pthread_join(t2, NULL) ;
  }

  }
  

  else Serial_Quick_Sort( a->arr, a->l, a->h ) ; 

pthread_exit(NULL) ;

}


















void Get_QuickSort_Times( int size, int QS_times[3], int* a ){

int* a1 = new int[size] ;
int* a2 = new int[size] ;
int* a3 = new int[size] ;

set_lim(size) ;

for( int i = 0 ; i < size ; i++ )
  a1[i] = a2[i] = a3[i] = a[i] ;

auto start = high_resolution_clock :: now () ;
auto stop = high_resolution_clock :: now () ;
auto time = duration_cast<microseconds>( stop - start ) ;

  start = high_resolution_clock :: now () ;
  Serial_Quick_Sort(a1, 0, size-1) ;
  stop = high_resolution_clock :: now () ;
  time = duration_cast<microseconds>( stop - start ) ;

  QS_times[0] = time.count() ;


check(a1, size) ;


start = high_resolution_clock :: now () ;
  #pragma omp parallel
    #pragma omp single
    OpenMP_Quick_Sort(a2, 0, size-1) ; 

stop = high_resolution_clock :: now () ;
time = duration_cast<microseconds>( stop - start ) ;


QS_times[1] = time.count() ;


check(a2, size) ;


start = high_resolution_clock :: now () ;

    POSIX_Quick_Sort(a3, 0, size-1) ;

stop = high_resolution_clock :: now () ;
time = duration_cast<microseconds>( stop - start ) ;
check(a3, size) ;
//cout << endl << time.count() << " microseconds in POSIX" << endl ;
//cout << " POSIX Threads : " << POSIX_thrds << endl << endl;

QS_times[2] = time.count() ;
delete a1, a2, a3, a ;

}

