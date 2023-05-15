void merge(int* arr, int p, int q, int r) {

  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];

  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

void Serial_Merge_Sort(int* arr, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
      
    Serial_Merge_Sort(arr, l, m);
      
    Serial_Merge_Sort(arr, m + 1, r);
      

      merge(arr, l, m, r);
  }
}



void OpenMP_Merge_Sort(int* arr, int l, int r) {


  POSIX_thrds++ ;
  if(  (r - l)/lim > POSIX_thrds ){

    if (l < r) {
      int m = l + (r - l) / 2;

      #pragma omp task
        OpenMP_Merge_Sort(arr, l, m);
       
      #pragma omp task
        OpenMP_Merge_Sort(arr, m + 1, r);
      

        merge(arr, l, m, r);
  
    }
  }
  else Serial_Merge_Sort( arr, l, r ) ;

}


void* POSIX_MS(void* i) ;



void POSIX_Merge_Sort( int* arr, int l, int h ){

  s = h+1 ;

  Data d( arr, l, h ) ;

  pthread_t t ;

  pthread_create( &t, NULL, POSIX_MS, &d ) ;
  pthread_join( t, NULL ) ;
}

void* POSIX_MS( void* i ){

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
 
    int m = a->l + (a->h - a->l) / 2;

    x -> arr = a -> arr ;
    y -> arr = a -> arr ;

    x->h = m ;
    x->l = L ;
    pthread_create( &t1, NULL, POSIX_MS, x ) ;

    y->h = H ;
    y->l = m + 1 ;

    pthread_create( &t2, NULL, POSIX_MS, y ) ;

    pthread_join(t1, NULL) ;
    pthread_join(t2, NULL) ;
  
  merge( arr, a->l, m, a->h ) ; 
  }
  

  }
  

  else Serial_Quick_Sort( a->arr, a->l, a->h ) ; 

pthread_exit(NULL) ;

}





void Get_MergeSort_Times( int size, int QS_times[3], int* a ){

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
  Serial_Merge_Sort(a1, 0, size-1) ;
  stop = high_resolution_clock :: now () ;
  time = duration_cast<microseconds>( stop - start ) ;

  QS_times[0] = time.count() ;


check(a1, size) ;


OpenMP_thrds = 0 ;
start = high_resolution_clock :: now () ;
  #pragma omp parallel
    #pragma omp single
    OpenMP_Merge_Sort(a2, 0, size-1) ; 

stop = high_resolution_clock :: now () ;
time = duration_cast<microseconds>( stop - start ) ;


QS_times[1] = time.count() ;


POSIX_thrds = 0 ;

start = high_resolution_clock :: now () ;

    POSIX_Quick_Sort(a3, 0, size-1) ;

stop = high_resolution_clock :: now () ;
time = duration_cast<microseconds>( stop - start ) ;
check(a3, size) ;

QS_times[2] = time.count() ;


delete a1, a2, a3, a ;
}

