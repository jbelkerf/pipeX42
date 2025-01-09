# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 11:57:31 by jbelkerf          #+#    #+#              #
#    Updated: 2025/01/09 18:29:49 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a

M_SRC =   ft_split2.c check_cmd.c pipex.c 

B_SRC = ft_split2.c check_cmd.c  ./get_the_next_line/get_next_line_utils.c \
./get_the_next_line/get_next_line.c pipex_bonus.c here_doc.c 

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
	rm $(M_OBJ) $(B_OBJ)
fclean: clean
	make fclean -C ./libft
	rm $(NAME)
re: $(fclean) $(all)
