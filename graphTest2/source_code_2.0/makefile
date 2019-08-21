# Filename of compiled application
EXECUTABLE = run_code
# All the .c filenames
SOURCES = $(wildcard *.c)
# All the .h filenames
DEPENDENCIES = $(wildcard *.h) 
INCLUDES = -I../linux-sama5d-armle-fbdev-GST01-obj/include/gre
# Replace the .c filenames to .o extension
OBJECTS = $(SOURCES:.c=.o) 

# The cross compiler used
CC = arm-linux-gnueabihf-gcc
# CC = gcc
# To avoid dependencies all needed libraries will be copied into the binary 
LDFLAGS += -static

# Load the library for using threads
SB_LIB += -pthread
#Load Lib of crank
SB_LIB +=  -lgreio
SB_LIB_PATH = -L../linux-sama5d-armle-fbdev-GST01-obj/lib
 

# To generate object files from .c files
CFLAGS += -c -g
# All warnings will be considered errors
CFLAGS += -Wall

# IP addres of the SAMA Xplained board
IP = 10.12.131.191
# User for SSH connection
USER = root
# Path in board where the app will copied
REMOTE_PATH = /home/root/sharif/source_code

CONFIG_TXT = config.txt

IP_UBUNTU = 172.17.44.79

##############################################################################

.PHONY : all clean deploy

all : $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(SB_LIB_PATH) $(LDFLAGS) -o $@ $^ $(SB_LIB)

%.o : %.c $(DEPENDENCIES) makefile
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

deploy:
	scp $(EXECUTABLE) $(USER)@$(IP):$(REMOTE_PATH)

cfg:
	scp $(CONFIG_TXT) $(USER)@$(IP):$(REMOTE_PATH)

##############################################################################
# Do not copy these set of two rules

inu:
	scp -r ../linux-sama5d-armle-fbdev-GST01-obj fer@(IP_UBUNTU):/home/fer/semestreI/
	scp *.c isaias@$(IP_UBUNTU):/home/isaias/semestreI/receiver/
	scp *.h isaias@$(IP_UBUNTU):/home/isaias/semestreI/receiver/
	scp makefile isaias@$(IP_UBUNTU):/home/isaias/semestreI/receiver/
	# ssh isaias@$(IP_UBUNTU) 'cd ~/semestreI/receiver;source /opt/poky-atmel/2.4.2/environment-setup-cortexa5hf-vfp-poky-linux-gnueabi;make'
	ssh isaias@$(IP_UBUNTU) 'cd ~/semestreI/receiver;make'
	scp isaias@$(IP_UBUNTU):/home/isaias/semestreI/receiver/receiver receiver
	scp $(EXECUTABLE) $(USER)@$(IP):$(REMOTE_PATH)
