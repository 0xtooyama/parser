CC = gcc
OBJDIR = obj
SRCS = main.c lexer.c
OBJS = $(SRCS:%.c=%.o)
TARGET = lexer

.PHONY : all
all : $(OBJS)
	$(CC) $(OBJDIR)/* -o $(TARGET)

main.o : main.c lexer.h
	$(CC) -c $< -o $(OBJDIR)/$@

lexer.o : lexer.c
	$(CC) -c $< -o $(OBJDIR)/$@

.PHONY : clean
clean :
	$(RM) $(OBJDIR)/* $(TARGET)
