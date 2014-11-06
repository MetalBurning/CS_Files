//Jacob Rede
//830172687
//jare1987
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
bool is_valid_int(const char *the_string);

int main(int argc, char *argv[]) {
   int number;
    char buf[80];
    for (int i=1; i<argc; i++) {
      //printf("go: %s", argv[i]);
      //##############################################################if under 3 arguments then all fields arent filled in
      if (argc < 3) {
        fprintf(stderr,"error: not enough arguments: %s\n", argv[0]); 
        return 1;
      }
      //##############################################################if first argument then must be number
      if (i == 1) {
        if (is_valid_int(argv[i]) == 0) {
          fprintf(stderr,"error: not a correct integer: %s\n", argv[i]); 
          return 1;
        } 
        number = atoi(argv[i]);
       // printf("go: %d", number);
        //##############################################################if number is positive then proceed, else return error
        if (number > 0) {

        } else {
          fprintf(stderr,"error: not a correct integer: %d\n", number); 
          return 1;
        }
      } else {
        FILE *handle = fopen(argv[i],"r");
          if (handle == NULL) {
            fprintf(stderr,"Can't open data file: %s\n", argv[0]);
            return 1;
          }
          //##############################################################get line by line
        while (fgets(buf, sizeof(buf), handle) != NULL) {
        //##############################################################remove newline at end of string
        int len = strlen(buf);
        if( buf[len-1] == '\n' )
            buf[len-1] = 0;

//##############################################################tokenizer on the comma
          const char *tok;
          const char s[2] = ",";



          tok = strtok(buf, s);
          int counter = 1;
          //##############################################################while not nuill print out
          //##############################################################if our counter == the users input number then print out the element from the string
         while( tok != NULL )  {
           if (counter == number) {
                printf( "%s", tok );
            }
           
            tok = strtok(NULL, s);
            counter++;
         }
       printf( "\n");
       }
      }







    }

    return 0;
}
//##############################################################function to detect the 3X example (if input is not int this returns false)
bool is_valid_int(const char *the_string)
{
   // if negative numbers
   if (*the_string == '-')
      ++the_string;

   // if empty the_stringing or"-"
   if (!*the_string)
      return 0;

   // Check for any non-digit
   while (*the_string)
   {
      if (!isdigit(*the_string))
         return 0;
      else
         ++the_string;
   }

   return 1;
}
