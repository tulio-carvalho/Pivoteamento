#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *fp;

void imprime1( double **M, int dim) // função que imprime a matriz
{
	printf("\n");
	for(int i=0;i<dim;i++) 
	{	for(int j=0;j<dim+1;j++) 
			
			printf("%3f ",M[i][j]);	  
		
		puts("");
	}		
	printf("\n*******************************\n");
}

//Função para ler a matriz do arquivo
double **leitura( char *matriz, int *dim)
{
        int  i, j;
        double **M;
        float a;
        fp = fopen(matriz,"r");
        i = fscanf(fp,"%d",dim);

        M = malloc( *dim *sizeof(double *));
        for(i=0; i<*dim; i++)
        {
                M[i]= malloc((*dim+1)*sizeof(double));
        }
        i =0;
        j = 0;

        while (fscanf(fp,"%f",&a)!= EOF)
        {
                M[i][j]=a;
                j++;
                if (j== *dim+1)
                {
                        j= 0;
                        i++;
                }
        }

        return (M);
}	

//Função para trocar as linhas da matriz
void troca(double *M1, double *M2, int dim)
{	double *m; // matriz auxiliar
	int i;
	
	m= (double*)malloc((dim+1)*sizeof(double));
	
	for(i=0;i<=dim;i++)
	{	m[i] = M1[i];
		M1[i] = M2[i];
		M2[i] = m[i];
	}
}

double **triangsup(double **M, int dim) // função triangular superior
{
	int i,j,k,l,v;
	double auxiliar; // variável auxiliar para calculo dos passos da triangularização
	v=-1;
	
	for(k=0;k<dim;k++) 
	{
		for (l=k+1;l<dim;l++)
		{
			if(M[k][k]<fabs(M[l][k]));
				v=1;
			if(v!=-1)
				troca(M[k],M[v],dim);
			
			for(i=k+1;i<dim;i++)
			{	
			 	auxiliar=(M[i][k]/M[k][k]);
 			 	for(j=k;j<=dim;j++)
 			 	{
 			 		M[i][j]=M[i][j]-(auxiliar*M[k][j]);
 			 	}
			}
		}
		v=-1;
	}
	return M;
}

void subsreversa(double **M, double* raizes, int dim)
{
	double x[dim], soma[dim], auxiliar;
	int i, j;
	
	for(i=dim-1;i>=0;i--)
	{
		soma[i]=0;
		
		for(j=i;j<=dim;j++)
		{
			soma[i]=soma[i]+M[i][j-1]*raizes[j-1];
		}
		
		auxiliar=M[i][dim];
		x[i]=auxiliar-soma[i];
		raizes[i]=x[i]/M[i][i];
	}	
}


int main (int argc , char **argv )
{
  double **M;
  double *raizes;
  int i, dim;

  printf("\nA matriz lida é:\n");
  M=leitura(argv[1] ,&dim);
  imprime1(M,dim);
   printf("\nMatriz triangularizada:\n");
  M=triangsup(M, dim);
  imprime1(M, dim);
  //Solução do sistema atraves da substituição reversa:
  printf("\nSolução:\n");
  raizes = malloc(dim *sizeof(double));
  subsreversa(M,raizes,dim);
  for (i =0; i<dim ; i++) 
  {
  	printf ("x%1d = %5.2lf\n",i , raizes[i]) ;
  }
  return (0);
  fclose(fp);
}
