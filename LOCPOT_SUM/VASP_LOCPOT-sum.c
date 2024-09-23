#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double*** make_3d_array(double a1, double a3, double a2){
 int x,y;
 double ***Arr;
  Arr = (double ***)calloc(a1, sizeof(double **));
   for(x=0;x<=a1;x++) {
    Arr[x] = (double **)calloc(a3, sizeof(double *));
   }
   for(x=0;x<=a1;x++) {
    for(y=0;y<=a3;y++) {
     Arr[x][y] = (double *)calloc(a2, sizeof(double));
    }
   }
 return Arr;
}

int main(void)
{
/*	outline
0.frst is first, i need to consider the full structure of this code.
i want dealing 3D_ gird data file as what i need.
1.set basic parameters
index,array,pointer,calculation_function.
2.read minimum information from original file = need file input
informations are structure information and main 3Dgrid data.
3.using malloc for make flexible array.
3D array for calculation
4.dealing the data from original file and matching this for 
main purpose. mainly cutting off except specific range, 
gain derivertive, and basic calculate between two or more files.
5.using functions(may be 1~3 parts), calculate the array.
6.cleaning up the toatal processes.
*/

//declaration variables start
int NGX=300,NGY=300,NGZ=300; 		//declare number of grids
int x,y,z;                                      //declare number of arry index
int test1,test2,test3;
int TOTAL_ATOM;
double i,j,k,h,g;
double L1[4],L2[4],L3[4],L4;                    //latice vector 
double a1,a2,a3;				//latice size 
double d1=0,d2=0,d3=0;                          //
char txt[91];                                   //
FILE *ORIGINAL_CAR;                             //original file pointer
FILE *TEMPORARY1_CAR;                           //temporary file1 pointer
FILE *TEMPORARY2_CAR;                           //temporary file2 pointer
FILE *TEMPORARY3_CAR;                           //temporary file3 pointer
FILE *FINAL_CAR;                                //final file pointer
double ***ORIGINAL_3D_CAR,  ***TEMPORARY1_3D_CAR,  ***TEMPORARY2_3D_CAR,  ***TEMPORARY3_3D_CAR;
double ***FINAL_3D_CAR;
//declaration variables end


//find number of atom in original file start
remove("./TEMP.txt");
remove("./Original_3D_Grid_Data_Only");
remove("./Final_3D_Grid_Data_Only");


ORIGINAL_CAR = fopen("./LOCPOT","r");
for(test1=1;test1<8;test1++)
{
fgets(txt,92,ORIGINAL_CAR);
if(test1>5)
{
//printf("%03d %s",test1,txt);
printf("%s",txt);
}
}
fclose(ORIGINAL_CAR);

TEMPORARY1_CAR = fopen("./TEMP.txt","w");
fprintf(TEMPORARY1_CAR,"%s",txt);
fclose(TEMPORARY1_CAR);

TEMPORARY1_CAR = fopen("./TEMP.txt","r");
TOTAL_ATOM = 0;
while(!feof(TEMPORARY1_CAR))
{
fscanf(TEMPORARY1_CAR,"%d ",&test2);
TOTAL_ATOM = TOTAL_ATOM + test2;
//printf("%03d \n",TOTAL_ATOM);
}
printf("TOTAL_ATOM# = %03d \n",TOTAL_ATOM);
fclose(TEMPORARY1_CAR);
//find number of atom in original file end

//reciving structure data from original file start
ORIGINAL_CAR = fopen("./LOCPOT","r");
TEMPORARY1_CAR = fopen("./TEMP.txt","w");
TEMPORARY2_CAR = fopen("./POSCAR","w");
for(test1=1;test1<8+TOTAL_ATOM+3;test1++)
{
fgets(txt,92,ORIGINAL_CAR);
if(test1<8+TOTAL_ATOM+3)
fprintf(TEMPORARY2_CAR,"%s",txt);
if(test1>8+TOTAL_ATOM+1)
fprintf(TEMPORARY1_CAR,"%s",txt);
}

fclose(ORIGINAL_CAR);
fclose(TEMPORARY1_CAR);
fclose(TEMPORARY2_CAR);


TEMPORARY1_CAR = fopen("./TEMP.txt","r");
for(test2=1;test2<4;test2++)
{
if(test2==1)
fscanf(TEMPORARY1_CAR,"%d",&NGX);
if(test2==2)
fscanf(TEMPORARY1_CAR,"%d",&NGY);
if(test2==3)
fscanf(TEMPORARY1_CAR,"%d",&NGZ);
}
printf("NGX=%03d NGY=%03d NGZ=%03d \n",NGX,NGY,NGZ);
fclose(TEMPORARY1_CAR);

//array set start
 ORIGINAL_3D_CAR = make_3d_array(NGX+2,NGY+2,NGZ+2);
 TEMPORARY1_3D_CAR = make_3d_array(NGX+2,NGY+2,NGZ+2);
 TEMPORARY2_3D_CAR = make_3d_array(NGX+2,NGY+2,NGZ+2);
 TEMPORARY3_3D_CAR = make_3d_array(NGX+2,NGY+2,NGZ+2);
 FINAL_3D_CAR = make_3d_array(NGX+2,NGY+2,NGZ+2);
//array set end


ORIGINAL_CAR = fopen("./LOCPOT","r");
TEMPORARY2_CAR = fopen("./Original_3D_Grid_Data_Only","a");
for(test1=1;test1<8+TOTAL_ATOM+3+(NGX*NGY*NGZ/5.0);test1++)
{
fgets(txt,92,ORIGINAL_CAR);
if(test1>8+TOTAL_ATOM+2)
fprintf(TEMPORARY2_CAR,"%s",txt);
}
fclose(ORIGINAL_CAR);
fclose(TEMPORARY2_CAR);

//reciving structure data from original file end

TEMPORARY3_CAR = fopen("./POSCAR","r");
fscanf(TEMPORARY3_CAR,"%lf",&L4);
for(x=1;x<4;x++){
fscanf(TEMPORARY3_CAR,"%lf",&L1[x]);
}
for(y=1;y<4;y++){
fscanf(TEMPORARY3_CAR,"%lf",&L2[y]);
}
for(z=1;z<4;z++){
fscanf(TEMPORARY3_CAR,"%lf",&L3[z]);
}
fclose(TEMPORARY3_CAR);

a1 = sqrt(pow(L1[1],2)+pow(L1[2],2)+pow(L1[3],2));
a2 = sqrt(pow(L2[1],2)+pow(L2[2],2)+pow(L2[3],2));
a3 = sqrt(pow(L3[1],2)+pow(L3[2],2)+pow(L3[3],2));

printf("a1=%lf a2=%lf a3=%lf \n",a1,a2,a3);

//calculation part start
TEMPORARY2_CAR = fopen("./Original_3D_Grid_Data_Only","r");
for(z=1;z<NGZ+1;z++){
for(y=1;y<NGY+1;y++){
for(x=1;x<NGX+1;x++){
fscanf(TEMPORARY2_CAR,"%lf",&ORIGINAL_3D_CAR[x][y][z]);
}}}
fclose(TEMPORARY2_CAR);

for(z=1;z<NGZ+1;z++){
ORIGINAL_3D_CAR[0][0][z] = 0 ;
}

for(y=1;y<NGY+1;y++){
for(x=1;x<NGX+1;x++){
ORIGINAL_3D_CAR[x][y][0] = 0 ;
}
}

for(z=1;z<NGZ+1;z++){
for(x=1;x<NGX+1;x++){
ORIGINAL_3D_CAR[x][0][z] = 0 ;
}
}

for(z=1;z<NGZ+1;z++){
for(y=1;y<NGY+1;y++){
ORIGINAL_3D_CAR[0][y][z] = 0 ;
}
}

for(z=1;z<NGZ+1;z++){
 for(x=1;x<NGX+1;x++){
  for(y=1;y<NGY+1;y++){
   ORIGINAL_3D_CAR[x][0][z] = ORIGINAL_3D_CAR[x][0][z] + ORIGINAL_3D_CAR[x][y][z] ;
  }
 }
}

for(z=1;z<NGZ+1;z++){
 for(x=1;x<NGX+1;x++){
  ORIGINAL_3D_CAR[0][0][z] = ORIGINAL_3D_CAR[0][0][z] + ORIGINAL_3D_CAR[x][0][z] ;
 }
}

for(z=1;z<NGZ+1;z++){
 ORIGINAL_3D_CAR[0][0][0] = ORIGINAL_3D_CAR[0][0][0] + ORIGINAL_3D_CAR[0][0][z] ;
}

j = NGZ;
k = ORIGINAL_3D_CAR[0][0][0];
h = NGX*NGY*NGZ;
g = k/h;

printf("Total number of electron=%lf \n",k);

FINAL_CAR = fopen("./Final_3D_Grid_Data_Only","a");
for(z=1;z<NGZ+1;z++){
i = z/j*a3 ;
fprintf(FINAL_CAR,"%lf	",i);
fprintf(FINAL_CAR,"%12.11E  ",ORIGINAL_3D_CAR[0][0][z]/h);
fprintf(FINAL_CAR,"\n");
}
fclose(FINAL_CAR);
//calculation part end

 system("mv Final_3D_Grid_Data_Only ./LOCPOT_sum-c");
 system("rm Original_3D_Grid_Data_Only TEMP.txt POSCAR");

return 0;
}
