#!/usr/bin/python

n=0

filename="runtime.json"


def run_func(iter=1):
	for i in range(0,iter):
		n=i



if __name__ == "__main__":
	import timeit
	myfunc="from __main__ import run_func"
	
	#Final Execution
	for i in range(0,4):	
		print("Exec\t[\033[35m1\033[0m:\033[34m%i\033[0m]: %f" % (i, timeit.timeit("run_func(iter=10)",setup=myfunc)))
		print("Exec\t[\033[35m2\033[0m:\033[34m%i\033[0m]: %f" % (i, timeit.timeit("run_func(iter=20)",setup=myfunc)))
	
