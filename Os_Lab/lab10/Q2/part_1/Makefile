CFLAGS = -lrt -Wall -Wextra

all: score_updater score_viewer

score_updater: score_updater.c protocol.h
	$(CC) score_updater.c -o score_updater $(CFLAGS)

score_viewer: score_viewer.c protocol.h
	$(CC) score_viewer.c -o score_viewer $(CFLAGS)

clean:
	rm -f score_updater score_viewer