#include <stdio.h>
#include <stdlib.h>

typedef struct intArray{
	unsigned int* arr;
	unsigned int initialized;
	unsigned int dim;
} uintArrayT;

void printArr(uintArrayT arr) {
    for(int i=0;i<=arr.initialized;i++){
        printf("%d ",arr.arr[i]);
    }
    putchar('\n');
}

char isPrime(unsigned int n){
	for(int i=2;i<n;i++){
		if(n%i==0){
			return 0;
		}
	}
	return 1;
}

int getNPrime(int n){
	int primesFound=0;
	int prime=0;
	int i=2;
	while(primesFound!=n){
		if(isPrime(i)){
			primesFound+=1;
			prime=i;
			i++;
		}
		else{
			i++;
		}
	}
	return prime;
}

uintArrayT getInstructNum(unsigned int godelNum){
	godelNum+=1;
	uintArrayT arr;
	arr.dim=1;
	arr.initialized=0;
	arr.arr=malloc(arr.dim*sizeof(unsigned int));
	if(godelNum==1){
		arr.arr[0]=0;
		arr.initialized=1;
		return arr;
	}
    int primeN,j=0;
	while(godelNum!=1){
	    if(arr.dim==j){
	        arr.arr=realloc(arr.arr,(arr.dim+1)*sizeof(unsigned int));
	        arr.dim+=1;
	    }
	    primeN=getNPrime(j+1);
	    arr.arr[j]=0;
	    while(godelNum%primeN==0){
	       godelNum=godelNum/primeN;
	       arr.arr[j]+=1;
	    }
	    arr.initialized=j;
	    j++;
	}
	return arr;
}

int leftPar(unsigned int n){
    int ret=0;
    n=n+1;
    while(n%2==0){
        ret+=1;
        n=n/2;
    }
    return ret;
}

unsigned int pow(int i, int pot) {
    if(pot==0){
        return 1;
    }
    else{
        for(int j=1;j<pot;j++){
            i=i*i;
        }
    }
    return i;
}

int rightPar(unsigned int n){
    n=(n+1)/pow(2,leftPar(n));
    return (n-1)/2;
}

void transalateFunctions(uintArrayT array) {
    int l,r,inst;
    for(int i=0;i<=array.initialized;i++){
        inst=array.arr[i];
        l=leftPar(inst);
        r=rightPar(inst);
        if(l!=0){
            printf("[A%d]",l);
        }
        l=leftPar(r);
        r=rightPar(r);
        if(l==0){
            if(r==0){
                printf("Y<-Y");
            }
            else{
                printf("X%d<-X%d",r,r);
            }
        }
        else if(l==1){
            if(r==0){
                printf("Y<-Y+1");
            }
            else{
                printf("X%d<-X%d+1",r,r);
            }

        }

        else if(l==2){
            if(r==0){
                printf("Y<-Y-1");
            }
            else{
                printf("X%d<-X%d-1",r,r);
            }

        }

        else if(l>2){
            if(r==0){
                printf("IF Y=/=0 GOTO A%d",l-2);
            }
            else{
                printf("IF X%d=/=0 GOTO A%d",r,l-2);
            }

        }
        putchar('\n');
    }
}

int main(int argc, char* argv[]){
    uintArrayT arr=getInstructNum(99);
    printArr(arr);
    transalateFunctions(arr);
    free(arr.arr);
}
