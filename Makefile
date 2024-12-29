NAME=pipex

all:
	gcc *.c -o pipex
clean:
	rm pipex
fclean: $(clean)
re: $(fclean) $(all)
