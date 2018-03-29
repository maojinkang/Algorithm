

#include"stdio.h"  
#define num 3 //宏定义数码的行列数为3 

//显示当前待调整数码矩阵
void show(int begin[num][num])
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
			printf("%d ", begin[i][j]);
		printf("\n");
	}
	printf("\n");
}

/*交换数码中的 begin[row_one][column_one] 与 begin[row_two][column_two] 这两个数*/
void exchange(int begin[num][num], int row_one, int column_one, int row_two, int column_two)
{
	int temp;
	temp = begin[row_two][column_two];
	begin[row_two][column_two] = begin[row_one][column_one];
	begin[row_one][column_one] = temp;
}

/*判断待调整的数码与最终数码相比正确位置数码的个数*/
int judge(int begin[num][num], int end[num][num])
{
	int count = 0;           //count记录数码中正确位置的个数  
	for (int i = 0; i < num; i++)   //检查当前图形的正确度  
	for (int j = 0; j < num; j++)
	{
		if (begin[i][j] == end[i][j] && end[i][j] != 0)
			count++;
	}
	return count;           //返回数码中正确位置的个数  
}

/* 将待调整数码从开始位置移动到终止位置，并将其过程输出*/
int yidong(int begin[num][num], int end[num][num]
	, int right, int jishu, int ji_shu[50][3][3]
	, int biaoji, int row, int column) //biaoji存储上一轮移动的反方向代号  
{
	int temp_zhi;
	show(begin);   //显示数组矩阵  
	if (jishu >= 20)
		return 0;
	int node;  //,node为标记  
	int temp;               //存储当前待调整数码正确的个数  
	for (int q = 0; q<jishu; q++)  //检查交换后的end[][]图形是否先前已经遍历过了  
	{
		node = 1;
		for (int w = 0; w<num && node; w++)
		for (int r = 0; r<num && node; r++)
		if (ji_shu[q][w][r] != begin[w][r])
			node = 0;
		if (node == 1)   //如果先前遍历过，返回0  
		{
			return 0;
		}
	}
	for (int i = 0; i < num; i++)
	for (int j = 0; j < num; j++)
		ji_shu[jishu][i][j] = begin[i][j];

	if (right == num * num - 1)  //如果待调整数码与最终数码完全相同时，返回1  
		return 1;
	if (row > 0 && biaoji != 0)             //存储0的位置不是在第一行  
	{
		exchange(begin, row - 1, column, row, column);  //将0与其上面的元素交换存储位置  
		temp = judge(begin, end);
		if (temp < right)   //如果交换后正确数码的个数不大于原来正确数码的个数  
			exchange(begin, row - 1, column, row, column); //再将其交换回来         
		else if (temp >= right)          //如果交换后正确数码的个数大于或等于原来正确数码的个数  
		{
			temp_zhi = yidong(begin, end, temp, jishu + 1, ji_shu, 2, row - 1, column);
			if (temp_zhi == 1)  //进行下一步的移动  
				return 1;
			exchange(begin, row - 1, column, row, column); //再将其交换回来  
		}
	}
	if (column > 0 && biaoji != 1)
	{
		exchange(begin, row, column - 1, row, column); //将0与其左边的元素交换存储位置  
		temp = judge(begin, end);
		if (temp < right)
			exchange(begin, row, column - 1, row, column);
		else if (temp >= right)
		{
			temp_zhi = yidong(begin, end, temp, jishu + 1, ji_shu, 3, row, column - 1);
			if (temp_zhi == 1)
				return 1;
			exchange(begin, row, column - 1, row, column);
		}
	}

	if (row < num - 1 && biaoji != 2)
	{
		exchange(begin, row + 1, column, row, column); //将0与其下面的元素交换存储位置  
		temp = judge(begin, end);
		if (temp < right)
			exchange(begin, row + 1, column, row, column);
		else if (temp >= right)
		{
			temp_zhi = yidong(begin, end, temp, jishu + 1, ji_shu, 0, row + 1, column);
			if (temp_zhi == 1)
				return 1;
			exchange(begin, row + 1, column, row, column);
		}
	}
	if (column < num - 1 && biaoji != 3)
	{
		exchange(begin, row, column + 1, row, column); //将0与其右边的元素交换存储位置  
		temp = judge(begin, end);
		if (temp < right)
			exchange(begin, row, column + 1, row, column);
		else if (temp >= right)
		{
			temp_zhi = yidong(begin, end, temp, jishu + 1, ji_shu, 1, row, column + 1);
			if (temp_zhi == 1)
				return 1;
			exchange(begin, row, column + 1, row, column);
		}
	}
	return 0;   //移动失败，返回0  
}

/*有用户输入待调整的数码矩阵最初状态的数，并将其存入到begin[][]数组中*/
void shuru(int begin[][num], int blank[])
{
	int temp, node, zero = 0;
	for (int i = 0; i < num; i++)
	for (int j = 0; j < num; j++)
	{
		node = 1;
		printf("请输入第%d行，第%d列的元素的值：", i + 1, j + 1);
		scanf("%d", &temp);
		for (int q = 0; q <= i && node == 1; q++)  //当输入的值有重复的，提示重新输入  
		for (int w = 0; w < j; w++)
		if (temp == begin[q][w])
		{
			printf("输入重复，请重新输入\n");
			node = 0;
			j--;
			break;
		}
		if (temp < 0 || temp > num*num - 1)   //当输入的值不是在数码的区间范围内时，提示重新输入  
		{
			printf("请输入从%d到%d的数\n", zero, num*num - 1);
			node = 0;
			j--;
		}
		if (node == 1)   //如果输入满足条件    
		{
			if (temp == 0) //如果输入的值为零，由blank[0]记录行号，blank[1]记录列号  
			{
				blank[0] = i;
				blank[1] = j;
			}
			begin[i][j] = temp;//将满足条件的值存储起来  
		}
	}
}

int main()
{
	int jishu = 0, ji_shu[50][3][3];//jishu存储已经遍历过的八数码图形的个数，jishu[][][]存储已经遍历过的八数码图形的形状  
	int row;     //存储数字零的行数  
	int column;  //存储数字零的列数  
	int begin[num][num], blank[2], count = 1;
	int end[num][num] = { 1, 2, 3, 8, 0, 4, 7, 6, 5 };  //给最终状态的数码矩阵赋值  
	printf("-------%d数码游戏开始！--------\n", num);
	shuru(begin, blank);   //输入带调整状态的数码矩阵的值  
	row = blank[0];
	column = blank[1];
	if (yidong(begin, end, judge(begin, end), jishu, ji_shu, 4, row, column) == 0)
		printf("\n此8数码的问题可能无解！");
	else
		show(begin);
	getchar(); getchar();
	return 0;
}