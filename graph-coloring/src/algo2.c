#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//generation function which generates the random graph
void gen(int *a[],int);

//function to calculate the degree of each vertex
void degree(int *a[],int [],int);

//function to color a given graph
int color(int [],int *b[],int);


int main(int argc,char *argv[])
{

    int max;
    srand ((unsigned)time(NULL));

    //without any arguments
    if (argc==1)
    {
        max=rand()%100;
    }

    //number of vertices (OR) number of vertices along with file input as arguments
    if (argc==2 || argc==3)
    {
        max=atoi(argv[1]);
    }

    if (max<1||max>100)
    {
        printf("The number of nodes to be entered should be between 1 and 100\n");
        exit(0);
    }

    //a represents ajacency matrix and ind represents the array of degrees
    int *a[max],ind[max],x,i,j;
    FILE *fptr,*fptr1;

    if (argc==1 || argc==2)
    {

        for (i=0;i<max;i++)
        {
            a[i]=(int *)calloc(max,sizeof(int));
        }
        //function call to generate a graph if no arguments are passed to main
        //adjacency matrix is passed to the function
        gen(a,max);
    }

    //number of vertices along with file input as arguments
    if (argc==3)
    {

        fptr=fopen(argv[2],"r");

        if (fptr==NULL)
            exit(0);

        for (i=0;i<max;i++)
        {
            a[i]=(int *)calloc(max,sizeof(int));
        }

        for (i=0;i<max;i++)
        {
            for (j=0;j<max;j++)
            {
                fscanf(fptr,"%d\t",&a[i][j]);
            }
        }


        //for a test case if the given condition is not satisfied then print the following and exit
        for (i=0;i<max;i++)
        {
            for (j=0;j<max;j++)
            {
                if (i==j && a[i][j]==1)
                {
                    printf("Invalid input\n");
                    fptr1=fopen("t2.r","w");
                    fprintf(fptr1,"Invalid input\n");
                    fclose(fptr1);

                    exit(0);
                }
            }
        }

        //for a test case if the given condition is not satisfied then print the following and exit
        for (i=0;i<max;i++)
        {
            for (j=0;j<max;j++)
            {
                if (a[i][j]!=a[j][i])
                {
                    printf("Invalid input\n");
                    fptr1=fopen("t3.r","w");
                    fprintf(fptr1,"Invalid input\n");
                    fclose(fptr1);
                    exit(0);
                }
            }
        }

        fclose(fptr);
    }


    //function call to calculate the degree of a graph
    //adjacency matrix and array of degrees is passed to the function
    degree(a,ind,max);

    //function to color a graph
    //array of degrees and an adjacency matrix is passed to the function
    x=color(ind,a,max);

    //for different test cases choose different cases
    switch (x)
    {
    case 1:
        fptr1=fopen("t1.r","w");
        fprintf(fptr1,"Non-partite\n");
        fclose(fptr1);

    case 2:
        fptr1=fopen("t4.r","w");
        fprintf(fptr1,"Bipartite\n");
        fclose(fptr1);

    case 3:
        fptr1=fopen("t5.r","w");
        fprintf(fptr1,"3-partite\n");
        fclose(fptr1);

    case 4:
        fptr1=fopen("t6.r","w");
        fprintf(fptr1,"4-partite\n");
        fclose(fptr1);

    }


    printf("The given graph has %d vertices\n",max);
    printf("The graph with %d vertices given can be partitioned into %d subsets\n",max,x);
    if (x==1)
    {
        printf("So it is not a partite graph\n");
    }
    else if (x==2)
    {
        printf("So it is a Bipartite graph\n");
    }
    else
    {
        printf("So the graph is %d-partite\n",x);
    }

    return 0;
}

