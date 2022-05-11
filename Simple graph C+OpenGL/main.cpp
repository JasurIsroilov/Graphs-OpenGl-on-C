#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>

typedef struct Node
{
	float x;
	float y;
	int position;
	struct Node *next;
}node;
node *head=NULL;
typedef struct Pos
{
	int a;
	int b;
	struct Pos *next;
}pos;
pos *head_pos=NULL;

int matrix[100][100];

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void display(void)
{
	pos *temp=head_pos;
	node *temp1=head;
	node *temp2=head;
	glLineWidth(1); 
	glColor3f(0, 0.6, 0);
	while(temp!=NULL)
	{
		while(temp->a!=temp1->position)
		{
			temp1=temp1->next;
		}
		while(temp->b!=temp2->position)
		{
			temp2=temp2->next;
		}
		glBegin(GL_LINES);
			glVertex2f(temp1->x, temp1->y);
			glVertex2f(temp2->x, temp2->y);
		glEnd();
		temp=temp->next;
		temp1=head;
		temp2=head;
	}
	
	node *temp_p=head;
		while(temp_p!=NULL)
		{
			glColor3f(1, 0, 0);
			glEnable(GL_POINT_SMOOTH);
			glPointSize(9);
			glBegin(GL_POINTS);
				glVertex2f(temp_p->x, temp_p->y);
			glEnd();
			temp_p=temp_p->next;
		}

	glFlush();
}




void add_node(int position)
{
	node *temp=(node*)malloc(sizeof(node));
	temp->x=0;
	temp->y=0;
	temp->next=head;
	temp->position=position;
	head=temp;
}

void allocate(int pos_a,int pos_b)
{
	pos *temp=(pos*)malloc(sizeof(pos));
	temp->a=pos_a;
	temp->b=pos_b;
	temp->next=head_pos;
	head_pos=temp;
}

void choose(int n)
{
	int i,j,choose;
	printf("Choose which points to allocate!\n");
	for(i=1;i<=n;i++)
	{
		for(j=i+1;j<=n;j++)
		{
			printf("%d and %d:[1/0]",i,j);
			scanf("%d",&choose);
			if(choose==1)
			{
				allocate(i,j);
			}
			else if(choose!=0)
			{
				printf("1 or 0!\n");
				j--;
			}
		}
	}
}

void point_pos(int n)
{
	float angle=2*M_PI/n,f=0;
	node *temp=head;
	while(temp!=NULL)
	{
		temp->x=temp->x+0.75*cos(f);
		temp->y=temp->y+0.75*sin(f);
		f=f+angle;
		temp=temp->next;
	}
}

void matrix_adjacency(int n)
{
	pos *temp=head_pos;
	int i,j;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=n;j++)
		{
			matrix[i][j]=0;
		}
	}
	while(temp!=NULL)
	{
		matrix[temp->a][temp->b]=1;
		temp=temp->next;
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(matrix[i][j]==1)
			{
				printf("%d-%d connected\n",i,j);
			}
		}
	}
}

void check(int n)
{
	pos *temp=head_pos;
	int count=0;
	while(temp!=NULL)
	{
		count++;
		temp=temp->next;
	}
	if(count>=(n-1)*(n-2)/2)
	{
		printf("Graph is connected!\n");
	}
}





int main(int argc, char **argv)
{
	int n_points,i,position; 
	printf("How many points do you want?\n");
	scanf("%d",&n_points);
	for(i=0;i<n_points;i++)
	{
		position=i+1;
		add_node(position);
	}
	choose(n_points);
	point_pos(n_points);
	matrix_adjacency(n_points);
	check(n_points);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Graph");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

