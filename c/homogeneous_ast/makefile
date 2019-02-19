CC = gcc
CFLAGS = -std=c99
OBJDIR = obj
SRCS = main.c token.c ast.c
OBJS = $(SRCS:%.c=%.o)
TARGET = parser

.PHONY : all
all : $(OBJS)
	$(CC) $(OBJDIR)/* -o $(TARGET)

main.o : main.c token.o ast.o
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

token.o : token.c token.h
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@

ast.o : ast.c ast.h token.h
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$@


.PHONY : clean
clean :
	$(RM) $(OBJDIR)/* $(TARGET)
