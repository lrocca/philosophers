# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrocca <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/01 17:52:32 by lrocca            #+#    #+#              #
#    Updated: 2021/10/18 18:23:07 by lrocca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

# compilation options
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -pthread
IFLAGS	=	-I$(INCDIR)
MKDIR	=	mkdir -p

FILES	=	main.c \
			thread.c \
			utils/ft_atoi.c \
			utils/ft_error.c \
			utils/ft_get_time.c \
			utils/ft_log.c \
			utils/ft_usleep.c

SRCDIR	=	./src
OBJDIR	=	./obj
INCDIR	=	./inc

SRC	=	$(addprefix $(SRCDIR)/, $(FILES))
OBJ	=	$(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@

clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
