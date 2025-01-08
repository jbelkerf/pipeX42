# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbelkerf <jbelkerf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 11:57:31 by jbelkerf          #+#    #+#              #
#    Updated: 2025/01/08 12:05:13 by jbelkerf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT_DIR = ./libft
M_SRC =  ./libft/libft.a ft_split2.c check_cmd.c pipex.c 
M_BON = ft_split2.c check_cmd.c  ./get_the_next_line/get_next_line_utils.c \
./get_the_next_line/get_next_line.c pipex_bonus.c here_doc.c ./libft/libft.a
CC = cc
			
all:
	$(MAKE) -C $(LIBFT_DIR) 
	$(CC)  $(M_SRC)  -o $(NAME)
	
bonus:
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	$(CC)  $(M_BON)  -o $(NAME)
	
clean:
	@$(MAKE) clean -C ./libft
	rm pipex
fclean: $(clean)
re: $(fclean) $(all)
