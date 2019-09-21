main: Source.cpp
	g++ Source.cpp -o simpleScheduler
run:
	./simpleScheduler < test 
	./simpleScheduler < test1 
	./simpleScheduler < test2 
	./simpleScheduler < test3 

valgrindTest:
	valgrind ./simpleScheduler < test
	valgrind ./simpleScheduler < test1
	valgrind ./simpleScheduler < test2
	valgrind ./simpleScheduler < test3

leak:
	valgrind --leak-check=full ./simpleScheduler < test

leak1:
	valgrind --leak-check=full ./simpleScheduler < test

leak2:
	valgrind --leak-check=full ./simpleScheduler < test

leak3:
	valgrind --leak-check=full ./simpleScheduler < test
	
clean: 
	rm simpleScheduler
