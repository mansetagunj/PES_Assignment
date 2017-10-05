include sources.mk

CC_HOST=gcc
CC_KL25Z=arm-none-eabi-gcc
CC_BBB=arm-linux-gnueabi-gcc

OPTIMIZATION=0
C_STD=c99
ARCH_KL25Z=armv6-M
CPU_KL25Z=cortex-m0plus
SPECS_KL25Z=nosys.specs
CFLAGS_COMMON:= -Wall -Werror -g -O$(OPTIMIZATION) -std=$(C_STD)
CFLAGS_KL25Z:= -mcpu=$(CPU_KL25Z) -mthumb -march=$(ARCH_KL25Z) \
	      -mfpu=fpv4-sp-d16 --specs=$(SPECS_KL25Z) \
	      $(CFLAGS_COMMON)
CFLAGS_BBB:= $(CFLAGS_COMMON)
CFLAGS_HOST:= $(CFLAGS_COMMON)

ifeq ($(VERBOSE),true)
CPPFLAGS:= -DVERBOSE -DPROJECT1
else
CPPFLAGS:= -DPROJECT1
endif

BASENAME= project1
MAPFILE=$(BASENAME).map

LINKERFILE.MD= ./../platform/MKL25Z128xxx4_flash.ld
LD_KL25Z= -T $(LINKERFILE.MD)

INCLUDES_COMMON:=-I ./../include/common/

INCLUDES_KL25Z:=-I ./../include/kl25z \
		-I ./../include/CMSIS \
		$(INCLUDES_COMMON)

INCLUDES_BBB:=	-I ./../include/CMSIS \
	      	$(INCLUDES_COMMON)

INCLUDES_HOST := $(INCLUDES_COMMON)


LDFLAGS= -Xlinker -Map=$(MAPFILE)

ifeq ($(PLATFORM),KL25Z)
CC=$(CC_KL25Z)
CFLAGS=$(CFLAGS_KL25Z)
INCLUDES=$(INCLUDES_KL25Z)
LD=$(LD_KL25Z)
SRCS=$(SRCS_COMMON_C) $(SRCS_KL25Z_C)
SRCS_S=$(SRCS_KL25Z_S)
CPPFLAGS+= -DPLATFORM_KL25Z
else ifeq ($(PLATFORM),BBB)
CC=$(CC_BBB)
CFLAGS=$(CFLAGS_BBB)
INCLUDES+=$(INCLUDES_BBB)
SRCS=$(SRCS_COMMON_C)
LD=
SRCS_S=$(SRCS_KL25Z_S)
else ifeq ($(PLATFORM),HOST)
CC=$(CC_HOST)
CFLAGS=$(CFLAGS_HOST)
INCLUDES+=$(INCLUDES_HOST)
SRCS=$(SRCS_COMMON_C)
LD=
#SRCS_S=$(SRCS_KL25Z_S)
else
CC=$(CC_HOST)
CFLAGS=$(CFLAGS_HOST)
INCLUDES=$(INCLUDES_HOST)
SRCS=$(SRCS_COMMON_C)
LD=
#SRCS_S=$(SRCS_KL25Z_S)
endif

OBJS=$(SRCS:.c=.o) $(SRCS_S:.S=.o)
DEPS=$(SRCS:.c=.d)
ASMS=$(SRCS:.c=.asm)
PREPS=$(SRCS:.c=.i)
OUTPUT_ELF=$(BASENAME).elf	


%.o: %.c
	@echo "Using $(CC) - Building $@ from $<"	
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Using $(CC) - Build Finish"

%.d: %.c 
	@echo "Using $(CC) - Building $@ from $<"	
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -M $< -o $@
	@echo "Using $(CC) - Build Finish"

%.o: %.S
	@echo "Using $(CC) - Building $@ from $<"	
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Using $(CC) - Build Finish"


%.asm: %.c 
	@echo "Using $(CC) - Building $@ from $<"	
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -S $< -o $@
	@echo "Using $(CC) - Build Finish"


%.i: %.c 
	@echo "Using $(CC) - Building $@ from $<"	
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -E $< -o $@
	@echo "Using $(CC) - Build Finish"

.PHONY: compile-all
compile-all: $(OBJS)

.PHONY: build
build: $(OBJS) $(DEPS)
	@echo "Using $(CC) - Building and Linknig. Generating - $(OUTPUT_ELF) , $(MAPFILE)" 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LD) $(INCLUDES) $(OBJS) -o $(OUTPUT_ELF)
	@echo "Using $(CC) - Build and Link Complete"

.PHONY: clean
clean:
	@echo "Removing all the .o .asm .i .elf .map files generated"
	rm -rf $(OBJS) $(ASMS) $(PREPS) $(DEPS) $(OUTPUT_ELF) $(MAPFILE)
	@echo "Clean Complete"

