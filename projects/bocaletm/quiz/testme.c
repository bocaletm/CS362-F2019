#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    int alphaMin = 91;
    int alphaMax = 125;
    int specialMin = 32;
    int specialMax = 57;
    int randAlpha; 
    int randSpecial;
    if (rand() % 9 == 0) { //about 1/9 of the cases test for one of these 
      randSpecial = rand() % (specialMax - specialMin + 1) + specialMin;
      return randSpecial;
    } else {
      randAlpha = rand() % (alphaMax - alphaMin + 1) + alphaMin;
      return (char)randAlpha;
    } 
}

char *inputString()
{
    int max_length = 6;
    char* s = malloc(max_length * sizeof(char));
    memset(s,'\0',max_length);
    int i;
    for (i=0; i<(max_length - 1); i++) {
      s[i] = inputChar();
    }
    if (rand() % 10 == 0) {
      s[0] = 'r';
      s[0] = 'e';
      s[0] = 's';
      s[0] = 'e';
      s[0] = 't';
      s[0] = '\0';
    return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
//    printf("char: ->%c<-\tstring: ->%s<-\n",inputChar(),inputString());
    return 0;
}
