include sources.mk

CC_HOST=gcc
CC_KL25Z=arm-none-eabi-gcc
CC_BBB=arm-linux-gnueabi-gcc

OPTIMIZATION=0
C_STD=C99
ARCH_KL25Z=armv6-M
CPU_KL25Z=cortex-m0plus
SPECS_KL25Z=nosys.specs
CFLAGS_COMMON= -Wall -Werror -g -O$(OPTIMIZATION) -std=$(C_STD)
CFLAGS_KL25Z= -mcpu=$(CPU_KL25Z) -mthumb -march=$(ARCH_KL25Z) \
	      -mfpu=fpv4-sp-d16 --specs=$(SPECS_KL25Z) \
	      $(CFLAGS_COMMON)
CFLAGS_BBB= $(CFLAGS_COMMON)
CFLAG_HOST= $(CFLAGS_COMMON)

LINKERFILE.MD= ./../platform/MKL25Z128xxx4_flash.ld
LD_KL25Z= -T $(LINKERFILE.MD)

INCLUDES_COMMON= -I ./../include/common/
INCLUDES_KL25Z = -I ./../include/kl25z \
		 -I ./../include/CMSIS \
		 $(INCLUDES_COMMON)
INCLUDES_BBB = 	-I ./../include/CMSIS \
	      	$(INCLUDES_COMMON)
INCLUDES_HOST = $(INCLUDES_COMMON)


ifeq ($(PLATFORM),KL25Z)
CC=$(CC_KL25Z)
CFLAGS=$(CFLAGS_KL25Z)
INCLUDES+=$(INCLUDES_KL25Z)
LD=$(LDFLAGS_KL25Z)
SRCS=$(SRCS_COMMON_C) $(SRCS_KL25Z_C)
else ifeq ($(PLATFORM),BBB)
CC=$(CC_BBB)
CFLAGS=$(CFLAGS_BBB)
INCLUDES+=$(INCLUDES_BBB)
SRCS=$(SRCS_COMMON_C)
else ifeq ($(PLATFORM),HOST)
CC=$(CC_HOST)
CFLAGS=$(CFLAGS_HOST)
INCLUDES+=$(INCLUDES_HOST)
SRCS=$(SRCS_COMMON_C)
else
#echo 'No Platform specified. Taking Default.' 
CC=$(CC_HOST)
CFLAGS=$(CFLAGS_HOST)
INCLUDES=$(INCLUDES_HOST)
SRCS=$(SRCS_COMMON_C)
endif

OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.dep)

%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJS)


