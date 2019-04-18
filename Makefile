exe = raycast

$(exe): src
	$(CC) -Wall -Wextra -o $(exe) src/*.c -lm -lncurses

clean:
	$(RM) $(exe)
