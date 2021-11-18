NAME= philo

all : $(NAME)

$(NAME) :
		gcc -o $@ *.c -pthread
		./philo 250 410 200 200
		rm -rf ./philo

clean :

fclean : clean
	rm -f ./philo

re : fclean all