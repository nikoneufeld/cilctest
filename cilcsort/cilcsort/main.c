//
//  main.c
//  cilcsort
//
//  Created by Niko Neufeld on 11/19/11.
//  Copyright (c) 2011 CERN. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
void sort(int *, int, int);
void csort(int *, int, int);
int partition(int *, int, int);

int partition(int *x, int l, int r) {
    int m, i, j, k, t;
    // select middle
    m = (r - l) / 2 + l;
    i = l; j = r;
    //	print x[l:m], x[m], x[m+1:r+1],"m %d i %d j %d" % (m, i, j)
    while (i < m && j > m) {
        //		print x[l:m], x[m], x[m+1:r+1]
        if (x[i] < x[m]) {
            i += 1; 
            continue;       
        }
        t = x[j]; x[j] = x[i]; x[i] = t;
        j -= 1; 
    }
    //	print x[l:m], x[m], x[m+1:r+1],"m %d i %d j %d" % (m, i, j)
    if (i == m) { 
        k = m + 1;
        while (k <= j) { 
            //			print x[l:m], x[m], x[m+1:r+1],"m %d k %d j %d" % (m, k, j)
            if (x[k] > x[m]) {
                t = x[j]; x[j] = x[k]; x[k] = t;
                j -= 1;
                continue;
            }
            if (x[k] <  x[m]) {
                t = x[k]; x[k] = x[m]; x[m] = t;
                m += 1;
                k = m + 1;
                continue;
            }
            k += 1;
            //		print x[l:m], x[m], x[m+1:r+1],"m %d k %d j %d" % (m, k, j)
        }
    } else {
        k = m - 1;
        while (k >= i) {
            if (x[k] < x[m]) {
                t = x[i]; x[i] = x[k]; x[k] = t;
                i += 1;
                continue;
            }
            if (x[k] > x[m]) {
                t = x[k]; x[k] = x[m]; x[m] = t;
                m -= 1;
                k = m - 1;
                continue;
            }
            k -= 1;
            //	print "fin ", x[l:m], x[m], x[m+1:r+1],"m %d k %d j %d" % (m, k, j)
        }
    }
    //	if n > 3: return x
    //        print "l: %d m-1: %d" % (l, m-1); 
    return m;
}

void sort(int *x, int l, int r)	
{
    int m, t;
/* select middle element
   distribute elements smaller to the left, larger to the right
   repeat sort
   terminate at two elements
*/
//	print "start l %d r %d" % (l,r) 
    if (l >= r) return;
    if (l + 1 == r) {
        if (x[l] < x[r]) return;
        t = x[l]; x[l] = x[r]; x[r] = t;
        return;
    }    
    m = partition(x, l, r);
    sort(x, l, m - 1);
    sort(x, m + 1, r);
}
#ifdef _ICC
void csort(int *x, int l, int r)	
{
    int m, t;
    /* select middle element
     distribute elements smaller to the left, larger to the right
     repeat sort
     terminate at two elements
     */
    //	print "start l %d r %d" % (l,r) 
    if (l >= r) return;
    if (l + 1 == r) {
        if (x[l] < x[r]) return;
        t = x[l]; x[l] = x[r]; x[r] = t;
        return;
    }    
    m = partition(x, l, r);
    _Cilk_spawn csort(x, l, m - 1);
    csort(x, m + 1, r);
    _Cilk_sync;
}
#endif
// -O3 icc 12 38.881 s no cilc 18.358 with cilc
int main (int argc, const char * argv[])
{
    int n = 200000000;
    int i, *x;
    struct timeval ts, te;
    if (argc > 1) n = (int) strtoul(argv[1], NULL, 10);
    x = malloc(n * sizeof(int));
    for (i = 0; i < n; x[i++] = random() / (1<<30 / n)); 
    if (n < 40) {
        for (i = 0; i < n; printf("%d, ", x[i++]));
        printf("\n");
    }  
    gettimeofday(&ts, NULL);
    sort(x, 0, n-1);
    gettimeofday(&te, NULL);
    printf("gcc seq %ld us\n", (te.tv_sec * 1000000 + te.tv_usec - ts.tv_sec * 1000000 - ts.tv_usec));
    if (n < 40) {
        printf("\n");
        for (i = 0; i < n; printf("%d, ", x[i++]));
        printf("\n");
    }  
#ifdef _ICC
    for (i = 0; i < n; x[i++] = random() / (1<<30 / n)); 
    gettimeofday(&ts, NULL);
    csort(x, 0, n-1);
    gettimeofday(&te, NULL);
    printf("%ld us\n", (te.tv_sec * 1000000 + te.tv_usec - ts.tv_sec * 1000000 - ts.tv_usec));
#endif
    return 0;
}

