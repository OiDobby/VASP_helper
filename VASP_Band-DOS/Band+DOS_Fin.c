#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
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

void DOS(int b1,int b2,int orbit_num){
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
   a2=4;
  }
  if(orbit_num==6){
   a2=5;
  }
 }
 else {
 a1=5;
  if(orbit_num==4){
   a2=7;
  }
  if(orbit_num==6){
   a2=9;
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

 printf("reading total DOS\n");
 
 for (a=1;a<=step_num;a++) {
   for (b=1;b<=a1;b++) {
    fscanf(f1,"%lf",&n);
    A[a][b]=n;
   }
  }					//make total dos data sheet

 printf("reading atomic DOS\n");
 for(x=1;x<=atom_num;x++) {
  printf("#%d	",x);
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

printf("\nwrite total DOS\n");

 f2=fopen("./DOSCAR_tot", "wt");
  for (a=1;a<=step_num;a++) {
   for (b=1;b<=a1;b++) {
     i=A[a][b];
     fprintf(f2,"%lf    ",i);
   }
  fprintf(f2,"\n");
  }                     //writing file
 fclose(f2);

 printf("write atomic DOS\n");
 for (c=1;c<=atom_num;c++) {
  printf("#%d	",c);
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

 printf("\nDOS splitting program finished\n");

 del_2D_array(A,step_num+10,a1+1);
 del_3D_array(B,step_num+10,a2+1,atom_num+10); //B[a0][a1][a2]
 del_2D_array(C,atom_num+10,6);
}

void band(int b1, int b2, int kpoint_num){
 FILE *f1;				//EIGENVAL 
 FILE *f2;				//up-eigenval
 FILE *f3;				//down-eigenval
 FILE *f4;				//kpoint-path
 char s1;
 char *name1,*name2;			//eps file names
 int a,b,c,d,e,g,h,x,y,z;
 double i,j,k,l,m,n,o;
 double c1;				//I don't know what is this
 double a0,a1,a2;			//data sheet X Y Z
 double kpn_sum,delta_k,num_k;		//k point integration, delta k
 double first_kpnt;
 int num_kpath;
 double DB[10][10];			//data base

 if (b2==0) {
  if (b1==0) {
   a1=3;
  }
  else {
   a1=5;
  }
 }
 else {
  if (b1==0) {
   a1=2;
  }
  else {
   a1=3;
  }
 }

 f1 = fopen("./EIGENVAL", "r");
  if (f1==NULL) {
   printf("Fail! Can't find the 'EIGENVAL' file in this directory\n");
  } 			//consider spin in calculation?

 for (a=1;a<=4;a++) {
  fscanf(f1,"%lf",&i);
  DB[1][a]=i;
 }
 for (a=1;a<=6;a++) {
  fscanf(f1,"%lf",&i);
  DB[2][a]=i;
 }
 fscanf(f1,"%s",&s1);	//writed 'CAR' in EIGENVAL file 
 for (a=1;a<=3;a++) {
  fscanf(f1,"%lf",&i);
  DB[3][a]=i;
 } 			//Data base numbers

 c1=DB[3][1]; 		//number of electron?
 a0=DB[3][3]; 		//band number = X axis (first number in array)
 a2=DB[3][2]; 		//kpoint number = Z axis

 double ***A, ***B, ***C;
 double **US, **DS, **D;
  A = make_3D_array(A,a0+10,a1+1,a2+10); //A[a0][a1][a2]
  B = make_3D_array(B,a0+10,a1+1,a2+10); 
  C = make_3D_array(C,a2+10,5,5);
  US = make_2D_array(US,a2+10,a0+10); //US[a2][a0]
  DS = make_2D_array(DS,a2+10,a0+10);
  D = make_2D_array(D,a2+10,5);

 for(x=1;x<=a2;x++) {
  for (y=1;y<=4;y++) {
   fscanf(f1,"%lf",&j);
   C[x][y][1]=j;
   }			//K-point gathering
  for (a=1;a<=a0;a++) {
   for (b=1;b<=a1;b++) {
    fscanf(f1,"%lf",&n);
    A[a][b][x]=n;	
   }
  }
 }			//make data sheets (scaning band# and values)

num_kpath = 0;
 for(x=1;x<a2;x++) {
  if(fabs(C[x][1][1]-C[x+1][1][1])<1E-15){
   if(fabs(C[x][2][1]-C[x+1][2][1])<1E-15){
    if(fabs(C[x][3][1]-C[x+1][3][1])<1E-15){
     num_kpath = num_kpath + 1;
    }
   }
  }
 }
 num_kpath = num_kpath + 1;
 //printf("%d	\n",num_kpath);

 kpn_sum = 0;
 for(x=1;x<=num_kpath;x++){
  for(a=kpoint_num/num_kpath*(x-1)+1;a<kpoint_num/num_kpath*x;a++){
   for(y=1;y<=3;y++){
    d=kpoint_num/num_kpath*(x-1)+1;
    i=C[d][y][1];
    j=C[d+1][y][1];
    k=j-i;
    C[x][y][2]=k;
    C[a][y][3]=k;
   }
  }
 }
 for(x=1;x<=a2;x++){
  i=C[x][1][3];
  j=C[x][2][3];
  k=C[x][3][3];
  l=sqrt(i*i+j*j+k*k);
  delta_k=fabs(l);                    //K-point delta calculation
  for (a=1;a<=a0;a++) {
   for (b=1;b<=a1;b++) {
    B[a+1][b-1][x]=A[a][b][x];
    B[1][b-1][x]=kpn_sum;
   }
  }                                   //change location in data sheet
 D[x][1] = kpn_sum;
 kpn_sum=kpn_sum+delta_k;             //gnuplot x path integration
// printf("%lf	\n",kpn_sum);
 } 

 for(a=1;a<=a2;a++) {
  for (b=1;b<=a0+1;b++){
   US[a][b]=B[b][1][a];
   DS[a][b]=B[b][2][a];
  }
 }			//sum data sheets in one matrix + transpose
 fclose(f1);

 f2=fopen("./up-eigenval", "wt");
  for (a=1;a<=a2;a++) {
   for (b=1;b<=a0+1;b++) {
     i=US[a][b];
     fprintf(f2,"%lf    ",i);
   }
  fprintf(f2,"\n");
  }			//writing file
 fclose(f2);

 f3=fopen("./down-eigenval", "wt");
  for (a=1;a<=a2;a++) {
   for (b=1;b<=a0+1;b++) {
     i=DS[a][b];
     fprintf(f3,"%lf    ",i);
   }			
  fprintf(f3,"\n");
  }			//writing file
 fclose(f3);

 f4=fopen("./kpnt-path", "wt");
  first_kpnt=D[1][1];
  fprintf(f4,"%d     \n",num_kpath+1);
  fprintf(f4,"%lf     \n",first_kpnt);
  for (a=1;a<=num_kpath;a++) {
   i=D[40*a][1];
   fprintf(f4,"%lf     \n",i);
  }
 fclose(f4);

 printf("EIGENVAL file success separation\n");

 printf("band splitting program finished\n");

 del_3D_array(A,a0+10,a1+1,a2+10); //A[a0][a1][a2]
 del_3D_array(B,a0+10,a1+1,a2+10);
 del_3D_array(C,a2+10,5,3);
 del_2D_array(US,a2+10,a0+10); //US[a2][a0]
 del_2D_array(DS,a2+10,a0+10);
 del_2D_array(D,a2+10,5);

}

void gnuband(FILE *filename,char *material_name,double fermi_level,int bnd_num,double mag,double min_dos,double DOS_unit){
 FILE *f1;		//kpnt-path
 int num_kpath;
 double k_sym[100];
 int a;
 double i;

  f1 = fopen("./kpnt-path", "r");
  fscanf(f1,"%d",&num_kpath); 
  for(a=1;a<=num_kpath;a++) {
   fscanf(f1,"%lf",&i);
   k_sym[a]=i;
  }
  fclose(f1);

  filename=fopen("./gnuband", "wt");
   fprintf(filename,"set term postscript eps color enhanced\n");
   fprintf(filename,"set output \"%s-band.eps\"\n",material_name);
   fprintf(filename,"set size 0.70,1.00\n");
   fprintf(filename,"set size ratio 1.0\n");
   fprintf(filename,"set multiplot layout 1,1\n");
   fprintf(filename,"set nokey\n");
   fprintf(filename,"set yr [-4:4]\n");
   fprintf(filename,"set xtic (\"{/Symbol G}\"0,");
   for(a=2;a<num_kpath;a++){
    fprintf(filename," \"{/Symbol G}\"%lf,",k_sym[a]);
   }
   fprintf(filename," \"{/Symbol G}\"%lf)\n",k_sym[num_kpath]);
   fprintf(filename,"set mxtic 2\n");
   fprintf(filename,"set ytic 1\n");
   fprintf(filename,"set mytic 2\n");
   fprintf(filename,"set grid xtics lw 4\n");
   fprintf(filename,"set xzeroaxis lw 4\n");
   fprintf(filename,"set xtic font \"Arial,30\"\n");
   fprintf(filename,"set ytic font \"Arial,30\"\n");
   fprintf(filename,"set tics font \"Arial,30\"\n");
   fprintf(filename,"set tmargin 3\n");
   fprintf(filename,"set bmargin 6\n");
   fprintf(filename,"set lmargin 12\n");
   fprintf(filename,"set rmargin 6\n");
   fprintf(filename,"set xlabel 'wave vector' font \"Arial, 36\" offset 0,-1.5,0\n");
   fprintf(filename,"set ylabel 'E-E_F (eV)' font \"Arial, 36\" offset -2,0,0\n");
   fprintf(filename,"set origin -0.15,0.0\n");
   fprintf(filename,"plot    \"up-eigenval\" using ($1):($2+%lf) w l  lw 4 lt 1 lc 0 ,\\\n",fermi_level*-1);
   for (a=3;a<bnd_num+1;a++) {
    fprintf(filename,"        \"up-eigenval\" using ($1):($%d+%lf) w l  lw 4 lt 1 lc 0 ,\\\n",a,fermi_level*-1);
   }
   fprintf(filename,"        \"up-eigenval\" using ($1):($%d+%lf) w l  lw 4 lt 1 lc 0 \n",bnd_num+1,fermi_level*-1);
   fprintf(filename,"#plot    \"down-eigenval\" using ($1):($2+%lf) w l  lw 4 lt 1 lc 1 ,\\\n",fermi_level);
   for (a=3;a<bnd_num+1;a++) {
    fprintf(filename,"        \"down-eigenval\" using ($1):($%d+%lf) w l  lw 4 lt 1 lc 1 ,\\\n",a,fermi_level*-1);
   }
   fprintf(filename,"        \"down-eigenval\" using ($1):($%d+%lf) w l  lw 4 lt 1 lc 1 \n",bnd_num+1,fermi_level*-1);
 
  fclose(filename);
 
}

void gnudos(FILE *filename,char *material_name,double min_dos,double DOS_unit,double fermi_level,double mag){

 if(mag==0){
   min_dos = 0.1;
  }
  else{
   min_dos = DOS_unit*-3;
  }

 filename=fopen("./gnudos", "wt");
  fprintf(filename,"set term postscript eps color enhanced\n");
  fprintf(filename,"set output \"%s-tdos.eps\"\n",material_name);
  fprintf(filename,"set size 0.70,1.00\n");
  fprintf(filename,"set size ratio 1.0\n");
  fprintf(filename,"set multiplot layout 1,1\n");
  fprintf(filename,"set nokey\n");
  fprintf(filename,"set xr [-4:4]\n");
  fprintf(filename,"set yr [%lf:%lf]\n",min_dos,DOS_unit*3);
  fprintf(filename,"set xtic 1\n");
  fprintf(filename,"set mxtic 2\n");
  fprintf(filename,"set ytic %lf\n",DOS_unit);
  fprintf(filename,"set mytic 2\n");
  fprintf(filename,"set xzeroaxis lw 4\n");
  fprintf(filename,"set yzeroaxis lw 4\n");
  fprintf(filename,"set xtic font \"Arial,30\"\n");
  fprintf(filename,"set ytic font \"Arial,30\"\n");
  fprintf(filename,"set tics font \"Arial,30\"\n");
  fprintf(filename,"set tmargin 3\n");
  fprintf(filename,"set bmargin 6\n");
  fprintf(filename,"set lmargin 12\n");
  fprintf(filename,"set rmargin 6\n");
  fprintf(filename,"set xlabel 'E-E_F (eV)' font \"Arial, 36\" offset 0,-1.5,0\n");
  fprintf(filename,"set ylabel 'Total DOS' font \"Arial, 36\" offset -2,0,0\n");
  fprintf(filename,"set origin -0.15,0.0\n");
  fprintf(filename,"plot    \"DOSCAR_tot\" using ($1+%lf):($2) w l  lw 4 lt 1 lc 0 ,\\\n",fermi_level*-1);
  fprintf(filename,"        \"DOSCAR_tot\" using ($1+%lf):($3*-1) w l  lw 4 lt 1 lc 1 \n",fermi_level*-1);

  fclose(filename);

}

int main(void){
 FILE *f1;		//EIGENVAL
 FILE *f2;		//DOSCAR
 FILE *f3,*f4;		//up-eigenval, down-eigenval
 FILE *f5;		//DOSCAR_tot
 FILE *fg1;             //gnuband
 FILE *fg2;             //gundos
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
 double CK_option[10][10];
 double CK_orbit[50];
 double DOS_unit;
 double MAX_input_dos,MIN_input_dos;

// printf("please press key 0 or 1; 0 mean spin-off, 1 mean spin-on\n");
// scanf("%d",&b1);
// printf("please press key  0 or 1; 0 mean 5.4.4 ver, 1 mean else\n");
// scanf("%d",&b2);

 name1 = (char *)calloc(10, sizeof(char));

 printf("This file made by JW.Chae 23-01-04 version\n");
 printf("We will make gnuband file. Please enter eps file's name.\n");
 scanf("%s",name1);


 f1 = fopen("./EIGENVAL", "r");
 for (a=1;a<=4;a++) {
  fscanf(f1,"%lf",&i);
  DB_band[1][a]=i;
 }
 for (a=1;a<=6;a++) {
  fscanf(f1,"%lf",&i);
  DB_band[2][a]=i;
 }
 fscanf(f1,"%s",&s1);   //read 'CAR' in DOSCAR file
 for (a=1;a<=3;a++) {
  fscanf(f1,"%lf",&i);
  DB_band[3][a]=i;
 }
 for (a=1;a<=4;a++) {
  fscanf(f1,"%lf",&i);
  DB_band[4][a]=i;
 }
 for (a=1;a<=2;a++) {
  for (b=1;b<=5;b++){
   fscanf(f1,"%lf",&i);
   CK_option[a][b]=i;
  }
 }			//getting data for option check - spin(up,down) & VASP ver
 fseek(f1,0L,SEEK_SET);
 fclose(f1);

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
 fseek(f2,0L,SEEK_SET);
 fclose(f2);
 
 c1=CK_option[2][1]-CK_option[1][1];
 c2=CK_option[1][4]-CK_option[1][1];
 if(c1==1){
  b2=0;
  b1=1;
  printf("Over 5.44 ver and spin-on\n");
 }
 else{
  if(c1==0){
   b2=0;
   b1=0;
   printf("Over 5.44 ver and spin-off\n");
  }
  else{
   if(c2==1){
    b2=1;
    b1=1;
    printf("Under 5.44 ver and spin-on\n");
   }
   else{
    b2=1;
    b1=0;
    printf("Under 5.44 ver and spin-off\n");
   }
  }
 }			//option checking

 if (b1==0) {
 a1=3;
 }
 else {
 a1=5;
 }

 atom_num = DB_dos[1][1];
 MAX_input_dos = DB_dos[3][1];
 MIN_input_dos = DB_dos[3][2];
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
 for(x=1;x<=28;x++) {
   fscanf(f2,"%lf",&i);
   CK_orbit[x]=i;
 }
 fseek(f2,0L,SEEK_SET);
 fclose(f2);

// printf("insert orbital number : 4=d_orbital, 6=f_orbital\n");
// scanf("%d",&orbit_num);

 orbit_num=0;

 if (b1 ==1){
  d1 = (CK_orbit[22]-CK_orbit[1])-((MAX_input_dos-MIN_input_dos)/step_num*3);
  d2 = (CK_orbit[28]-CK_orbit[1])-((MAX_input_dos-MIN_input_dos)/step_num*3);
  d3 = (MAX_input_dos-MIN_input_dos)/step_num*3;
  if(d1 < 0.001){
   orbit_num=4;
  }
  else if(d2 < 0.001){
   orbit_num=6;
  }
  else{
   orbit_num=orbit_num;
  }
 }

 if (b1 ==0){
  d1 = (CK_orbit[13]-CK_orbit[1])-((MAX_input_dos-MIN_input_dos)/step_num*3);
  d2 = (CK_orbit[16]-CK_orbit[1])-((MAX_input_dos-MIN_input_dos)/step_num*3);
  d3 = (MAX_input_dos-MIN_input_dos)/step_num*3;
  if(d1 < 0.001){
   orbit_num=4;
  }
  else if(d2 < 0.001){
   orbit_num=6;
  }
  else{
   orbit_num=orbit_num;
  }
 }

 printf("orbit_num=%d\n",orbit_num);
 printf("band program start\n");
 band(b1,b2,kpoint_num);
 printf("DOS program start\n");
 DOS(b1,b2,orbit_num);

 printf("checking properties\n");

 double ***eigenval,**tdos, ***band_gap;
 eigenval = make_3D_array(eigenval,kpoint_num+10,bnd_num+10,5);
 tdos = make_2D_array(tdos,step_num+10,a1+10);
 band_gap = make_3D_array(band_gap,bnd_num+10,5,5);


 f3=fopen("./up-eigenval", "r"); 
 for (a=1;a<=kpoint_num;a++) {
  for (b=0;b<=bnd_num;b++) {
   fscanf(f3,"%lf",&i);
   eigenval[a][b][1]=i;
   }
  }
  fclose(f3);

 f4=fopen("./down-eigenval", "r");
 for (a=1;a<=kpoint_num;a++) {
  for (b=0;b<=bnd_num;b++) {
   fscanf(f4,"%lf",&i);
   eigenval[a][b][2]=i;
   }
  }
 fclose(f4);

 f5=fopen("./DOSCAR_tot", "r");
 for (a=0;a<step_num;a++) {
  for (b=0;b<a1;b++) {
   fscanf(f5,"%lf",&i);
   tdos[a][b]=i;
   }
  }
 fclose(f5);

//file reading

 count_dos = 0;

 if(b1 == 1){
  for(a=1;a<step_num;a++) {
   delta_dos = tdos[a][1]-tdos[a][2];
    if (fabs(delta_dos) > 0.01 ){
     count_dos = count_dos +1;
    }
    else{
     count_dos = count_dos;
    }
  }
 }

 if(b1 == 0){
   printf("***  spin effect : Off       ***\n");
  }
 else{
   printf("***  spin effect : On        ***\n");
  }


 if(count_dos > step_num*0.1){
  mag=1;
  printf("***	spin effect : O		***\n");
 }
 else{
  mag=0;
  printf("***	spin effect : X		***\n");
 }

//spin effecj check

 m_dos1 = tdos[1][1];
 for(a=2;a<step_num;a++) {
  val_dos1 = tdos[a][1];
   if (val_dos1>=m_dos1){
    m_dos1 = val_dos1;
   }
   else{
    m_dos1 = m_dos1;
   }
 }

 m_dos2 = tdos[1][2];
 for(a=2;a<step_num;a++) {
  val_dos2 = tdos[a][2];
   if (val_dos2>=m_dos2){
    m_dos2 = val_dos2;
   }
   else{
    m_dos2 = m_dos2;
   }
 }

 if (m_dos1>m_dos2){
  max_dos = m_dos1;
 }
 else{
  max_dos = m_dos2;
 }

 printf("***	max in DOS : %lf	***\n",max_dos);

 DOS_unit = ceil(max_dos/3);

//max value check

 for(c=1;c<=2;c++){
  for(b=1;b<=bnd_num;b++){
   m_band = eigenval[1][b][c];
   for(a=2;a<=kpoint_num;a++){
    val_band = eigenval[a][b][c];
    if(val_band>=m_band){
     m_band = val_band;
    }
    else{
     m_band = m_band;
    }
   }
   max_band = m_band;
   m_band = eigenval[1][b][c];
   for(a=2;a<=kpoint_num;a++){
    val_band = eigenval[a][b][c];
    if(val_band<=m_band){
     m_band = val_band;
    }
    else{
     m_band = m_band;
    }
   }
   min_band = m_band;
   
   band_gap[b][2][c] = max_band;
   band_gap[b][1][c] = min_band;

// printf("%lf,%lf,%lf\n",min_band,max_band,fermi_level);
  }
 }

 for(b=1;b<step_num;b++){
  i = tdos[b][0];
  if(i<=fermi_level){
   j = tdos[b+1][0];
   k = b;
   CBm1 = tdos[b+1][1];
   CBm2 = tdos[b+1][2];
  }
  else{
   CBm1=CBm1;
   CBm2=CBm2;
  }
 }

// printf("%lf,   %lf     \n",CBm1,CBm2);

 if(CBm1>0){
  metal = 1;
 }
 else{
  if(CBm2>0){
   metal = 1;
  }
  metal = 0;
 }

 if(metal==1){
  printf("***	band gap : X		***\n");
 }
 else{
  printf("***	band gap : O		***\n");
 }

 for(c=1;c<=2;c++){
  for(b=1;b<=bnd_num;b++){
   if(eigenval[1][b][c]-fermi_level<=0){
    VBM = band_gap[1][2][c];
    if(band_gap[b][2][c]-VBM>=0){
     VBM = band_gap[b][2][c];
     x=b;
    }
    else{
     VBM = VBM;
    }
   } 
   if(eigenval[1][b][c]-fermi_level>=0){
    CBM = band_gap[x+1][1][c];
    if(band_gap[b][1][c]-CBM<=0){
     CBM = band_gap[b][1][c];
    }
    else{
     CBM = CBM;
    }
   }
  }
 }

 printf("***	VBM : %lf		***\n",VBM);
 printf("***	CBM : %lf		***\n",CBM);

 re_fermi = (VBM+CBM)/2;

 if(metal==0){
  fermi_level = re_fermi;
 }
 if(metal==1){
  fermi_level = fermi_level;
 } 

 printf("***	fermi : %lf	***\n",fermi_level);
 printf("***    	orbit : %d		***\n",orbit_num);
 printf("write gnu files\n");

 gnuband(fg1,name1,fermi_level,bnd_num,mag,min_dos,DOS_unit);
 gnudos(fg2,name1,min_dos,DOS_unit,fermi_level,mag);

 system("gnuplot gnuband");
 system("gnuplot gnudos");

 printf("Finish!\n");

return 0;

}
