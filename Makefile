NAME = pipex
M_SRC = ft_split2.c check_cmd.c pipex.c
all:
	$(MAKE) -C ./libft
	$(MAKE) clean -C ./libft
	cc  $(M_SRC) ./libft/libft.a -o pipex
clean:
	rm pipex
fclean: $(clean)
re: $(fclean) $(all)
