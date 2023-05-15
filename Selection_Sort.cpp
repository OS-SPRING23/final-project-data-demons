struct Compare{

  int val ;
  int index ;
} ;

#pragma omp declare reduction( Minimum : struct Compare : omp_out = omp_in.val > omp_out.val ? omp_out : omp_in)\
                                    initializer( omp_priv = omp_orig )

struct Array{

  int* arr ;
  int size ;
};

void Serial_Selection_Sort( int* arr, int size ){

int i, j, min ;

for( int i = 0 ; i < size-1 ; i++  ){

min = i ;

for( j = i+1 ; j < size ; j++ ){
  if( arr[j] < arr[min] )
    min = j ;

}

if( min != i )
  swap( &arr[min], &arr[i] ) ;

}

}




void OpenMP_Selection_Sort( int* arr, int size ){


int i, j ;

    #pragma omp single
    for( int i = 0 ; i < size-1 ; i++  ){

    struct Compare min ;
    min.index = i ;
    min.val = arr[i] ;

//      #pragma omp parallel for reduction( Minimum : min )
      for( j = i+1 ; j < size ; j++ ){
        if( arr[j] < min.val ){
          min.index = j ;
          min.val = arr[j] ;
        }
      }

    if( min.index != i )
      swap( &arr[min.index], &arr[i] ) ;

    }
}


void* POSIX_SS( void* x ){

struct Array* a = (Array*) x ;

int i, j, min ;

for( i = 0 ; i < a->size-1 ; i++  ){

min = i ;

  for( j = i+1 ; j < a->size ; j++ ){
    if( a->arr[j] < a->arr[min] )
      min = j ;

  }

if( min != i )
  swap( &a->arr[min], &a->arr[i] ) ;

}

pthread_exit(NULL) ;

}


void POSIX_Selection_Sort( int* arr, int size ){

struct Array* a ;
pthread_t t ;

a->arr = arr ;
a->size = size ;

pthread_create( &t, NULL, POSIX_SS, (void*)a ) ;

pthread_join(t, NULL) ;

}




void Get_SelectionSort_Times(int size, int SS_times[3], int* a){

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
  Serial_Selection_Sort(a1, size) ;
stop = high_resolution_clock :: now () ;
time = duration_cast<microseconds>( stop - start ) ;

  SS_times[0] = time.count() ;

check(a1, size) ;


start = high_resolution_clock :: now () ;
    OpenMP_Selection_Sort(a2, size) ; 
stop = high_resolution_clock :: now () ;
time = duration_cast<microseconds>( stop - start ) ;


SS_times[1] = time.count() ;


check(a2, size) ;


start = high_resolution_clock :: now () ;

    POSIX_Quick_Sort(a3, 0, size-1) ;

stop = high_resolution_clock :: now () ;
time = duration_cast<microseconds>( stop - start ) ;
//check(a3, size) ;
//cout << endl << time.count() << " microseconds in POSIX" << endl ;
//cout << " POSIX Threads : " << POSIX_thrds << endl << endl;

SS_times[2] = time.count() ;

check(a3, size) ;


delete a1, a2, a3 ;

  
}

