# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttorbeyn <ttorbeyn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/09 13:46:03 by ttorbeyn          #+#    #+#              #
#    Updated: 2022/04/09 13:46:08 by ttorbeyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

INCLUDE			=	-I include

SRC				=	./ft_philo.c \
					./ft_error.c \
					./ft_set.c \
					./ft_utils.c \
					./ft_utils2.c \
					./libft/ft_atoi.c \
					./libft/ft_putnbr.c \
					./libft/ft_putchar.c \
					./libft/ft_putstr.c \
					./libft/ft_strjoin.c \
					./libft/ft_strlen.c

OBJS			=	$(SRC:.c=.o)

RM				= 	@rm -f

NAME			=	philo

all: 		$(NAME)

$(NAME):
			@$(CC) $(CFLAGS) $(SRC) $(INCLUDE) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) philo

re:			fclean all

.PHONY:		all clean fclean re save