//generation of random graph
void gen(int *a[],int max)
{
    int i,j;
    srand ((unsigned) time (NULL));          //the function srand() generates different random numbers during each run

    for (i=0;i<max;i++)
    {
        for (j=0;j<max;j++)
        {
            if (i==j)
            {
                //diagonal elements in an adjacency matrix is zero,i.e,there is no loop
                a[i][j]=0;
            }
            else
            {
                //since it is an undirected graph
                //in an adjacency matrix, a[i][j]=a[j][i] shows that there exists an edge between i and j
                a[i][j]=rand()%2;
                a[j][i]=a[i][j];
            }
        }
    }

    //print the matrix if there are only vertices less than 10
    if (max<=10)
    {
        printf("Ajacency Matrix\n");

        for (i=0;i<max;i++)
        {
            for (j=0;j<max;j++)
            {
                printf("%d\t",a[i][j]);
            }
            printf("\n");
        }
    }
}



//calculate the degree of each vertex
void degree(int *a[],int ind[],int max)
{
    int i,j,sum;

    printf("Degrees of vertices\n");

    for (j=0;j<max;j++)
    {
        sum=0;
        for (i=0;i<max;i++)
        {
            sum=sum+a[i][j];
        }

        //sum will have the degree of 'j'th vertex, which is stored in an array ind[]
        ind[j]=sum;
        printf("%d\n",ind[j]);
    }
}


//color a graph to know how a graph is partitioned
int color(int a[],int *b[],int max)
{
    int i,j,k,pos,top=-1,min,ccolor=0,m,d[max],count;
    int u,c[max],s[max],temp[max],top1=-1;
    int p,q;
    FILE *fptr;
    //s[max] and temp[max] are the 2 stacks used
    // top and top1 are used to represent the stack tops for the stacks 's' and 'temp'


    //to sort the vertices according to the degrees and push it on to the stack
    //such that vertex with the highest degree is on the top

    for (k=0;k<max;k++)
    {
        i=0;
        min =a[i];
        for (j=0;j<max;j++)
        {
            if (a[j]<=min)		//min degree vertex is found
            {
                min=a[j];
                pos=j;
            }
        }
        a[pos]=100;			//the value of the degree is made infinite after the vertex is found
        s[++top]=pos;			//the vertex found is pushed onto the stack
    }


    //while there are vertices to be colored

    while (top!=-1)
    {

        //pop the vertex that has the highest degree
        u=s[top];
        top--;

        //assign a color to that vertex
        c[u]=ccolor;

        //count represents number of vertices that are not connected to 'u'
        count=0;
        m=0;

        //vertices that are not connected to 'u' are put into d[]
        for (k=0;k<max;k++)
        {

            //select the vertex that is not connected to the popped vertex
            if (b[u][k]==0 && u!=k)
            {

                d[m]=k;
                m++;
                count++;
            }
        }

        //coloring of the non adjacent vertices in the array
        for (p=0;p<count;p++)
        {
            for (q=p+1;q<count;q++)
            {
                //if the vertices in the array d[] are connected then do not color
                if (b[d[p]][d[q]]==1)
                {
                    break;
                }
            }

            //if the vertices are non adjacent then they are colored and popped
            if (q==count)
            {
                c[d[p]]=ccolor;


                //pop the vertices from the stack and push it to the temporary stack
                //till the colored vertex is obtained
                while (s[top]!=d[p] && top!=-1)
                {
                    temp[++top1]=s[top--];
                }

                //if the stack is not empty pop the vertex obtained
                if (top!=-1)
                    top--;

                //pop the vertices back from the temporary stack and push it on to the original stack
                while (top1!=-1)
                    s[++top]=temp[top1--];
            }
        }


        //increment the color counter so that it will color the next vertex from the stack
        ccolor=ccolor+1;
    }


    printf("\ncoloring needed=%d\n",ccolor);

    //writing the colors needed, number of vertices, the color of the vertices and adjacency matrix
    //to a file named sa.txt

    fptr=fopen("sa.txt","w");
    fprintf(fptr,"%d\n",ccolor);

    fprintf(fptr,"%d\n",max);

    for (i=0;i<max;i++)
    {
        fprintf(fptr,"%d\t",c[i]);
    }
    fprintf(fptr,"\n");

    for (i=0;i<max;i++)
    {
        fprintf(fptr,"\n");
        for (j=0;j<max;j++)
        {
            fprintf(fptr,"%d\t",b[i][j]);
        }
    }
    fclose(fptr);


    return ccolor;
}

