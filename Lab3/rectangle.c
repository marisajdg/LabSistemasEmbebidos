#include<stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) 
{ 
  /*regex_t regex;

  regcomp(&regex, "(-a|-p) -((l [0-9]+ -w)|(w [0-9]+ -l))", REG_EXTENDED);
  int return_value = regexec(&regex, argv, 0, NULL, 0);
  printf("%d", return_value);*/

  if (argc != 6){
    printf("Error reading parameters, format must be:\n-a -l <int length> -w <int width>\n-p -l <int length> -w <int width>\n");
  } else{
      int side1 = atoi(argv[3]);
      int side2 = atoi(argv[5]);

      if (strcmp(argv[1], "-a") == 0){
        printf("area = %d units\n", side1 * side2);
      } else if (strcmp(argv[1], "-p") == 0){
        printf("perimeter = %d units\n", 2 * side1 + 2 * side2);
      } else{
          printf("Error reading parameters, format must be:\n-a -l <int length> -w <int width>\n-p -l <int length> -w <int width>\n");
      }
  }

  return 0; 
}