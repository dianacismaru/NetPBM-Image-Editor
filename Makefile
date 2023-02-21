# Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

TARGETS=apply.o basics.o crop.o load.o rotate.o save.o select.o
CFLAGS=-Wall -Wextra -std=c99

build: $(TARGETS)
	gcc $(CFLAGS) -o image_editor $^ image_editor.c -lm
	rm -f $(TARGETS)

apply.o: apply.c
	$(CC) $(CFLAGS) -c -o $@ $^

basics.o: basics.c
	$(CC) $(CFLAGS) -c -o $@ $^

crop.o: crop.c
	$(CC) $(CFLAGS) -c -o $@ $^

load.o: load.c
	$(CC) $(CFLAGS) -c -o $@ $^

rotate.o: rotate.c
	$(CC) $(CFLAGS) -c -o $@ $^

save.o: save.c
	$(CC) $(CFLAGS) -c -o $@ $^

select.o: select.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f image_editor *.
pack:
	zip -FSr 311CA_CismaruDianaIuliana_Tema3.zip README Makefile *.c *.h

.PHONY: pack clean
