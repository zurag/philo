NAME		= philo
CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -MMD

CPPFLAGS	= $(CFLAGS) -march=native -O2 -pipe

HEADERS		= includes/

SRCS =	srcs/main.c srcs/utils.c

OBJS = $(SRCS:.c=.o)

$(NAME):		$(OBJS)
				$(CC) $(CPPFLAGS) -I $(HEADERS) $(OBJS) -pthread -o $(NAME)

all:			$(NAME)

.c.o:
				$(CC) $(CPPFLAGS) -I $(HEADERS) -o $@ -c $<

$(OBJS):		$(HEADERS)

clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS:.o=.d)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re