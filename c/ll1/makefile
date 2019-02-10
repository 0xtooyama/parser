CC = gcc
OBJDIR = obj
SRCS = main.c lexer.c parser.c
OBJS = $(SRCS:%.c=%.o)
TARGET = parser

.PHONY : all
all : $(OBJS)
	$(CC) $(OBJDIR)/* -o $(TARGET)

main.o : main.c lexer.h parser.h
	$(CC) -c $< -o $(OBJDIR)/$@

lexer.o : lexer.c
	$(CC) -c $< -o $(OBJDIR)/$@

parser.o : parser.c parser.h lexer.h
	$(CC) -c $< -o $(OBJDIR)/$@

.PHONY : clean
clean :
	$(RM) $(OBJDIR)/* $(TARGET)
