# To compile app-conway.c and generate gif automatically: make ARGS = "data/file.txt" run

CC = gcc
CFLAGS = -g -std=c99 -Wall -I ./include

.PHONY: clean doc

doc:
	doxygen conf/doxygen.conf

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

##### read-file #####

read-file: read-file.o
	$(CC) $(CFLAGS) -o $@ $^

##### write-fact #####

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o $@ $^

##### conway-naive #####

conway-naive: conway-naive.o
	$(CC) $(CFLAGS) -o $@ $^

launch-conway-naive: conway-naive
	./conway-naive

##### app-cell #####

app-cell: cell.o app-cell.o
	$(CC) $(CFLAGS) -o $@ $^

run-cell: app-cell
	./app-cell

##### app-generate-image #####

app-generate: app-generate-image.o generate-image.o cell.o
	$(CC) $(CFLAGS) -o $@ $^

run-generate: app-generate
	./app-generate

##### app-load #####

app-load: app-load.o load.o cell.o
	$(CC) $(CFLAGS) -o $@ $^

run-load: app-load
	./app-load

##### app-conway #####

app-conway: cell.o generate-image.o load.o app-conway.o
	$(CC) $(CFLAGS) -o $@ $^

run-conway: app-conway
	./app-conway ${ARGS}

##### generate-animation #####

generate-animation:
	convert -delay 10 -loop 0 out/*.ppm gif/animation.gif

##### run #####

compile-all: clean app-cell app-load app-generate app-conway

run: clean app-conway run-conway generate-animation
	eog gif/animation.gif &

add-files-svn:
	svn add --force *.txt src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q

clean:
	rm -f *.o read-file conway-naive write-fact app-cell app-conway app-generate app-generate-image app-load app-run
	rm -f out/*.ppm


