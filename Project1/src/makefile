include sources.mk

CC_HOST=gcc
CC_KL25Z=arm-none-eabi-gcc
CC_BBB=arm-linux-gnueabi-gcc

#VARIABLE for LIB creation
AR_HOST=ar
AR_KL25Z=arm-none-eabi-gcc-ar
AR_BBB=arm-linux-gnueabi-gcc-ar

OPTIMIZATION=0
C_STD=c99
ARCH_KL25Z=armv6-M
CPU_KL25Z=cortex-m0plus
SPECS_KL25Z=nosys.specs
CFLAGS_COMMON:= -Wall -Werror -g -O$(OPTIMIZATION) -std=$(C_STD)
CFLAGS_KL25Z:= -mcpu=$(CPU_KL25Z) -mthumb -march=$(ARCH_KL25Z) \
	      -mfpu=fpv4-sp-d16 --specs=$(SPECS_KL25Z) -mfloat-abi=soft\
	      $(CFLAGS_COMMON)
CFLAGS_BBB:= $(CFLAGS_COMMON)
CFLAGS_HOST:= $(CFLAGS_COMMON)

#Compile time switches for Selecting the Project1 and VERBOSE
ifeq ($(VERBOSE),true)
	CPPFLAGS:= -DVERBOSE -DPROJECT1
else
	CPPFLAGS:= -DPROJECT1
endif

BASENAME= project1
MAPFILE=$(BASENAME).map
OUTPUT_ELF=$(BASENAME).elf	
LIB_PATH=./../lib/
LIB_FILENAME=$(LIB_PATH)lib$(BASENAME).a

LINKERFILE.LD= ./../platform/MKL25Z128xxx4_flash.ld
LD_KL25Z= -T $(LINKERFILE.LD)

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
	AR_CC=$(AR_KL25Z)
	CFLAGS=$(CFLAGS_KL25Z)
	INCLUDES=$(INCLUDES_KL25Z)
	LINKER=$(LD_KL25Z)
	SRCS=$(SRCS_COMMON_C) $(SRCS_KL25Z_C)
	SRCS_S=$(SRCS_KL25Z_S)
	CPPFLAGS+= -DPLATFORM_KL25Z
	OBJS_LIB:=$(SRCS_KL25Z_C:.c=.o) $(SRCS_KL25Z_S:.S=.o)
	SIZE=arm-none-eabi-size
else ifeq ($(PLATFORM),BBB)
	CC=$(CC_BBB)
	AR_CC=$(AR_BBB)
	CFLAGS=$(CFLAGS_BBB)
	INCLUDES+=$(INCLUDES_BBB)
	SRCS=$(SRCS_COMMON_C)
	SIZE=arm-linux-gnueabi-size
else ifeq ($(PLATFORM),HOST)
	CC=$(CC_HOST)
	AR_CC=$(AR_HOST)
	CFLAGS=$(CFLAGS_HOST)
	INCLUDES+=$(INCLUDES_HOST)
	SRCS=$(SRCS_COMMON_C)
	SIZE=size
else
	PLATFORM=No PLATFORM defined. Taking HOST as PLATFORM
	AR_CC=$(AR_HOST)
	CC=$(CC_HOST)
	CFLAGS=$(CFLAGS_HOST)
	INCLUDES=$(INCLUDES_HOST)
	SRCS=$(SRCS_COMMON_C)
	SIZE=size
endif

OBJS=$(SRCS:.c=.o) $(SRCS_S:.S=.o)
DEPS=$(SRCS:.c=.d)
ASMS=$(SRCS:.c=.asm)
PREPS=$(SRCS:.c=.i)
OBJS_LIB+= debug.o memory.o conversion.o project1.o

.PHONY:PRINT_PLATFORM
PRINT_PLATFORM:
	@echo "\n-----BUILDING FOR PLATFORM - $(PLATFORM)----------\n"

%.o: %.c
	@echo "Building $@ from $<"	
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Build Finish\n"

%.d: %.c 
	@echo "Building $@ from $<"	
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -M $< -o $@
	@echo "Build Finish\n"

%.o: %.S
	@echo "Building $@ from $<"	
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Build Finish\n"


%.asm: %.c 
	@echo "Building $@ from $<"	
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -S $< -o $@
	@echo "Build Finish\n"


%.i: %.c 
	@echo "Building $@ from $<"	
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) -E $< -o $@
	@echo "Build Finish\n"

.PHONY: compile-all
compile-all: PRINT_PLATFORM $(OBJS)

.PHONY: build
build: 	PRINT_PLATFORM $(OBJS) $(DEPS) 
	@echo "Building and Linking. Generating - $(OUTPUT_ELF) , $(MAPFILE)\n" 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LINKER) $(INCLUDES) $(OBJS) -o $(OUTPUT_ELF)
	@echo "Build and Link Complete\n"
	

.PHONY: clean
clean:	clean-lib
	@echo "Removing all the .o .asm .i .elf .map files generated\n"
	rm -rf $(OBJS) startup_MKL25Z4.o system_MKL25Z4.o $(ASMS) $(PREPS) $(DEPS) system_MKL25Z4.d $(OUTPUT_ELF) $(MAPFILE)
	@echo "Clean Complete\n"

.PHONY: generate-lib
generate-lib: $(OBJS_LIB) 
	@echo "Generating Library.\n"
	$(AR_CC) -cq $(LIB_FILENAME) $?
	@echo "Library Created at $(LIB_FILENAME)"
	@echo "Library $(LIB_FILENAME) contains:"
	$(AR_CC) -t $(LIB_FILENAME)
	@echo ""

.PHONY: build-lib
build-lib: PRINT_PLATFORM generate-lib main.o
	@echo "Building and Linking using Library libproject1.a. Generating - $(OUTPUT_ELF), $(MAPFILE)" 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LINKER) $(INCLUDES) main.o -L$(LIB_PATH) -l$(BASENAME) -o $(OUTPUT_ELF)
	@echo "Build and Link Complete using Library $(LIB_FILENAME)"

.PHONY: clean-lib
clean-lib:
	@echo "Removing $(LIB_FILENAME)\n"
	rm -rf $(LIB_FILENAME)
	@echo "Clean LIB complete\n"

.PHONY: size
size:	build
	$(SIZE) --format=svr project1.elf
	#size --format=svr project1.elf

.PHONY: help
help:
	@echo "\tBuilds available : \n\
		1. compile-all 	: Compiles all the .c/.s files to .o files \n\
		2. build	: Compiles and Links all the .o files to .elf output file\n \
		3. clean	: Cleans all the make generated files \n\
	       	4. generate-lib	: Generates the .a library from .o files \n\
		5. build-lib	: Generates the .a library, links it with main.o to generate .elf output file\n \
		6. size		: Executes 2. build target and creates a code size file.\n \
	     	Switches available:\n\
		1. PLATFORM = { HOST, BBB, KL25Z }\n \
		2. VERBOSE  = true\n"

