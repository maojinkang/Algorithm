/*#include<iostream>
using namespace std;
int main()
{
	int n, i, j;
	while (cin >> n){
		int y = 0;
		int sum = 0;
		int str[40000];
		int flag = 1;
		str[0] = 1;
		for (i = 2; i <= n; i++){
			for (j = 1; j <= flag; j++)
			{
				sum = str[j - 1] * i + y;
				str[j - 1] = sum % 10;
				y = sum / 10;
			}
			while (y){
				flag++;
				str[flag - 1] = y % 10;
				y = y / 10;
			}
		}
		for (i = flag - 1; i >= 0; i--)
			cout << str[i];
		cout << endl;
	}
	return 0;
}
*/
/*#include<iostream>  
using namespace std;
int main()
{
	int t;
	long long n, sum;
	cin >> t;
	while (t--){
		cin >> n;
		sum = 0;
		while (n){
			n >>= 1;
			sum += n;
		}
		printf("%lld\n", sum);
	}
}*/
/*
/*如果x的x次幂结果为10，你能计算出x的近似值吗？

显然，这个值是介于2和3之间的一个数字。

请把x的值计算到小数后6位（四舍五入），并填写这个小数值。
#include<stdio.h>  
#include<math.h>  
int main()
{
	//printf("%.7lf\n", pow(2.5, 2.5));//显然这个数大于2.5
	double x = 2.5;
	while (x<3.0)
	{
		x = x + 0.0000001;//7个小数位的形式递增 //计算到小数后6位  
		if (fabs(pow(x, x) - 10.0)<0.000001)
		{
			printf("%.7lf\n", x);
		}
	}
	return 0;
}*/
#include<iostream>
using namespace std;
typedef long long ll;
int D;
void CNM(int a[],int n)
{
	for (int i = 0; i < n; i++){
		if (a[i] == D) a[i] = 0;
		else if (a[i] == 0) a[i] = D;
		else a[i] = a[i] ^ D;
	}
}
int main()
{
	int  n, m, a[50000],flag;
	ll sum;
	memset(a, 0, sizeof(a));
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	while (m--){
		cin >> flag;
		if (flag == 1){
			sum = 0;
			for (int i = 0; i < n; i++)
				sum += a[i];
			cout << sum << endl;
		}
		else{
			cin >> D;
				CNM(a,n);
		}
	}
	return 0;
}