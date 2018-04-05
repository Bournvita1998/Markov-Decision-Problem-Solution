#include<stdio.h>
#include<stdlib.h>

double north(int x, int y, double **util, int wall[][2], int n1)
{
	if(x==0)
		return util[x][y];
	int i;
	for(i=0;i<n1;i++) //wall
		if((wall[i][0] == (x-1)) && (wall[i][1] == y))
			return util[x][y];
	return util[x-1][y];
}

double east(int x, int y, double **util, int wall[][2], int n1, int m)
{
	if(y == (m-1))
		return util[x][y];
	int i;
	for(i=0;i<n1;i++) //wall
		if((wall[i][0] == (x)) && (wall[i][1] == (y+1)))
			return util[x][y];
	return util[x][y+1];
}

double south(int x, int y, double **util, int wall[][2], int n1, int n)
{
	if(x == (n-1))
		return util[x][y];
	int i;
	for(i=0;i<n1;i++) //wall
		if((wall[i][0] == (x+1)) && (wall[i][1] == y))
			return util[x][y];
	return util[x+1][y];
}

double west(int x, int y, double **util, int wall[][2], int n1)
{
	if(y==0)
		return util[x][y];
	int i;
	for(i=0;i<n1;i++) //wall
		if((wall[i][0] == (x)) && (wall[i][1] == (y-1)))
			return util[x][y];
	return util[x][y-1];
}

double max(double a, double b)
{
	return ((a>b) ? a : b);
}

int endStateWall(int x, int y, int end[][2], int e, int wall[][2], int w)
{
	for(e--; e >= 0; e--)
		if((end[e][0] == x) && (end[e][1] == y))
			return 1;
	for(w--; w >= 0; w--)
		if((wall[w][0] == x) && (wall[w][1] == y))
			return 1;
	return 0;
}

double absolute(double x)
{
	if(x<0)
		x = x * -1;
	return x;
}

int main()
{
	int n,m;
	int i,j;
	scanf("%d %d",&n,&m);
	double *arr[n];
	for(i=0;i<n;i++)
		arr[i] = (double*)malloc(m*sizeof(double));
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			scanf("%lf", &arr[i][j]);
	int e,w;
	scanf("%d %d",&e,&w);
	int end[e][2];
	int wall[w][2];
	for(i=0;i<e;i++)
		scanf("%d %d", &end[i][0], &end[i][1]);
	for(i=0;i<w;i++)
		scanf("%d %d", &wall[i][0], &wall[i][1]);
	int startx, starty;
	scanf("%d %d", &startx, &starty);
	double unit;
	scanf("%lf", &unit);

	double *util[n], *last[n];
	for(i=0;i<n;i++)
	{
		util[i] = (double*)malloc(m*sizeof(double));
		last[i] = (double*)malloc(m*sizeof(double));
	}

	for(i=n-1;i>=0;i--)
		for(j=0;j<m;j++)
		{
			util[i][j] = arr[i][j];
			last[i][j] = arr[i][j];
		}

	int k;

	for(i=n-1;i>=0;i--)
		for(j=0;j<m;j++)
			for(k=0;k<e;k++)
			{
				if((i == end[k][0]) && (j == end[k][1]))
					last[i][j] = 0;
			}

	double x1,x2,x3,x4;
	double a1,a2,a3,a4;

	int t = 1;

	for(i=n-1;i>=0;i--)
		for(j=0;j<m;j++)
		{
			util[i][j] = util[i][j] - last[i][j];
		}
	
	while(t)
	{
		t = 0;
		for(i=n-1;i>=0;i--)
			for(j=0;j<m;j++)
			{
				if(endStateWall(i, j, end, e, wall, w))
					arr[i][j]=util[i][j];
				else
				{
					a1 = north(i, j, util, wall, w) + last[i][j];
					a2 = east(i, j, util, wall, w, m) + last[i][j];
					a3 = south(i, j, util, wall, w, n) + last[i][j];
					a4 = west(i, j, util, wall, w) + last[i][j];
					x1 = 0.8 * a1 + 0.1 * a2 + 0.1 * a4;
					x2 = 0.8 * a2 + 0.1 * a1 + 0.1 * a3;
					x3 = 0.8 * a3 + 0.1 * a2 + 0.1 * a4;
					x4 = 0.8 * a4 + 0.1 * a1 + 0.1 * a3;
					arr[i][j] = max(max(x1,x2), max(x3,x4)) + unit;
					if(absolute(arr[i][j] - util[i][j]) > (absolute(arr[i][j])/100))  //1%check
						t=1;
				}
			}

		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
				util[i][j] = arr[i][j];
	}

	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
			printf("%.3lf ", util[i][j]);
		printf("\n");
	}
	return 0;
}
