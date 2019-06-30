APP_VERSION:=1.00

#DEBUG_MODE:=ENABLED
LDPATH := ./lib

APP_BASE_NAME:=service_queue


ifeq ($(DEBUG_MODE),ENABLED)
APP_NAME:=$(APP_BASE_NAME)$(APP_VERSION)_debug
else
APP_NAME:=$(APP_BASE_NAME)$(APP_VERSION)
endif

CC := gcc 

ifeq ($(DEBUG_MODE),ENABLED)
DEBUG := -Wall \
		 -std=gnu99 \
		 -g \
		 -ggdb3 \
		 -fsanitize=leak
else
DEBUG := -Wall \
		 -std=gnu99 
endif

CFLAGS := -I include 

LDFLAGS := 	   -L ./lib \
			   -lrt \
		       -lpthread 

SRCDIR  := src

OBJDIR  := obj

OBJS =  $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.c))


TARGETDIR = Release


TARGET = $(APP_NAME)

ifdef DEBUG_MODE
OUT_MESSAGE:= APP has been compiled with DEBUG_MODE .File name = $(APP_NAME)
else
OUT_MESSAGE:= APP has been compiled. File name = $(APP_NAME)
endif

all: $(TARGET) $(OBJS)

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo $(OUT_MESSAGE)

$(OBJDIR)/%.o:$(SRCDIR)/%.c	
	$(CC) -c $(DEBUG) $(CFLAGS) -o $@ $<


$(OBJS): |$(OBJDIR)
$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f obj/*
	rm -f $(APP_BASE_NAME)*



