#include <stdio.h>
#include <stdlib.h>
int XMIN = 0;
int ** arrs = 0;

void onePart(){														
	printf("Cena: 0\n");
}
void error() {
	printf("Nespravny vstup.\n");										
	exit(1);
}
int recursion ( int *arr,int ind, int actSize,int actMin) {
	int newSize = actSize-1;
	int * newArr;// [actSize];
	int j, i;
	int min  = 0;

	if (!arrs)
	{
		arrs = (int**) malloc (actSize * sizeof(int*));
		for (i = 0; i < actSize; ++i)
		{	
			arrs[i] = (int*) malloc (actSize * sizeof(int));
		}
	}

	if (ind == 0)
	{
		newArr = arr;
	}
	else
	{
		newArr = arrs[actSize-1];
	}
	
	if (ind != 0) {
		//newArr = (int*) malloc (newSize * sizeof(int));
		j=0;
		for (i=0; i<actSize; i++) { /* copying elements of the old array to new SKIPPING one element!  */
			if (i!=ind) {
				newArr[j] = arr[i];
				j++;
			}
		}
	}
	else {
		//newArr = arr; //(int*) malloc (actSize * sizeof(int));
	//	for (i=0; i<actSize; i++) 
	//		newArr[i] = arr[i];
		newSize = actSize;
	}	
	for (i=1; i<newSize-1; i++){
		min = newArr[i-1]*newArr[i+1];
		if ( XMIN && ((min + actMin) >= XMIN))
			break;
		if (newSize == 3) {
			if (XMIN) {
				if ((actMin+min) < XMIN)
					XMIN = min + actMin;
				if(ind) ;
					//free(newArr);
				break;
				
			}
			else {
				XMIN = actMin + min;
				if(ind) ;
					//free(newArr);				
				break;
			}
		}	
		if (!recursion(newArr, i, newSize, actMin+min)) {
			if (i==newSize-2){
				if (ind) ;
					//free(newArr);
				break;	
			}	
		}
	}	
	//if (ind)	;
		//free(newArr);
	//free(arr);
	if (!ind)
	{
		for (i = 0; i < actSize; ++i)
		{	
			free(arrs[i]);
		}
		free(arrs);
	}	
	return 0;
}

int main(void)
{														/*MAIN   */
int c=0;
int *arr;
int i=0;
int actSize;
int sizeArr = 100;
int amount=0;

	arr = (int*) malloc (sizeArr * sizeof(int));
	printf("Zadejte pocty sroubu pro jednotlive priruby:\n");
	while( c!='\n' && c != -1)  {
		if ( scanf("%d", &arr[i]) == 1) {
			if (arr[i]>=1)
			{
				if (++i == sizeArr) {
					sizeArr *= 2;
					if (!realloc (arr, sizeArr)) {
		//				printf	("Error during the realloc");
						free(arr);
						exit(1);
					}
				}
	   			c=getchar();
	//			printf("c: %d\n", c);	
				if (c != '\n' && c != ' ' && c != -1) {
				    free(arr);
					error();	
				}
			}
			else
			{
				free(arr);
				error();
			}
		}
		else {
			if (!feof(stdin))
			{
				free(arr);
				error();
			}
			break;
			/*printf("error: %d\n", feof(stdin));
			c = getchar();
			printf("c: %d\n", c);	
			while (c == ' ')
			{
				c = getchar();
				printf("c: %d\n", c);		
			}
			if (c != '\n' && c != -1)
			{
				free(arr);
				error();
			}*/
		}
//		printf("CCC: %d\n", c);
	}
	if(i<=1) {
		free(arr);		
		error();	
	}
	actSize = i;
/*	printf("act=%d\n",actSize);*/
	for(i=1;i<actSize-1;i++){      /*FINDING AN AMOUNT OF REMOVABLE ITEMS */
		amount+=arr[i];
	}
/*printf("total=%d\n",amount);*/
	
	if(actSize==2){
		onePart();
		free(arr);
	return 0;	
	}
	if (!recursion (arr, 0, actSize,0)) {
		printf ("Cena: %d\n", XMIN+amount);
	}
	free(arr);	
return 0;
}


