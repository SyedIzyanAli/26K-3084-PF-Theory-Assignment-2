#include <stdio.h>
int main(void)
{
    int rows;
    int seats;
    int count = 0;
    int totalcount = 0;

    int k;

    printf("Enter the Number of Rows: ");
    scanf("%d", &rows);

    printf("Enter the Number of Seats Per Row: ");
    scanf("%d", &seats);

    int array[rows][seats];
    int freeseats[rows];

    printf("Enter the Number of Seats You want in a Group: ");
    scanf("%d", &k);
    printf("Input Seating Plan:\n");

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < seats; j++)
        {

            printf("Row: %d Seat: %d: ", i, j);
            scanf("%d", &array[i][j]);
        }
    }

    for (int i = 0; i < seats; i++)
    {
        printf("\t%d", i);
    }
    for (int i = 0; i < rows; i++)
    {

        count = 0;
        printf("\n");
        printf("R%d", i);
        for (int j = 0; j < seats; j++)
        {

            if (array[i][j] == 0)
            {
                count += 1;
                printf("\t_");
            }
            else
            {
                printf("\tX");
            }
        }
        freeseats[i] = count;
        printf("\n");
    }
    printf("\nNumber of free Seats per Row: ");
    for (int i = 0; i < rows; i++)
    {
        printf("\t%d", freeseats[i]);
        totalcount += freeseats[i];
    }
    printf("\nThe Total Number of Free Seats is: %d\n", totalcount);

    int mid_row = rows/2;
    int i = mid_row;
    int dist_counter = 0;
    int j = 0;
    int free_seat = 0;
    int iterate = 0;
    int token = 0;
    while(i<rows){
        j = 0;
        if(iterate == 0){
        i = mid_row - dist_counter;
        iterate = 1;
        }
        else{
        i = mid_row + dist_counter;
        iterate = 0;
        if(i==rows){
            break;
        }
        }
        while(j<seats){
            if(i<0 || i==rows){
                break;
            }
            if(array[i][j]==0){
                free_seat+=1;
                
            }
            else{
                free_seat =0;
            }
            if(free_seat==k){
                token =1;
                printf("\nGroup of %d Seats Found in Row %d From Seat %d to %d.\n",k,i,j-k+1,j);
                for(int a = 1; a < k+1; a++){
                array[i][j-k+a] = 1; 
                }
                break;
            }

            j+=1;
        }
        free_seat =0;
        if(iterate==0){
        dist_counter+=1;
        }
        if(token==1){
            break;
        }
    }
    

    for (int i = 0; i < seats; i++)
    {
        printf("\t%d", i);
    }
    for (int i = 0; i < rows; i++)
    {

        count = 0;
        printf("\n");
        printf("R%d", i);
        for (int j = 0; j < seats; j++)
        {

            if (array[i][j] == 0)
            {
                printf("\t_");
            }
            else
            {
                printf("\tX");
            }
        }
        printf("\n");
    }
    
    return 0;
}