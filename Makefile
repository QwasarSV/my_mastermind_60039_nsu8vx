CC = gcc
CFLAGS += -Wall -Werror -Wextra
CFLAGS_DEBUG = $(CFLAGS)
MAIN = my_mastermind
SRCS = main.c \
		my_mastermind.c
OBJS = $(SRCS: .c = .o) 

all: $(MAIN)

$(MAIN): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $(LINKERFLAG) $^

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(MAIN) $(DEBUG)

re: fclean all