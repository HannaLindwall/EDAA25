# include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
int line=1;
int count=0;
int digits[10]= {0};
int input;
int temp = 0;
int n=1;
while (1==1) {
while ((input=getchar())!=EOF) {
if (isdigit(input)) {
while (isdigit(input)) {
input=input-'0';
temp=(temp*n)+input;
n=10;
input = getchar();
}
n=1;
if (count==10) {
printf("line %d: error at %d\n", line, temp);
break;
} else {
digits[count] = temp;
count++;
}
temp=0;
}
if (input=='!') {
printf("line %d: error at %c\n", line, input);
break;
} else if (input=='+' || input=='-'||input=='*'||input=='/') {
if (digits[count-1]==0) {
printf("line %d: error at /\n", line);
break;
}
if (count>=2) {
switch (input) {
case '+' : digits[count-2]=digits[count-2]+digits[count-1]; count--;
break;
case '-' : digits[count-2]=digits[count-2]-digits[count-1]; count--;
break;
case '*' : digits[count-2]=digits[count-2]*digits[count-1]; count--;
break;
case '/' : digits[count-2]=digits[count-2]/digits[count-1]; count--;
break;
default : printf("invalid input\n"); break;
}
} else {
printf("line %d: error at %c\n", line, input);
break;
}
}
if (input=='\n') {
if (count != 1) {
printf("line %d: error at \\n\n", line);
break;
} else if ( count==1) {
printf("line %d: %d\n", line, digits[0]);
break;
count=0;
}
}
}
temp=0;
line++;
count=0;
if (input==EOF) {
break;
}
while (input!='\n') {
input=getchar();
}
}
return 0;
}
