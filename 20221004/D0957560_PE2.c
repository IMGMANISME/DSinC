#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	FILE *fp = fopen("D0957560_PE2.csv", "w");
	int m, n, bug_x, bug_y;
	int i, j;
	int count = 1;
	int sum[1] = {0};

	// initial random time
	srand(time(NULL));

	// scanf("%d%d%d%d", &m, &n, &bug_x, &bug_y);
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	bug_x = atoi(argv[3]);
	bug_y = atoi(argv[4]);

	int map[m][n];

	// check rules
	while (1)
	{
		if (argc != 5)
		{
			fprintf(fp, "invalid !");
			break;
		}

		if (2 > m || m >= 40 || 2 >= n || n >= 20)
		{
			fprintf(fp, "invalid !!");
			break;
		}

		if (m < bug_x || n < bug_y)
		{
			fprintf(fp, "invalid !!!");
			break;
		}

		// inital map
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n; j++)
			{
				map[i][j] = 0;
			}
		}

		// set first position
		map[bug_x][bug_y] = 1;

		// max run times 50000
		int z = 1;
		while (z <= 50000)
		{
			// generate random number
			while (1)
			{
				int random_num, next_x = bug_x, next_y = bug_y;
				random_num = rand() % 8;

				// move next_x, next_y
				switch (random_num)
				{
				case 0:
					next_x += 1;
					next_y += 1;
					break;
				case 1:
					next_x += 1;
					break;
				case 2:
					next_x += 1;
					next_y -= 1;
					break;
				case 3:
					next_y -= 1;
					break;
				case 4:
					next_x -= 1;
					next_y -= 1;
					break;
				case 5:
					next_x -= 1;
					break;
				case 6:
					next_x -= 1;
					next_y += 1;
					break;
				case 7:
					next_y += 1;
					break;
				}

				// check border
				if (next_x < 0 || next_x >= m || next_y < 0 || next_y >= n)
				{
					continue;
				}
				else
				{
					map[next_x][next_y]++;
					bug_x = next_x;
					bug_y = next_y;
					break;
				}
			}

			// check finish
			int check = 1;
			for (i = 0; i < m; i++)
			{
				for (j = 0; j < n; j++)
				{
					if (map[i][j] == 0)
					{
						check = -1;
						break;
					}
				}
				if (check == -1)
				{
					break;
				}
			}

			// finish all map
			if (check == 1)
			{
				for (i = 0; i < m; i++)
				{
					for (j = 0; j < n; j++)
					{
						sum[0] += map[i][j];
					}
				}
				break;
			}
			z++;
		}

		// print sum and map to csv file
		fprintf(fp, "The total number of moves = %d\n", sum[0]);
		printf("Sum: %d\n", sum[0]);
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n; j++)
			{
				sum[0] += map[i][j];
				printf("%d\t", map[i][j]);
				fprintf(fp, "%d,\t", map[i][j]);
			}
			fprintf(fp, "\n");
			printf("\n");
		}
		fclose(fp);
		break;
	}
}
