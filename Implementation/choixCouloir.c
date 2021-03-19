#include <stdio.h>
#include <stdlib.h>
#include "structures.h"


CORD choixCouloir(){
	CORD a;
	printf("Donnez coordonnées du couloir ou insérer\n");
	printf("x :");
	scanf("%u",&a.x);

	printf("\n");
	
	printf("y :");
	scanf("%u",&a.y);
	return a;
}


//TEST:
/*
int main(void){
	CORD test;
	test = choixCouloir();
	printf("x:%u y:%u\n",test.x,test.y);

	return 0;
}
*/