#include<stdio.h>
#include<stdlib.h>
int main()
{
    int i,j,temp,color,max;
    FILE *fptr;
    int *a;

    //read input from a file to verify the code algo2.c
    fptr=fopen("sa.txt","r");


    //if file is empty then exit
    if (fptr==NULL)
        exit(0);


    //read the number of colors used in algo2.c
    fscanf(fptr,"%d",&color);
    printf("color = %d\n",color);

    //max represents the number of vertices which is read from the file
    fscanf(fptr,"%d",&max);
    printf("Number of vertices = %d\n",max);

    int *b[max];

    a=(int *)calloc(max,sizeof(int));


    for (i=0;i<max;i++)
    {
        b[i]=(int *)calloc(max,sizeof(int));
    }

    //read the array which contains the colors assigned to the vertices
    for (i=0;i<max;i++)
        fscanf(fptr,"%d",&a[i]);

    //adjacency matrix of the graph is read
    for (i=0;i<max;i++)
    {
        for (j=0;j<max;j++)
        {
            fscanf(fptr,"%d",&b[i][j]);
        }
    }

    fclose(fptr);


    //check if there exists an edge between two vertices of same color
    for (i=0;i<max;i++)
    {
        temp=a[i];

        //if the vertex is not scanned
        if (a[i]!=1000)
        {
            for (j=i+1;j<max;j++)
            {
                if (a[j]==temp)
                {
                    //assign large value to the vertex once scanned
                    a[j]=1000;
                    if (b[i][j]!=0)
                    {
                        //print error if there exists an edge between two vertices of the same color and exit
                        printf("Error\n");
                        exit(0);
                    }
                }
            }
        }
    }
    //if there exists no edge between same colored vertices then print successful
    printf("\nVerification Successful\n");
    return 0;
}




