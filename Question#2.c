    #include <stdio.h>
    int rangef(void);
    int lengthf(int range);
    int main(void){
        
        int range = rangef();
        int index = 0;
        int index2;
        int va1 =0;
        int va2;
        
        for (int i = 2; i <range; i++){
            int array[lengthf(i)];
            for (int j = 1; j < i; j++){
                if((i%j)==0){
                    array[index] = j;
                    index+=1;
                }
            }
            va1 = 0;
            for (int i = 0; i < index; i++)
            {
                va1 += array[i];
            }
            int array2[lengthf(va1)];
            index2 =0;
            for(int i = 1; i < va1; i++){
                if((va1%i)==0){
                    array2[index2] = i;
                    index2 +=1;
                }
            }
            va2 = 0;
            for (int i = 0; i < index2; i++)
            {
                va2 += array2[i];
            }
            if(va2==i && (va1 != i)){
                if(i<va1){
                printf("\nThe Amicable Pair: [%d,%d]\n",i,va1);
                }
            }
            
            index  =0;
        }

    }

    int rangef(void){
        int range;
        printf("Enter Range: ");
        scanf("%d",&range);
        return range;
    }

    int lengthf(int range){
        int count = 0;
        int i = 1;
        while(1){
            if(i==range){
                break;
            }
            if((range%i)==0){
                count +=1;
            }
            i +=1;

        }
        return count;
    }