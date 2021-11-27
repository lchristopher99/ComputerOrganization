(QSORT)
// int QSORT(int *begin, int *end) {
//   int sz ;
//   int *split ;
//   sz = end-begin ;
//   if(sz < 2)
//     return sz ;
//   split = PARTITION(begin,end) ;
//   QSORT(begin,split) ;
//   QSORT(split,end) ;
//   return sz ;
// 

(PARTITION)
// Lomuto Partitioning Scheme
// int *PARTITION(int *begin, int *end) {
//   pivot = *(end-1);
//   i = begin - 1
//   for(j=i+1;j<end;j++) {
//     if(*j <= pivot) {
//        i = i + 1
//        swap(*i,*j) ;
//     }
//   }
//   return i ;
// }

