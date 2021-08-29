#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 3){
    printf("Error reading parameters, format must be:\n-a -l <int length> -w <int width>\n-p -l <int length> -w <int width>\n");
  } else{
    char name[30];
    char id[30];
    char addMore = 'Y';
    int i = 0;

    FILE *f = fopen("Datalog.txt", "w"); 
    if (f == NULL) 
    { 
      fprintf(stderr,"Error opening file!\n"); 
      exit(1); 
    } 
      
    while (addMore == 'Y'){
      printf("Enter Name: ");
      scanf("%s", name);

      printf("Enter ID: ");
      scanf("%s", id);

      fprintf(f, "%s %s\n", name, id); 

      i++;

      if (i < atoi(argv[2])){
        printf("Do you wish to add more [Y/n]:");
        scanf(" %c", &addMore);
      }
      else{
        break;
      }
    }
    
    printf("Students information stored in Datalog.txt\n");

    fclose(f); 
  }

  return 0;
}