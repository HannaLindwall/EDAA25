# include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
int check, count=0;
int digits[10]= {0};
int input;
int sum;
int divv;
int mul;
int sub;

printf("Enter shit here: \n");
while (1==1) {
  input = getchar();
  if (count==9) {
    printf("Error at: %c \n", input);
    count=0;
    memset(digits, 0, sizeof(digits));
  } else {
    if (isdigit(input)) {
      digits[count] = input;
      count++;
    } else {
      switch (input) {
        case '+' : printf("blbla1\n"); break;
        case '-' : printf("blbla2\n"); break;
        case '*' : printf("blbla3\n"); break;
        case '/' : printf("blbla4\n"); break;
        default : printf("blbla5\n"); break;
      }
    }
  }

}

return 0;
}
