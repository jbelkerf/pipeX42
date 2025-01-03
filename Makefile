NAME=pipex

all:
	$(MAKE) -C ./libft
	$(MAKE) clean -C ./libft
	gcc  *.c ./libft/libft.a -o pipex
clean:
	rm pipex
fclean: $(clean)
re: $(fclean) $(all)
