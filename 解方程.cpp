#include<stdio.h>  
int main(){  
    int n;  
    int tmp[100][3];  
    int i,k;  
    scanf("%d",&n);  
    for(i=0;i<n;i++){  
        scanf("%d %d %d",&tmp[i][0],&tmp[i][1],&tmp[i][2]);  
    }  
    for(i=0;i<n;i++){  
        if(tmp[i][0]!=0){  
            k=tmp[i][1]*tmp[i][1]-4*tmp[i][0]*tmp[i][2];  
            if(k>0){  
                printf("%d\n",2);  
            }  
            else if(k<0){  
                printf("%d\n",0);  
            }  
            else  
                printf("%d\n",1);  
        }  
        else if(tmp[i][1]==0 && tmp[i][2]!=0){  
                printf("%d\n",0);  
        }  
        else if(tmp[i][1]==0 && tmp[i][2]==0){  
            printf("INF\n");  
        }  
    }  
      
}  