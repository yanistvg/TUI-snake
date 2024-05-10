PROGNAME=TUI-snake

CC=gcc
CFLAGS=-Wall -Wextra -Wconversion

OBJS= main.o              \
      terminal-interact.o \
      draws.o             \
      snake.o             \
	  apple.o

all: ${OBJS}
	${CC} ${CFLAGS} -o ${PROGNAME} ${OBJS}

main.o: main.c libs/headers/main.h
	${CC} ${CFLAGS} -c main.c
terminal-interact.o: libs/srcs/terminal-interact.c
	${CC} ${CFLAGS} -c libs/srcs/terminal-interact.c
draws.o: libs/srcs/draws.c
	${CC} ${CFLAGS} -c libs/srcs/draws.c
snake.o: libs/srcs/snake.c
	${CC} ${CFLAGS} -c libs/srcs/snake.c
apple.o: libs/srcs/apple.c
	${CC} ${CFLAGS} -c libs/srcs/apple.c

clean:
	rm ${OBJS} ${PROGNAME}
