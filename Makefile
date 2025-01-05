NAME = pipex
M_SRC = ft_split2.c check_cmd.c pipex.c
M_BON = ft_split2.c check_cmd.c pipex_bonus.c
all:
	$(MAKE) -C ./libft
	$(MAKE) clean -C ./libft
	cc  $(M_SRC) ./libft/libft.a -o pipex
bonus:
	
	cc  $(M_BON) ./libft/libft.a -o pipex_bonu
clean:
	rm pipex
fclean: $(clean)
re: $(fclean) $(all)
