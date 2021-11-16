NAME= philo

all : $(NAME)

$(NAME) :
		gcc -o $@ *.c -pthread

clean :

fclean : clean
	rm -f ./philo

re : fclean all