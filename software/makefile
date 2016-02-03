
PROG = reFlow powerCntl

CFLAGS = -Wall -g $(INCLUDE) 

INCLUDE = -I src/headers/ 

LIBS = -pthread -lwiringPi

CC = gcc

TARGETDIR = bin

SOURCES = CursorCntl.c reFlow.c thermostats.c

PSOURCES = PowerCntl.c

OBJS = $(addprefix $(TARGETDIR)/modules/,$(SOURCES:.c=.o))

POBJS = $(addprefix $(TARGETDIR)/modules/,$(PSOURCES:.c=.o))

LOGS_DIR = /var/PowerCntl

MK_DIR = mkdir -p


.PHONY: logs

vpath %.c ./src/modules

vpath %.c ./src/test

vpath %.h ./src/headers


all: $(TARGETDIR)/reFlow $(TARGETDIR)/powerCntl

$(TARGETDIR)/reFlow: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $@

$(TARGETDIR)/modules/%.o: %.c 
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

$(TARGETDIR)/powerCntl: $(POBJS) logs
	$(CC) $(CFLAGS) $(LIBS) $(POBJS) -o $@

logs: $(LOGS_DIR) 


$(LOGS_DIR):
	$(MK_DIR) $(LOGS_DIR)


clean:
	rm $(OBJS) bin/reFlow $(POBJS)