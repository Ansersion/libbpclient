INCLUDES = -I../inc

CC = cc
COMPILE_OPTS =		$(INCLUDES) -I. -c -g
# COMPILE_OPTS += -O2

MACRO 	=
MACRO 	= -DBP_CPU64
MACRO 	+= -DDEBUG

CFLAGS +=		$(COMPILE_OPTS) 
CFLAGS +=		$(MACRO) 

SRC =
OBJ =
SRC 	+= ${wildcard *.c}
OBJ 	+= ${patsubst %.c, %.o, $(SRC)}

TARGET = bpclient_dev
all: $(TARGET)

$(TARGET): $(OBJ)
	gcc -o $@ $(OBJ) ../libbpclient.a

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) $< -o $@ -MMD -MF $*.d -MP

clean:
	-rm -rf $(TARGET) *.$(OBJ) $(ALL) *.d core *.core *~ inc/*~ src/*.d

install:
	@echo "install not supported\n"

##### Any additional, platform-specific rules come here:
