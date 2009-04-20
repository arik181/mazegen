# Change Me
NAME	= mazegen
REQ1	= maze
REQ2	= node
REQ3	= screen
CREQS	= $(REQ1).cpp $(REQ2).cpp $(REQ3).cpp 
HREQS	= $(REQ1).h $(REQ2).h $(REQ3).h
ALLREQS	= $(NAME).cpp $(NAME).h $(CREQS) $(HREQS)

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

### Compile the application ###

$(NAME) : $(ALLREQS)
	$(COMPILER) -o $(NAME) $(NAME).cpp $(CREQS) $(NC)

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
	$(COMPILER) $(DEBUG) -o $(NAME) $(NAME).cpp $(CREQS) $(NC)

profiletarget : $(ALLREQS)
	$(COMPILER) $(PROFILE) -o $(NAME) $(NAME).cpp $(CREQS) $(NC)

clean : $(NAME)
	rm $(NAME) && rm *.o 

dump: $(NAME)
	objdump -d $(NAME) > objcode

### Send out homework ###

tex : 	
	latex $(NAME).tex
	dvipdfm $(NAME).dvi

TARDIR		= arik182
ADDRESS1 	= arik182@gmail.com
ADDRESS2 	= karlafgr@cs.pdx.edu
SUBJECT		= [CS202 Submission]
ASSIGNMENT	= 'CS202 Assignment 1'

homework: $(ALLREQS) Makefile 
	echo "Cleaning up..."
	rm -rf $(NAME)
	rm -rf *~
	rm -rf $(TARDIR)
	echo "Creating directory..."
	mkdir $(TARDIR)
	echo "Copying targets..."
	cp Makefile design.txt debug.txt $(TARDIR)/
	echo "Creating headers..."
	sh -c "./fileheader.sh $(TARDIR) $(ASSIGNMENT)"
	echo "Creating archive..."
	tar czvf $(TARDIR).tar $(TARDIR)
	echo "Sending email..."
	mpack -a -s '$(SUBJECT)' $(FILE) $(ADDRESS1)
	#mpack -a -s '$(SUBJECT)' $(FILE) $(ADDRESS2)
	echo "Done."

