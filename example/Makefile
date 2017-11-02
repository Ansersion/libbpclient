INCLUDES = -I../inc

CC = cc
COMPILE_OPTS =		$(INCLUDES) -I. -O2 -c

MACRO 	=
MACRO 	= -DBP_CPU64

CFLAGS +=		$(COMPILE_OPTS) 
CFLAGS +=		$(MACRO) 

SRC =
OBJ =
SRC 	+= ${wildcard *.c}
OBJ 	+= ${patsubst %.c, %.o, $(SRC)}

TARGET = bpclient
all: $(TARGET)

$(TARGET): $(OBJ)
	gcc -o $@ $(OBJ) ../libbpclient.a

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) $< -o $@ -MMD -MF $*.d -MP

clean:
	-rm -rf *.$(OBJ) $(ALL) *.d core *.core *~ inc/*~ src/*.d

install:
	@echo "install not supported\n"

##### Any additional, platform-specific rules come here:
