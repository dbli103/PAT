/*
1002
读入一个正整数 n，计算其各位数字之和，用汉语拼音写出和的每一位数字。
输入格式：
每个测试输入包含 1 个测试用例，即给出自然数 n 的值。这里保证 n 小于 10^100


输出格式：
在一行内输出 n 的各位数字之和的每一位，拼音数字间有 1 空格，但一行中最后一个拼音数字后没有空格。

输入样例：
1234567890987654321123456789
结尾无空行
输出样例：
yi san wu
结尾无空行
*/
/*
//   Date:2020/4/29
//   Author:xiezhg5
#include <stdio.h>
#include <string.h>
int main(void) {
	int i,num,sum=0,count=0;
	int weishu[5];
	char pinyin[][5]= {"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};
	char str[101];
	//读入字符并转化为整数数值 
	while(scanf("%s",str) != EOF);
	for(int i=0; i<strlen(str); i++) {
		sum=sum+str[i]-'0';
	}
	//求进制位上的数字 
	while(sum!=0) {
		weishu[count]=sum%10;
		sum=sum/10;
		count++;
	}
	//格式输出(最后一个拼音后无空格) 
	for(int i=count-1; i>0; i--)
		printf("%s ",pinyin[weishu[i]]);
	printf("%s",pinyin[weishu[0]]);
	return 0;
}
*/
#include <stdio.h>
#include<string.h> 
int main()
{
	int sum = 0;
	char n;  //各位的数 
	char *pingyin[] = {"ling","yi","er","san","si","wu","liu","qi","ba","jiu"};
	while((n = getchar())!= '\n') //逐个接收数字 
		{
		sum += n - '0';	 //比如字符串n是'5'，'5'的ASCII码是53,'0'的ASCII码是48 ,53-48=5
		}	
	
	if(sum/100) // 比如135/100=1
	{
		printf("%s", pingyin[sum/100]); //pingyin[1]="yi"
		printf(" "); //每个拼音间有空格 
 	} 
	if(sum/10) // 135/10=13
	{ 
		printf("%s", pingyin[sum/10%10]);//135/10%10=3,pingyin[3]="san"
		printf(" ");
	}
			
	printf("%s", pingyin[sum%10]); //135%10=5,pinyin[5]="wu"
    return 0;
}






/*
#include<iostream>
using namespace std;
int main()
{
	char x[10000];
	int s[10000];
	int y[10000];
	int g = 0;
	int sum = 0;
	cin >> x;
	for (int i = 0; x[i] != '\0'; i++)
	{
		s[i] = x[i] - 48;
		sum += s[i];
	}
	if (sum == 0)
		cout << "ling";
	else
	{
		while (sum != 0)
		{
			int k;
			k = sum % 10;
			y[g++] = k;
			sum = sum / 10;
		}
	}
	for (int i = g - 1; i >= 0; i--)
	{

		switch (y[i])
		{
		case 0:if (i != 0)cout << "ling" << " ";
			   else cout << "ling"; break;
		case 1:if (i != 0)cout << "yi" << " "; else cout << "yi"; break;
		case 2:if (i != 0)cout << "er" << " "; else cout << "er"; break;
		case 3:if (i != 0)cout << "san" << " "; else cout << "san"; break;
		case 4:if (i != 0)cout << "si" << " "; else cout << "si"; break;
		case 5:if (i != 0)cout << "wu" << " "; else cout << "wu"; break;
		case 6:if (i != 0)cout << "liu" << " "; else cout << "liu"; break;
		case 7:if (i != 0) cout << "qi" << " "; else cout << "qi"; break;
		case 8:if (i != 0)cout << "ba" << " "; else cout << "ba"; break;
		case 9:if (i != 0)cout << "jiu" << " "; else cout << "jiu"; break;
		}
	}
	return 0;
}


#include<iostream>
#include<string>
#include<stack>
using namespace std;

void print(int sum)
{
	string name[] = { "ling","yi","er","san","si","wu","liu","qi","ba","jiu" };
	stack<int>r_sum;
	while (sum > 0)
	{
		r_sum.push(sum % 10);
		sum /= 10;
		if (sum == 0)
		{
			while (!r_sum.empty())
			{
				cout<<name[r_sum.top()];
				r_sum.pop();
				if (!r_sum.empty())
				{
					cout << " ";
				}
			}
		}
	}
}

int main()
{
	char ch;
	int sum = 0;
	while ((ch = getchar()) != '\n')
	{
		sum = sum + ch - '0';
	}
	print(sum);
}


#include <iostream>
using namespace std;
int main()
{
	int sum = 0;
	char ch, s[4];                       //ch作为临时变量保存输入的每一个字符，s保存sum的每一个数字 ，因为题目小于1000                       
	char b[10][5] = { "ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu" };
	while ((ch = getchar()) != '\n')    //如果一直输入字符，不按回车的话 
		sum += (ch - '0');
	sprintf_s(s, "%d", sum);              // sprintf(char *buffer, const char *format,[ argument])将任意类型数据按某种格式转换成字符串 
	for (int i = 0; s[i] != 0; i++) {
		if (i > 0) //消除第一个空格 
			printf(" ");
		printf("%s", b[s[i] - '0']);
	}
	return 0;//上文sprintf中s为s[4]数组名，将sum的值存放在s中 
}


*/

