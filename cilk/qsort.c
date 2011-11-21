#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void sort(int l, int k, int u) {
	int j, t;
	if (d[k] < d[k+1]) return;
	t = d[k]; d[k] = d[k+1]; d[k+1] = t;
	j = k + 1;
	while (d[j] > d[u]) {
	i	 
		t = d[u]; d[u] = d[k+1]; d[k+1] = t;
	}
		
int main(int argc, char **argv)
{
	int n = 100000;
	int *d, i;

	if (argc > 1) n = strtoul(argv[1], NULL, 10);
        d = malloc(n, sizeof(int));
	for (i = 0; i < n; d[i++] = int(d * rand()));
}				
	
