#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double*** make_3D_array(double ***array_3D,double a,double b,double c){
 int x,y;
  array_3D = (double ***)calloc(a, sizeof(double **));
   for(x=0;x<a;x++) {
    array_3D[x] = (double **)calloc(b, sizeof(double *));
    for(y=0;y<b;y++) {
     array_3D[x][y] = (double *)calloc(c, sizeof(double));
    }
   }
  return array_3D;
}

double** make_2D_array(double **array_2D,double a,double b){
 int x;
  array_2D = (double **)calloc(a, sizeof(double *));
    for(x=0;x<a;x++) {
      array_2D[x] = (double *)calloc(b, sizeof(double));
      }
  return array_2D;
}

void del_3D_array(double ***array_3D,double a,double b,double c){
 int x,y,z;
 for(x=0;x<a;x++){
  for(y=0;y<b;y++){
   for(z=0;z<c;z++){
    array_3D[x][y][z]=0;
   }
  }
 }
 for(x=0;x<a;x++){
  for (y=0;y<b;y++){
   free(array_3D[x][y]);
  }
 free(array_3D[x]);
 }
 free(array_3D);
}

void del_2D_array(double **array_2D,double a,double b){
 int x,y;
 for(x=0;x<a;x++){
  for(y=0;y<b;y++){
   array_2D[x][y]=0;
  }
 }
 for(x=0;x<a;x++){
   free(array_2D[x]);
  }
 free(array_2D);
}

void DOS(int b1,int orbit_num){
 FILE *f1; 		//DOSCAR
 FILE *f2;              //tot DOS
 FILE *f3;		//atomic DOS
 char s1;
 int a,b,c,d,e,g,h,x,y,z;
 double i,j,k,l,m,n,o;
 int a1,a2;		//tot_dos line, atomic_dos line
 int atom_num, step_num;
 double DB[10][10];     //data base
 char filename[100];

 f1 = fopen("./DOSCAR", "r");
  if (f1==NULL) {
   printf("Fail! Can't find the 'DOSCAR' file in this directory\n");
  }

 for (a=1;a<=4;a++) {
  fscanf(f1,"%lf",&i);
  DB[1][a]=i;
 }
 for (a=1;a<=6;a++) {
  fscanf(f1,"%lf",&i);
  DB[2][a]=i;
 }
 fscanf(f1,"%s",&s1);   //writed 'CAR' in DOSCAR file

 if (b1==0) {
 a1=3;
  if(orbit_num==4){
   a2=10;
  }
  if(orbit_num==6){
   a2=17;
  }
 }
 else {
 a1=5;
  if(orbit_num==4){
   a2=19;
  }
  if(orbit_num==6){
   a2=33;
  }    
 }

 atom_num = DB[1][1];

 for (a=1;a<=5;a++) {
  fscanf(f1,"%lf",&i);
  DB[3][a]=i;
 }

 step_num = DB[3][3];

 double **A, ***B, **C;
  A = make_2D_array(A,step_num+10,a1+1);
  B = make_3D_array(B,step_num+10,a2+1,atom_num+10); //B[a0][a1][a2]
  C = make_2D_array(C,atom_num+10,6);

 for (a=1;a<=step_num;a++) {
   for (b=1;b<=a1;b++) {
    fscanf(f1,"%lf",&n);
    A[a][b]=n;
   }
  }					//make total dos data sheet

 for(x=1;x<=atom_num;x++) {
  for (y=1;y<=5;y++) {
   fscanf(f1,"%lf",&j);
   C[x][y]=j;
   }                    		//cutting trash data
  for (a=1;a<=step_num;a++) {
   for (b=1;b<=a2;b++) {
    fscanf(f1,"%lf",&n);
    B[a][b][x]=n;
   }
  }
 }					//make atomic dos data sheets
 fclose(f1);

 f2=fopen("./DOSCAR_tot", "wt");
  for (a=1;a<=step_num;a++) {
   for (b=1;b<=a1;b++) {
     i=A[a][b];
     fprintf(f2,"%lf    ",i);
   }
  fprintf(f2,"\n");
  }                     //writing file
 fclose(f2);

 for (c=1;c<=atom_num;c++) {
  sprintf(filename,"./DOSCAR_atom#%d",c);
  f3=fopen(filename, "wt");
   for (a=1;a<=step_num;a++) {
    for (b=1;b<=a2;b++) {
      i=B[a][b][c];
      fprintf(f3,"%lf    ",i);
    }
   fprintf(f3,"\n");
   }                     //writing file
  fclose(f3);
 }

 printf("DOS splitting program finished\n");

 del_2D_array(A,step_num+10,a1+1);
 del_3D_array(B,step_num+10,a2+1,atom_num+10); //B[a0][a1][a2]
 del_2D_array(C,atom_num+10,6);
}


