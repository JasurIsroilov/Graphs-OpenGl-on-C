/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdio.h>
#include<iostream>
#include<cmath>

using namespace std;

int n,matrix[15][15];
struct flag
{
    int number[15];
    int pow[15];
};
flag save;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void display(void)
{
	int i,j;
	double angle=2*3.14 / n;

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (matrix[i][j] == 1)
			{
				glLineWidth(1);
				glColor3f(0, 1, 0);
				glBegin(GL_LINES);
				 glVertex2f(0.75*cos(i*angle), 0.75*sin(i*angle));
				 glVertex2f(0.75*cos(j*angle), 0.75*sin(j*angle));
				glEnd();
			}
		}

	}
	for (i = 1; i <= n; i++)
	{
		glColor3f(1, 0, 0);
		glEnable(GL_POINT_SMOOTH);
		glPointSize(9);
		glBegin(GL_POINTS);
		 glVertex2f(0.75*cos(i*angle), 0.75*sin(i*angle));
		glEnd();
	}

	glFlush();
}

void link_graph()
{
	int i,j,choose;
	cout << "Fill in the matrix of adjacency\n1 is linked\n0 is not linked\n";
	for (i = 1; i <= n; i++)
	{
		for (j = i+1; j <= n; j++)
		{
			cout <<"["<<i<<"and"<<j<<"]:";
			cin >> choose;
			if ((choose == 1) || (choose == 0))
			{
				matrix[i][j] = choose;
				matrix[j][i] = choose;
			}
			else
			{
				cout << "1 or 0!\n";
				j--;
			}
		}
	}
}

void display_matrix()
{
	int i, j;
	cout << "THE MATRIX OF THE ADJACENCY" << endl;
	cout << "  ";
	for (j = 1; j <= n; j++)
	{
		cout << j << " ";
	}
	cout << endl;
	for (i = 1; i <= n; i++)
	{
		cout << i << " ";
		for (j = 1; j <= n; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int find_even_pow(int size)
{
	int pow[15],i,j,count=0;
	for( i=1; i<=n; i++ )
	{
		for (j = 1; j<= n; j++)
			if(matrix[i][j]==1)
				count++;
		pow[i] = count;
		count = 0;
	}
	j=0;
	for (i = 1; i <= n; i++)
	{
		if ((pow[i] % 2 == 0) && (pow[i] != 0))
		{
			save.pow[j] = pow[i];
			save.number[j]=i;
			j++;
		}
	}
	return j;
}
int check(int buff[],int k,int edge)
{
    int i,temp=0;
    for(i=0;i<k;i++)
    {
        if(buff[i]==edge)
            temp=1;
    }
    return temp;
}
void insertion_sort(int size)
{
	int i, j, temp,k=0;
    int arr[15],buff[15];
    for(i=0;i<15;i++)
    {
        arr[i]=save.pow[i];
    }
	for (i = 1; i <= size; i++)
	{
		temp = arr[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j] < temp)
				break;

			arr[j + 1] = arr[j];
			arr[j] = temp;
		}
	}
	cout << "Sorted"<<endl;
	for (i = 1; i < size+1; i++)
	{
		for(j=0;j<size;j++)
		{
		    if(arr[i]==save.pow[j])
		    {
		        if(check(buff,k,save.number[j])==0)
		        {
		            buff[k]=save.number[j];
                    k++;
		            cout<<"edge:"<<save.number[j]<<"\t";
		            break;
		        }
		    }
		}
		cout<<"power:"<<arr[i]<<endl;
	}
}

int main(int argc, char **argv)
{
	system("color F0");
	int i,j,even_size=0;
	cout << "Input the number of points:";
	cin >> n;
	for(i = 0; i < 15; i++)
	{
	    save.number[i]=0;
	    save.pow[i]=0;
	}
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			matrix[i][j] = 0;
		}
	}

	link_graph();
	display_matrix();
	even_size=find_even_pow(even_size);
	cout<<"|Number of edge   |Power of edge"<<endl;
	for(i=0;i<even_size;i++)
	{
	    cout<<"|"<<save.number[i]<<"\t\t  |"<<save.pow[i]<<endl;
	}
	insertion_sort(even_size);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Graph");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	system("pause");

	return 0;
}
