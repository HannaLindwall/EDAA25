#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int main (){
int input;
char* word = malloc(sizeof(int));
char* longest_word = malloc(sizeof(int));
int count=0;
int longest=0;
while ((input=getchar())!=EOF) {
  while (isalpha(input)) {
    word[count]=input;
    count++;
    word = realloc(word, (count+1) * sizeof(int));
    input=getchar();
  }
  if (count>longest && count!=0) {
    longest_word=realloc(longest_word, (count+1) * sizeof(int));
    memcpy(longest_word, word, (count+1) * sizeof(int));
    longest=count;
  }
  count=0;
}
printf("%d characters in longest word: %.*s\n", longest, longest, longest_word);
free(word);
free(longest_word);
return 0;
}
