# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 11:57:31 by jbelkerf          #+#    #+#              #
#    Updated: 2025/01/16 16:53:16 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

M_SRC =   ft_split2.c check_cmd.c pipex.c pipex_utils.c pipex_utils1.c     \
ft_split3.c 

B_SRC = ft_split2.c check_cmd.c  ./get_the_next_line/get_next_line_utils.c \
./get_the_next_line/get_next_line.c pipex_bonus.c here_doc.c pipex_utils.c \
pipex_utils1.c ft_split3.c 

M_OBJ = $(M_SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

			
all: $(M_OBJ)
	$(MAKE) -C ./libft 
	$(CC) $(CFLAGS) $(M_OBJ) $(LIBFT) -o $(NAME)
	
%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@
bonus: $(B_OBJ)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(B_OBJ) $(LIBFT) -o $(NAME)
	
clean:
	$(MAKE) clean -C ./libft 
	rm -f $(M_OBJ) $(B_OBJ)
fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)
re: fclean all
