PWD := $(shell pwd)
SRC := lk_01 lk_02 lk_03 lk_04
INC := include
VPATH = $(SRC) $(INC)
vpath %.c $(SRC)
vpath %.h $(INC)

CC := gcc
CCPP := g++
FLAG := -I$(INC) -c
FLAGG := -I$(INC) -c -g

lk03_2: lk03_2.o
	$(CC) -o $@ $<
	@rm -f *.o

lk03_2.o: lk03_2.c
	@$(CC) $(FLAG) $<

lk03_1: lk03_1.o
	$(CC) -o $@ $<
	@rm -f *.o

lk03_1.o: lk03_1.c
	@$(CC) $(FLAG) $<

lk02: lk02.o
	$(CC) -o $@ $<
	@rm -f *.o

lk02.o: lk02.c
	@$(CC) $(FLAG) $<

lk01: lk01.o
	$(CC) -o $@ $<
	@rm -f *.o

lk01.o: lk01.c
	@$(CC) $(FLAG) $<

# .PHONY: clean
clean:
	@rm -f *.o
	@rm -f lk01
	@rm -f lk02
	@rm -f lk03_1
	@rm -f lk03_2