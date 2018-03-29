#include<stdio.h>  
double cf[30];  
int main()  
{  
    int i,j,n;  
    double s,f,x,l,r,m;  
    while(scanf("%d",&n)!=EOF)  
    {  
        if(n==0)  
            break;  
        scanf("%lf",&x);  
        for(i=0;i<n;i++)  
            scanf("%lf",&cf[i]);  
        l=-1.0;  
        r=1e6;
        for(i=0;i<100;i++)  
        {  
            s=0;  
            f=1.0;  
            m=(l+r)/2;  
            for(j=0;j<n;j++)  
            {  
                f=f/(1+m);  
                s=s+cf[j]*f;  
            }  
            if(s>(-x))  
                l=m;  
            else  
                r=m;  
        }  
        printf("%.2lf\n",m);  
    }  
    return 0;  
}  