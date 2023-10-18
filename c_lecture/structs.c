
/**
 * A demo showing the difference between passing by value and by reference
 * 
 * In a linux terminal compile with: gcc -o structs.out structs.c
 * And then run with: ./structs.out
 */

#include <stdio.h>
#include <stdlib.h>

struct aStructure {
  int a;
  int b;
};

int main() {
  struct aStructure s1;
  s1.a = 1;
  s1.b = 2;

  struct aStructure s2;
  s2.a = 3;
  s2.b = 4;
  
  printf("s1: a: %i, b %i\n", s1.a, s1.b);
  printf("s2: a: %i, b %i\n", s2.a, s2.b);
  
  
  struct aStructure * s3 = malloc(sizeof(struct aStructure));
  (*s3).a = 1;
  s3->b = 2;

  printf("s2: a: %i, b %i\n", s3->a, s3->b);
  return 0;



} 