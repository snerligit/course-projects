.phony:compile random test verify clean

compile:algo.out verify.out random.out

random.out:algo2.c
	gcc -o random.out algo2.c
algo.out: algo2.c  
	gcc -o algo.out algo2.c
verify.out:verify.c
	gcc -o verify.out verify.c

random:random.out
	./random.out 

test:algo.out
	./algo.out 4 t1.t
	@echo "Output written into file t1.r "
	diff t1.r t1.m
	./algo.out 4 t2.t
	@echo "Output written into file t2.r"
	diff t2.r t2.m
	./algo.out 4 t3.t
	@echo "Output written into file t3.r"
	diff t3.r t3.m
	./algo.out  t4.t
	@echo "Output written into file t4.r"
	diff t4.r t4.m
	./algo.out 4 t5.t
	@echo "Output written into file t5.r"
	diff t5.r t5.m
	./algo.out 4 t6.t
	@echo "Output written into file t6.r"
	diff t6.r t6.m

verify:verify.out
	./verify.out

clean: 
	rm *.out *.r

