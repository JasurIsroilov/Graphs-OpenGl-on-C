#include<stdio.h>
#include<math.h>
int main()
{
	int str[100],i;
	for(i=0;i<100;i++)
	{
		str[i]=0;
	}
	int n,x;
	int count=0;
	printf("Input n:");
	scanf("%d",&n);
	for(;;)
	{
		if(n==0)
			break;
		x=n%2;
		n=(n-x)/2;
		str[count]=x;
		count++;
	}
	for(i=count-1;i>=0;i--)
	{
		printf("%d",str[i]);
	}
}
/*
printf("\t\t\tDecimal form of the first set!\n");
	for(i=0;i<n;i++)
	{
		printf("%d:%d\n",i+1,set1[i]);
	}
	printf("\t\t\tDecimal form of the second set!\n");
	for(i=0;i<n;i++)
	{
		printf("%d:%d\n",i+1,set2[i]);
	}
*/
