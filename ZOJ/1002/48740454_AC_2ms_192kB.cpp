#include <stdio.h>
#include <string.h>

char square[4][5];
char temp[4][5];

typedef struct _point {
	int i;
	int j;
}Point;

Point empty[16];

int config(int i, int j, int size, char sq[][5]) {
	int k;
	if (sq[i][j] == '.') {
		for (k = i-1; k >= 0; --k)
			if (sq[k][j] == 'X')
				break;
			else if (sq[k][j] == '-')
				return 0;
			
		for (k = i+1; k < size; ++k)
			if (sq[k][j] == 'X')
				break;
			else if (sq[k][j] == '-')
				return 0;

		for (k = j-1; k >= 0; --k)
			if (sq[i][k] == 'X')
				break;
			else if (sq[i][k] == '-')
				return 0;
			
		for (k = j+1; k < size; ++k)
			if (sq[i][k] == 'X')
				break;
			else if (sq[i][k] == '-')
				return 0;

		sq[i][j] = '-';
		return 1;
	}
	return 0;
}

int main() {
	int i,j,k, count, count_empty, max, size;
	
	scanf("%d", &size);
	while (size != 0) {
		count_empty = 0;
		max = 0;
		for (i = 0; i < size; ++i) {
			scanf("%s", square[i]);
			for (j = 0; j < size; ++j) {
				if (square[i][j] == '.') {
					empty[count_empty].i = i;
					empty[count_empty].j = j;
					count_empty++;
				}
			}
		}
		for (i = 0; i < count_empty; ++i) {
			for (k = 0; k < size; ++k) {
				strcpy(temp[k], square[k]);
			}
			count = 0;
			for (j = 0; j < count_empty; ++j) {
				count+= config(empty[(i+j) % count_empty].i,empty[(i+j) % count_empty].j,size,temp);
			}
			max = (max > count)?max:count;
		}
		printf("%d\n",max);
		scanf("%d", &size);
	}

return 0;
}