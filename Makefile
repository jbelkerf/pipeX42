NAME=pipex

all:
	gcc libft/libft.a pipex.c -o pipex
clean:
	rm pipex
fclean: $(clean)
re: $(fclean) $(all)
