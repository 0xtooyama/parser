CC = gcc
CFLAGS = -std=c99
OBJDIR = obj
SRCS = main.c lexer.c parser.c token.c marker.c
OBJS = $(SRCS:%.c=%.o)
TARGET = parser

.PHONY : all
all : $(OBJS)
	$(CC) $(OBJDIR)/* -o $(TARGET)

main.o : main.c lexer.h parser.h
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

lexer.o : lexer.c
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

parser.o : parser.c parser.h lexer.h
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

token.o : token.c token.h
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

marker.o : marker.c marker.h
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

.PHONY : clean
clean :
	$(RM) $(OBJDIR)/* $(TARGET)
