compiler: lex.o synt.o gen.o symbols.o
	gcc -o compiler lex.o synt.o gen.o symbols.o -I. -g

compiler_win: lex.o synt.o gen_win.o symbols.o
	gcc -o compiler4win lex.o synt.o gen_win.o symbols.o -I. -g

lex.o: lex.c
	gcc -c -g lex.c

synt.o: synt.c
	gcc -c -g synt.c

gen.o: gen.c
	gcc -c -g gen.c

gen_win.o: gen_win.c
	gcc -c -g gen_win.c

symbols.o: symbols.c
	gcc -c -g symbols.c

tstLex: lex.o tst_lex.o
	gcc -o tstLexCompiler lex.o tst_lex.o -I. -g

tst_lex.o: tst_lex.c
	gcc -c -g tst_lex.c

run1: compiler
	./compiler code1.cc || true

run2: compiler
	./compiler code2.cc || true

RunAssembly1: compiler
	nasm -f elf64 code1.cc.asm
	ld -e main -melf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc code1.cc.o -o code1.exe
	./code1.exe

RunAssembly2: compiler
	nasm -f elf64 code2.cc.asm
	ld -e main -melf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc code2.cc.o -o code2.exe
	./code2.exe

clean:
	rm *.o compiler