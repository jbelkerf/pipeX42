NAME = pipex
M_SRC = ft_split2.c check_cmd.c pipex.c
M_BON = ft_split2.c check_cmd.c ./get_the_next_line/get_next_line.h ./get_the_next_line/get_next_line_utils.c ./get_the_next_line/get_next_line.c pipex_bo.c
all:
	$(MAKE) -C ./libft
	$(MAKE) clean -C ./libft
	cc  $(M_SRC) ./libft/libft.a -o pipex
bonus:
	
	cc  $(M_BON) ./libft/libft.a 
clean:
	rm pipex
fclean: $(clean)
re: $(fclean) $(all)
