# Compiler To Use
CC := gcc


# Target Binary
TARGET := workersDB
READFILE := readfile

# Directories
SRCDIR := src
INCDIR := headers
OBJDIR := obj


# Compile Time Flags
CFLAGS := -Wall -Wextra -O2 -g

#Default Make targets
all: readfile $(TARGET) 

readfile: $(SRCDIR)/$(READFILE).c $(INCDIR)/$(READFILE).h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I ${INCDIR} -c -o $(OBJDIR)/$(READFILE).o $(SRCDIR)/$(READFILE).c 

$(TARGET): readfile $(SRCDIR)/$(TARGET).c 
	$(CC) $(CFLAGS) -I ${INCDIR} -c -o $(OBJDIR)/$(TARGET).o $(SRCDIR)/$(TARGET).c 
	$(CC) $(CFLAGS) $(OBJDIR)/$(READFILE).o $(OBJDIR)/$(TARGET).o -o $(TARGET) 

#Non-File Targets
.PHONY: clean 

#Clean only Objecst
clean:
	@$(RM) -rf $(TARGET) $(OBJDIR)
