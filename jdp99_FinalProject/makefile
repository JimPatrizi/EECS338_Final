all:  q1	q2

q1:
	gcc mergev2.c -o normal_merge

q2:
	gcc openmp.c -o parallel_merge -fopenmp

clean:
	rm -f normal_merge
	rm -f parallel_merge
