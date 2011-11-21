n=0
def part(x, l, r):	
	# select middle element
        # distribute elements smaller to the left, larger to the right
        # repeat sort
        # terminate at two elements
	global n
#	print "start l %d r %d" % (l,r) 
	if (l >= r): return x
	if (l + 1 == r):
		if (x[l] < x[r]): return x
		t= x[l]; x[l] = x[r]; x[r] = t
		return x
	m = (r - l) / 2 + l
	i = l; j = r
#	print x[l:m], x[m], x[m+1:r+1],"m %d i %d j %d" % (m, i, j)
	while (i < m and j > m):
#		print x[l:m], x[m], x[m+1:r+1]
		if x[i] < x[m]: i+=1; continue
		t = x[j]; x[j] = x[i]; x[i] = t
		j-=1 
#	print x[l:m], x[m], x[m+1:r+1],"m %d i %d j %d" % (m, i, j)
	if (i == m):
		k = m + 1
		while (k <= j):
#			print x[l:m], x[m], x[m+1:r+1],"m %d k %d j %d" % (m, k, j)
			if x[k] > x[m]:
				t = x[j]; x[j] = x[k]; x[k] = t
				j -= 1
				continue
			if x[k] <  x[m]:
				t = x[k]; x[k] = x[m]; x[m] = t
				m += 1
				k = m + 1
				continue
			k += 1
#		print x[l:m], x[m], x[m+1:r+1],"m %d k %d j %d" % (m, k, j)
	else:
		k = m - 1
		while (k >= i):
			if x[k] < x[m]:
				t = x[i]; x[i] = x[k]; x[k] = t
				i += 1
				continue
			if x[k] > x[m]:
				t = x[k]; x[k] = x[m]; x[m] = t
				m -= 1
				k = m - 1
				continue	
			k -= 1
#	print "fin ", x[l:m], x[m], x[m+1:r+1],"m %d k %d j %d" % (m, k, j)
	n+=1
#	if n > 3: return x
#	print "l: %d m-1: %d" % (l, m-1); 
	part(x, l, m - 1)
#	print "m+1: %d r: %d" % (m+1, r); 
	part(x, m + 1, r)
	return x
