exe = raycast

$(exe): src
	$(CC) -O3 -Wall -Wextra $(CFLAGS) -o $(exe) src/*.c -lm -lncurses

clean:
	$(RM) $(exe)
