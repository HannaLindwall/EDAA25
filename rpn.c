# include <stdio.h>

int main()
{
int check, count=0;
char digits[10]="";
char input;
printf("Enter shit here: \n");
while (1==1) {
  input = (char) getchar();

  if (count==9) {
    //digits={0};
    printf("Error at: %c \n", input);
    count=0;
  } else {
    if (strcmp(input," ")==0 ) {

    }
    printf("You wrote: %c \n", input);
    digits[count]=input;
    count++;
  }
}

return 0;
}
