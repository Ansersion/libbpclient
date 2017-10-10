INCLUDES = -Iinc
SRC_DIR = src

COMPILE_OPTS =		$(INCLUDES) -I. -O2 -c
CC = cc

MACRO 	=
MACRO 	+= -DBP_CPU32

CFLAGS +=		$(COMPILE_OPTS) 
CFLAGS +=		$(MACRO) 

LINK_OPTS =		

LIBRARY_LINK =		ar cr 

LIBRARY_SHARE_LINK =
SHARE_LINK_OPTS =

SRC =
OBJ =
SRC 	+= ${wildcard $(SRC_DIR)/*.c}
OBJ 	+= ${patsubst %.c, %.o, $(SRC)}

TARGET_STATIC_LIB = libbpclient.a
TARGET_SHARE_LIB = libbpclient.so

ALL = 
ALL += $(TARGET_STATIC_LIB) 
#ALL += $(TARGET_SHARE_LIB)

all: $(ALL)

$(TARGET_STATIC_LIB): $(OBJ) 
	$(LIBRARY_LINK) $(LINK_OPTS) $@ $(OBJ)

$(TARGET_SHARE_LIB): $(OBJ) 
	$(LIBRARY_SHARE_LINK) $@ $(LIBRARY_SHARE_LINK_OPTS) $(OBJ)

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) $< -o $@ -MMD -MF $*.d -MP

clean:
	-rm -rf *.$(OBJ) $(ALL) core *.core *~ inc/*~ src/*.d

install:
	@echo "install not supported\n"

##### Any additional, platform-specific rules come here:
