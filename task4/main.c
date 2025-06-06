#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//analyzing input file suggested lsa threshold = 0.8+0.3/2 = 0.55 and ir sensor threshold = 80
#define LsaThresh 0.55
#define IRThresh 80
int main(){
    //reading input files
    FILE *fin = fopen("LSA_IR_data.txt","r");
    FILE *fout = fopen("output.txt","w");
}