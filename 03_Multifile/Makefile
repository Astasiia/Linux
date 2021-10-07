GENERATES = prog liboutput_static.a prog-a liboutput.so prog-so README
TRASH = *.o *~ o.* *.txt

%.o:	%.c
		gcc $< -c -o $@

all:	prog liboutput_static.a prog-a liboutput.so prog-so README

prog:   const.o fun.o prog.o
		gcc $^ -o $@

prog-a:	prog.o liboutput_static.a
		gcc -L. $< -loutput_static -o $@

prog-so:	prog.o liboutput.so
			gcc -L. $< -loutput -o $@

README:	prog
		./$< 2> $@

liboutput_static.a:	fun.o const.o
					ar -rcs $@ $^

liboutput.so:	fun.o const.o
				gcc -shared $^ -o $@

distclean:	clean
			rm -rf $(GENERATES)

clean:
		rm -f $(TRASH)

test0:	prog prog-a prog-so
		./prog 2> prog_0.txt
		./prog-a 2> prog-a_0.txt
		./prog-so 2> prog-so_0.txt
		cmp prog_0.txt prog-a_0.txt || true
		cmp prog_0.txt prog-so_0.txt || true
		cmp prog-a_0.txt prog-so_0.txt || true

test1:	prog prog-a prog-so
		./prog a 2> prog_1.txt
		./prog-a a 2> prog-a_1.txt
		./prog-so a 2> prog-so_1.txt
		cmp prog_1.txt prog-a_1.txt || true
		cmp prog_1.txt prog-so_1.txt || true
		cmp prog-a_1.txt prog-so_1.txt || true

test3:	prog prog-a prog-so
		./prog a b c 2> prog_3.txt
		./prog-a a b c 2> prog-a_3.txt
		./prog-so a b c 2> prog-so_3.txt
		cmp prog_1.txt prog-a_1.txt || true
		cmp prog_1.txt prog-so_1.txt || true
		cmp prog-a_1.txt prog-so_1.txt || true

test:	test0 test1 test3
