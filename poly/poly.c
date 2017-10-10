#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "error.h"
#include "poly.h"

typedef struct poly_t poly_t;

struct poly_t {
  int* digits;
  int* powers;
  char* polynom;
  int count;
};

poly_t*	new_poly_from_string(const char* p){

  poly_t* poly=malloc(sizeof(poly_t));

  char* polynom=malloc(strlen(p)+1);
  memcpy(polynom, p, strlen(p)+1);
  poly->polynom=malloc(strlen(p)+1);
  memcpy(poly->polynom, polynom, strlen(p)+1);

  int pos_or_neg=1;
  int digit=0;
  int power=0;
  int count=0;
  int temp=0;
  int build=0;
  int n=1;
  int* digits=malloc(sizeof(int));
  int* powers=malloc(sizeof(int));
  int p_size=strlen(p);
  int space_count=0;
  for (int i = 0; i < p_size; i++) {
    char str = p[i];
    if ( str==' '){
      space_count++;
    }
  }
  if (space_count!=0 ) {
    for (char c = *p; c; c=*++p) {
      p_size=strlen(p);
      //plus or minus
      if (c=='-' || c=='+') {
        if (c=='-') {
          pos_or_neg=-1;
        } else {
          pos_or_neg=1;
        }
      // is it a number: base or exp?
      } else if (isdigit(c)) {
          digit=(c-48)*pos_or_neg;

      // is it an x?
      } else if (c=='x') {
        // if there's no digit before x
         if (digit==0) {
          digit=1;
        }

      } else if (c=='^') {
        temp=0;
        n=1;
        for (c=*p;c;c=*++p) {
          if (isdigit(c)) {
            build=c-48;
            temp=(temp*n)+build;
            n=10;
          } else {
            if(c!='^'){
              break;
            }
          }
        }
        power=temp;
        digits=realloc(digits, (count+1) * sizeof(int));
        digits[count]=digit;
        powers=realloc(powers, (count+1) * sizeof(int));
        powers[count]=power;
        digit=0;
        power=0;
        count++;

      // insert digit and power into arrays
      } else if (c==' ' && digit!=0) {
        digits=realloc(digits, (count+1) * sizeof(int));
        digits[count]=digit;
        if (power==0) {
            power=1;
        }
        powers=realloc(powers, (count+1) * sizeof(int));
        powers[count]=power;
        digit=0;
        power=0;
        count++;
      }
      if(p_size==1 && digit!=0)  {
        power=0;
        digits=realloc(digits, (count+1) * sizeof(int));
        digits[count]=digit;
        powers=realloc(powers, (count+1) * sizeof(int));
        powers[count]=power;
        count++;
      }
    }
  } else {
    digits=realloc(digits, (count+1) * sizeof(int));
    powers=realloc(powers, (count+1) * sizeof(int));
    digits[count]=atoi(polynom);
    powers[count]=0;
    count++;
  }
  poly->digits=malloc((count+2)*sizeof(int));
  memcpy(poly->digits, digits, (count+2)*sizeof(int));
  poly->powers=malloc((count+2)*sizeof(int));
  memcpy(poly->powers, powers, (count+2)*sizeof(int));
  poly->count=count;
  free(digits);
  free(powers);
  free(polynom);
  return poly;
}


void		free_poly(poly_t* poly_t){
  free(poly_t->digits);
  free(poly_t->powers);
  free(poly_t->polynom);
  free(poly_t);
}

poly_t*		mul(poly_t* poly_p, poly_t* poly_q){
  int* digits=malloc(sizeof(int));
  int* powers=malloc(sizeof(int));
  int digit=0;
  int power=0;
  int size=0;
  int added=0;
  for (int i=0;i<poly_p->count;i++) {
    for (int j=0;j<poly_q->count;j++) {
      power=poly_p->powers[i] + poly_q->powers[j];
      if (size!=0) {
        // check if exp alredy exists and add to existing number
          for (int c=1;c<=size; c++){
            int p=powers[c];
            if (p==power) {
              digit=poly_p->digits[i] * poly_q->digits[j];
              digit=digits[c]+digit;
              digits[c]=digit;
              added=1;
            }
          }
      }
      if (added==0) {
        size++;
        digits=realloc(digits, (size+1)*sizeof(int));
        digit=poly_p->digits[i] * poly_q->digits[j];
        digits[size]=digit;
        powers=realloc(powers, (size+1)*sizeof(int));
        powers[size]=power;
      }
      added=0;
    }
  }
  poly_t* r=malloc (sizeof(poly_t));
  r->digits=malloc((size+2)*sizeof(int));
  memcpy(r->digits, digits, (size+2)*sizeof(int));
  r->powers=malloc((size+2)*sizeof(int));
  memcpy(r->powers, powers, (size+2)*sizeof(int));
  free(digits);
  free(powers);
  r->polynom=NULL;
  r->count=size;
  return r;
}

void		print_poly(poly_t* p){
  if (p->polynom==NULL) {
    int first=0;
    int count=p->count;
    int digit=0;
    for (int i=1;i<=p->count;i++){
      digit=p->digits[i];
      if (digit!=0) {
        if (digit<0) {
          digit=digit*-1;
          printf("- %d", digit);
        } else {
          if (first==0) {
            first=1;
            printf("%d", digit);
          } else {
            printf("+ %d", digit);
          }
        }
        if (count!=1) {
          printf("x");
        }
        if (count>2) {
          printf("^%d ", p->powers[i]);
        } else{
          if (count!=1){
            printf(" ");
          }
        }
        count--;
      }
    }
  } else {
    printf("%s",p->polynom);
  }
  printf("\n");
}
