#include<iostream>
#include<string.h>
using namespace std;
void NMB(char aa[])
{
	int i,j;
	char t;
	j=strlen(aa); //cout<<j<<endl;
	for(i=0;i<j/2;i++)
		t=aa[i],aa[i]=aa[j-1-i],aa[j-1-i]=t;
}
int main()
{
	char a[500],b[500],c[501];
	while(1){
	memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	cin>>a>>b;NMB(a);NMB(b);
	int i=0,aa,bb;
	c[0]='0';
	while(a[i]!='\0'||b[i]!='\0')
	{
		if(a[i]!='\0') aa=a[i]-'0';else aa=0;
		if(b[i]!='\0') bb=b[i]-'0';else bb=0;
		if(aa+bb+c[i]-'0'<10) {c[i]=aa+bb+c[i];c[i+1]='0';}
		else if(aa+bb+c[i]-'0'==10) c[i]='0',c[i+1]='1';
		else {c[i]=(aa+bb+c[i]-'0')%10+'0';c[i+1]='1';}
		i++;
	}
	if(c[i]=='0') c[i]='\0';
	NMB(c);
	cout<<c<<endl;
	}
	return 0;
}