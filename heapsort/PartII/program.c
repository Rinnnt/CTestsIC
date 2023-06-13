#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


char *derived_lookup_table(char *);
int contains(char *, char );

int main(void) {
  
    char *s = "attack";
  
    printf("The initial word is: %s\n", s);
  
    char *table = derived_lookup_table(s);
  
    printf("Derived lookup table: %s\n\n", table);

    free(table);
    
    return EXIT_SUCCESS;
}

char *derived_lookup_table(char *s) {
        
	char * o_out = calloc(strlen(s) + 1, sizeof(char));
	
        if (o_out == NULL) {
	    perror("malloc");
	    exit(EXIT_FAILURE);
	}

	char * o_end;
          
        o_end = o_out;

        for ( ; *s != '\0' ; ++s) {
	    if (!contains(o_out, *s)) {
	      *o_end++ = *s;
	    }
	}
	*o_end = '\0';

   	char *out = realloc(o_out, o_end - o_out + 1);

	if (out == NULL) {
	    perror("realloc");
	    exit(EXIT_FAILURE);
	  }

	return out;

}


int contains(char *s, char c) {

    for (int i=0; i < strlen(s); i++){
        if(s[i] == c){
	   return 1;
	}
    }
    
    return 0;
}
