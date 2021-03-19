#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

unsigned int oppose(CORD a, CORD choixPrecedent){

	if(a.x == 0 || a.x == 6){
		    if(a.x == 0){
		    	if(a.y == 1){
		        	temp.x=6;
		        	temp.y=1;
		        }	    
			 	if(a.y == 3){
			        temp.x=6;
			        temp.y=3;
			    }
			    if(a.y == 5){
			    	temp.x=6;
		    		temp.y=5;
		    	}
		    }

		    if(a.x == 6){
		    	if(a.y == 1){
		        	temp.x=0;
		        	temp.y=1;
		        }	    
			 	if(a.y == 3){
			        temp.x=0;
			        temp.y=3;
			    }
			    if(a.y == 5){
			    	temp.x=0;
		    		temp.y=5;
		    	}
		    }
	}

	else if(a.y == 0 || a.y == 6){
			if(a.y == 0){
		    	if(a.x == 1){
		        	temp.x=1;
		        	temp.y=6;
		        }	    
			 	if(a.x == 3){
			        temp.x=3;
			        temp.y=6;
			    }
			    if(a.x == 5){
			    	temp.x=5;
		    		temp.y=6;
		    	}
		    }
		    
		    if(a.y == 6){
		    	if(a.x == 1){
		        	temp.x=1;
		        	temp.y=0;
		        }	    
			 	if(a.x == 3){
			        temp.x=3;
			        temp.y=0;
			    }
			    if(a.x == 5){
			    	temp.x=5;
		    		temp.y=0;
		    	}
		    }

	}  
    
    if(temp.x == choixPrecedent.x && temp.y == choixPrecedent.y)
        return 1;
    else 
    	return 0;

}



/* TEST: Cette fonction renvoie 1 si la cord entrée est egal à l'opposé du choix précédent (autrement dit si on veut insérere la tuile d'ou elle vient de sortir).
int main(void){


	CORD a,a1;
	printf("x:");
	scanf("%u",&a.x);
	printf("\ny:");
	scanf("%u",&a.y);

	printf("x2:");
	scanf("%u",&a1.x);
	printf("\ny2:");
	scanf("%u",&a1.y);
	unsigned int b=  oppose( a, a1);//{// on veut savoir si a est choix sont opposés 
	printf("::%u",b);

}
*/