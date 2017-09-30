CC_ARM:=arm-linux-gnueabi-gcc
CC_Native:=gcc
UNAME:= $(shell uname -m)

ifeq ($(UNAME),i386)
CC=$(CC_Native)
else ifeq ($(UNAME),armv71)
CC=$(CC_ARM)
endif

all:	TestReverse helloworld HW3_ques2 HW3_ques4

TestReverse : TestReverse.c 
	${CC} -o  TestReverse.out TestReverse.c

helloworld : helloworld.c
	$(CC) -o helloworld.out helloworld.c

HW3_ques2 : HW3_ques2.c
	$(CC) -o HW3_ques2.out HW3_ques2.c

HW3_ques4 : HW3_ques4.c
	$(CC) -o HW3_ques4.out HW3_ques4.c

clean:
	rm *.out
