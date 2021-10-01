# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrocca <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/01 17:52:32 by lrocca            #+#    #+#              #
#    Updated: 2021/10/01 19:44:32 by lrocca           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

# compilation options
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
IFLAGS	=	-I$(INCDIR)
MKDIR	=	mkdir -p

FILES	=	main.c

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
