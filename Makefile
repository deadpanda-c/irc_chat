
all:
	make -C client
	make -C server

clean:
	make -C client clean
	make -C server clean

fclean:	clean
	make -C client fclean
	make -C server fclean

re:	fclean	all
