NAME=pipex

all:
	gcc pipex.c -o pipex
clean:
	rm pipex
fclean: $(clean)
re: $(fclean) $(all)