int main(void){
 FILE *f1;		//EIGENVAL
 FILE *f2;		//DOSCAR
 char s1;
 char *name1,*name2;    //eps file names
 int a,b,c,d,e,g,h,x,y,z;
 double i,j,k,l,m,n,o;
 int a1;		//total dos line	
 int b1,b2,b3;          //checking calculation option
 double c1,c2;		//option variable
 double d1,d2,d3;	//orbital dos (d? f?)
 int orbit_num;		//atom dos orbital number
 double delta_dos,count_dos,mag; 	//magnetization checking
 double max_dos,m_dos1,m_dos2,min_dos,val_dos1,val_dos2;	//dos maxvalue
 double max_band,min_band,m_band,val_band;		//metalic checking
 int metal;
 double VBM,CBM;	//valance band maximun, conduction band minimum
 double CBm1,CBm2;
 int atom_num,step_num,bnd_num,kpoint_num;
 double fermi_level,re_fermi;
 double DB_band[10][10], DB_dos[10][10]; 
 double CK_option[50];
 double CK_orbit[150];
 double DOS_unit;
 double MAX_input_dos,MIN_input_dos;

// printf("please press key 0 or 1; 0 mean spin-off, 1 mean spin-on\n");
// scanf("%d",&b1);
// printf("please press key  0 or 1; 0 mean 5.4.4 ver, 1 mean else\n");
// scanf("%d",&b2);

 name1 = (char *)calloc(10, sizeof(char));

 f2 = fopen("./DOSCAR", "r");
 for (a=1;a<=4;a++) {
  fscanf(f2,"%lf",&i);
  DB_dos[1][a]=i;
 }
 for (a=1;a<=6;a++) {
  fscanf(f2,"%lf",&i);
  DB_dos[2][a]=i;
 }
 fscanf(f2,"%s",&s1);   //writed 'CAR' in DOSCAR file
 for (a=1;a<=5;a++) {
  fscanf(f2,"%lf",&i);
  DB_dos[3][a]=i;
 }
 for (a=1;a<=16;a++){
  fscanf(f2,"%lf",&i);
  CK_option[a]=i;
 }
 fseek(f2,0L,SEEK_SET);
 fclose(f2);

 MAX_input_dos = DB_dos[3][1];
 MIN_input_dos = DB_dos[3][2];
 step_num = DB_dos[3][3];

 c1=(CK_option[10]-CK_option[1])-((MAX_input_dos-MIN_input_dos)/step_num*3);
 c2=(CK_option[16]-CK_option[1])-((MAX_input_dos-MIN_input_dos)/step_num*3);
 if(c1 < 0.001){
  b1=0;
  printf("spin-off\n");
 }
 else if(c2 < 0.001){
  b1=1;
  printf("spin-on\n");
 }
 			//option checking

 if (b1==0) {
 a1=3;
 }
 else {
 a1=5;
 }

 atom_num = DB_dos[1][1];
 step_num = DB_dos[3][3];
 fermi_level = DB_dos[3][4];
 bnd_num = DB_band[3][3];
 kpoint_num = DB_band[3][2];

 f2 = fopen("./DOSCAR", "r");
 for (a=1;a<=4;a++) {
  fscanf(f2,"%lf",&i);
 }
 for (a=1;a<=6;a++) {
  fscanf(f2,"%lf",&i);
 }
 fscanf(f2,"%s",&s1);   //writed 'CAR' in DOSCAR file
 for (a=1;a<=5;a++) {
  fscanf(f2,"%lf",&i);
 }
 for (a=1;a<=step_num;a++) {
   for (b=1;b<=a1;b++) {
    fscanf(f2,"%lf",&n);
  }
 }                                     //make total dos data sheet
 for (x=1;x<=5;x++) {
   fscanf(f2,"%lf",&i);
 }                                    //cutting trash data
 for(x=1;x<=100;x++) {
   fscanf(f2,"%lf",&i);
   CK_orbit[x]=i;
 }
 fseek(f2,0L,SEEK_SET);
 fclose(f2);

// printf("insert orbital number : 4=d_orbital, 6=f_orbital\n");
// scanf("%d",&orbit_num);

 if(b1==0){
  d1 = (CK_orbit[31]-CK_orbit[1])-((MAX_input_dos-MIN_input_dos)/step_num*3);
  d2 = (CK_orbit[52]-CK_orbit[1])-((MAX_input_dos-MIN_input_dos)/step_num*3);
 }
 if(b1==1){
  d1 = (CK_orbit[58]-CK_orbit[1])-((MAX_input_dos-MIN_input_dos)/step_num*3);
  d2 = (CK_orbit[100]-CK_orbit[1])-((MAX_input_dos-MIN_input_dos)/step_num*3);
 }
 d3 = (MAX_input_dos-MIN_input_dos)/step_num*3;
// printf("%lf	\n",d1);
// printf("%lf    \n",d2);
// printf("%lf    \n",d3);

 orbit_num=0;

 if(d1 < 0.001){
  orbit_num=4;
 }
 else if(d2 < 0.001){
  orbit_num=6;
 }
 else{
  orbit_num=orbit_num;
 }

 if(orbit_num==4){
  printf("considered 'd' orbital\n");
 }
 else if(orbit_num==6){
  printf("considered 'f' orbital\n");
 }
 else{
  printf("orbit error\n");
 }

 printf("decom-DOS program start\n");
 DOS(b1,orbit_num);

 printf("Finish!\n");

return 0;

}
