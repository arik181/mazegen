# Change Me
NAME	= mazegen
REQ1	= maze
REQ2	= node
REQ3	= screen
CREQS	= $(REQ1).cpp $(REQ2).cpp $(REQ3).cpp
HREQS	= $(REQ1).h $(REQ2).h $(REQ3).h
ALLREQS	= $(NAME).cpp $(NAME).h $(CREQS) $(HREQS)
ADIR	= arik182

# Constant Variables
COMPILER	= g++ -Wall
ASSEMBLER	= as
LINKER		= ld

# Flags
CURSES		= -lcurses
NC		= -lncurses
DEBUG		= -g
#OPT		= -O2
#OPT		= -O3
OBJECT		= -c
LINK		= -lc -dynamic-linker /lib/ld-linux.so.2
PROFILE		= -pg
MATH		= -lm

### Compile the application ###

$(NAME) : $(ALLREQS)
	$(COMPILER) -o $(NAME) $(NAME).cpp $(CREQS) $(NC) $(MATH)

run : $(NAME)
	./$(NAME)

### Special Cases ###

debug : debugtarget
	ctags *.cpp *.h && gdb ./$(NAME)

profile : profiletarget
	echo "Profiling..."
	rm -rf report.out
	rm -rf gmon.out
	echo >> report.out
	echo >> report.out
	echo "--------------------------------------------------------------" >> report.out
	echo >> report.out
	echo "Profile of ./$(NAME)" >> report.out
	echo >> report.out
	./$(NAME) -s $(TESTFILE1) $(CPFILE) >> report.out
	echo >> report.out
	gprof --brief --no-graph ./$(NAME) >> report.out
	vim report.out

debugtarget : $(ALLREQS)
	$(COMPILER) $(DEBUG) -o $(NAME) $(NAME).cpp $(CREQS) $(NC) $(MATH)

profiletarget : $(NAME).cpp $(NAME).h 
	$(COMPILER) $(PROFILE) -o $(NAME) $(NAME).cpp 

clean : $(NAME)
	rm $(NAME) && rm *.o 

dump: $(NAME)
	objdump -d $(NAME) > objcode

tex : 	
	latex $(NAME).tex
	dvipdfm $(NAME).dvi

homework: $(NAME) profile
	echo "Cleaning up..."
	rm -rf $(NAME)
	rm -rf *~
	rm -rf $(ADIR)
	echo "Creating directory..."
	mkdir $(ADIR)
	echo "Copying targets..."
	cp Makefile $(NAME).cpp $(NAME).h report.out typescript.out $(ADIR)/
	tar cvf $(ADIR).tar $(ADIR)
	echo "Done."

test : $(NAME) tests
	script -f -c 'cat ./tests | ./$(NAME)'
	cat typescript | col -b > readablescript
	


