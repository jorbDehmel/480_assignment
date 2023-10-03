# Written for use on Arch linux
# It'll probably work for other linux too

CC := clang++
CFLAGS := -pedantic -Wall -g

all:	main.out writeup.pdf

main.out:	heapsort.o mergesort.o p_queue.o radix.o main.o
	$(CC) $(CFLAGS) -o $@ heapsort.o mergesort.o p_queue.o radix.o main.o

main.o:	main.cpp sort_requirements.hpp
	$(CC) $(CFLAGS) -c -o main.o main.cpp

%.o:	%.cpp %.hpp sort_requirements.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

writeup.pdf:	writeup.tex
	pdflatex writeup.tex

clean:
	rm -rf *.out *.o
