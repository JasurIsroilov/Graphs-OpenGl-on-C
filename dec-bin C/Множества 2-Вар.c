#include<stdio.h>
#include<math.h>


void dec_bin(int n,int set[n])
{
	int x,i,j,count=0;
	int bin_set[100];
	for(i=0;i<n;i++)
	{
		for(j=0;j<100;j++)
		{
			bin_set[j]=0;
		}
		for(;;)
		{
			if(set[i]==0)
				break;
			x=set[i]%2;
			set[i]=(set[i]-x)/2;
			bin_set[count]=x;
			count++;
		}
		printf("%d-element:",i+1);
		for(j=count-1;j>=0;j--)
		{
			printf("%d",bin_set[j]);
		}
		printf("\n");
		count=0;
	}
}


int main(void)
{
	int n=0,i=0;
	printf("Input the number of elements:");
	scanf("%d",&n);
	int set1[n],set2[n];
	printf("\t\t\tInput elements of the first array!\n");
	for(i=0;i<n;i++)
	{
		printf("%d:",i+1);
		scanf("%d",&set1[i]);
	}
	
	printf("\t\t\tInput elements of the second array!\n");
	for(i=0;i<n;i++)
	{
		printf("%d:",i+1);
		scanf("%d",&set2[i]);
	}
	
	printf("\t\t\tBinary form of the first set!\n");
	dec_bin(n,set1);
	printf("\t\t\tBinary form of the second set!\n");
	dec_bin(n,set2);
	return 0;
}
