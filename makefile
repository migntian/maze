.PHONY:clean
main:maze.c
	gcc -o $@ $^
clean:
	rm main
