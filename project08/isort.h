(ISORT)
//int isort (int *begin, int *end) {
//  int *i = begin ;
//  int *j ;
//  int x ;
//  while(i<end) {
//    x = *i ;
//    j = i-1 ;
//    ** NOTE semantics here! the && operator will prevent the execution
//    ** of the *j>x part of the expression, this is not just  a logical
//    ** operation! 
//    while(j>=begin && *j>x) {
//      *(j+1) = *j ;
//      j=j-1 ;
//    }
//    i=i+1 ;
//  }
//  return end-begin ;
// }


