NAME1 = client
NAME2 = server

SRCS1 = client_src/client.c \
		client_src/client_utils.c \
		utils/ft_atoi.c \
		utils/ft_strlen.c \
		utils/ft_putchar.c \
		utils/ft_putstr.c \


SRCS2 =	server_src/server.c \
		server_src/server_utils.c \
		utils/ft_atoi.c \
		utils/ft_strlen.c \
		utils/ft_putchar.c \
		utils/ft_putstr.c \
		utils/ft_putendl.c \
		utils/ft_putnbr.c \
		utils/ft_lstnew.c \
	  	utils/ft_lstsize.c \
	  	utils/ft_lstadd_back.c \
	  	utils/ft_lstclear.c \

OBJS1 := ${SRCS1:.c=.o}
OBJS2 := ${SRCS2:.c=.o}

CC = gcc

CFLAGS = -g3 -Wall -Wextra -Werror

AR = ar rcs

RM = rm -rf

INC_DIR = headers

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -I ${INC_DIR} $< -o ${<:.c=.o}

all: $(NAME1) $(NAME2)

$(NAME1): ${OBJS1}
		gcc -o $(NAME1) $(OBJS1)

$(NAME2): ${OBJS2}
		gcc -o $(NAME2) $(OBJS2)

clean:
	@${RM} ${OBJS1}
	@${RM} ${OBJS2}

fclean: clean
	@${RM} ${NAME1}
	@${RM} ${NAME2}

re: fclean all

.PHONY: all clean fclean re