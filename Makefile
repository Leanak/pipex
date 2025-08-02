# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/17 13:04:31 by lenakach          #+#    #+#              #
#    Updated: 2025/08/02 11:47:34 by lenakach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Nom de l'exec
NAME = pipex
#NAME_BONUS = pipex_bonus

#Compilateur et flags
CC = cc
FLAGS = -Wall -Wextra -Werror
#Push_swap mandatory

#Dossiers
SRC_DIR = src
#SRC_BONUS_DIR = bonus
LIBFT_DIR = libft
#GNL_DIR = libft/get_next_line

#Includes
INCLUDES = -Iincludes -I$(LIBFT_DIR)/includes

#Bibliotheques
LIBFT = $(LIBFT_DIR)/libft.a

#Sources
SRC = $(SRC_DIR)/pipex.c $(SRC_DIR)/error.c	$(SRC_DIR)/free.c \
	$(SRC_DIR)/process.c $(SRC_DIR)/utils.c
#SRC_BONUS =

#GNL = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c 

SRCS = $(SRC)
#SRCS_BONUS = $(GNL) $(SRC_BONUS)
OBJS = $(SRCS:.c=.o)
#OBJS_BONUS = $(SRCS_BONUS:.c=.o)
 
#Commandes
RM = rm -f

#Regles
all : $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Compilation de LIbft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

#bonus: $(LIBFT) $(NAME_BONUS)

#$(NAME_BONUS): $(OBJS_BONUS)
#$(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re test