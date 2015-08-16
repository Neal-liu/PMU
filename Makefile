CC = arm-linux-gnueabihf-gcc
CFLAGS = -O3 -Wall -mtune=cortex-a15

pmutest: pmutest.o
	$(CC) $(CFLAGS) -o $@ $^

QEMU_CMD = qemu-arm -L /usr/arm-linux-gnueabihf ./pmutest

clean:
	rm -rf pmutest.o pmutest

qemu: pmutest
#	$(call QEMU_CMD)
