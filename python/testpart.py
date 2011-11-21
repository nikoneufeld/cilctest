#!/usr/bin/env python
import part
import sys
a=[5,3,7,1,4]
if len(sys.argv) > 1:
	a = sys.argv[1:]

print part.part(a,0,len(a)-1)


