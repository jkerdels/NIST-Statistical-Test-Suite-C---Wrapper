# Object files directory
# Warning: This will be removed by make clean!
#
OBJDIR = obj
BINDIR = bin

# Target file name (without extension)
TARGET = $(BINDIR)/randomTest

# Define all c source files (dependencies are generated automatically)
#
SOURCES  = main.cpp
SOURCES += AbstractTest.cpp
SOURCES += ApproximateEntropyTest.cpp
SOURCES += BlockFrequencyTest.cpp
SOURCES += Cephes.cpp
SOURCES += CumulativeSumsTest.cpp
SOURCES += DiscreteFourierTransformTest.cpp
SOURCES += FrequencyTest.cpp
SOURCES += LinearComplexityTest.cpp
SOURCES += LongestRunOfOnesTest.cpp
SOURCES += Matrix.cpp
SOURCES += MaurersTest.cpp
SOURCES += NonOverlappingTemplateMatchingTest.cpp
SOURCES += OverlappingTemplateMatchingTest.cpp
SOURCES += RandomExcursionsTest.cpp
SOURCES += RandomExcursionVariantTest.cpp
SOURCES += RankTest.cpp
SOURCES += RunsTest.cpp
SOURCES += SerialTest.cpp
SOURCES += Tools.cpp
SOURCES += dfft.c

OBJECTS = $(addprefix $(OBJDIR)/,$(addsuffix .obj,$(basename $(SOURCES))))

# Compiler options
#
CFLAGS   = -Wall

# Linker Options
#
LDFLAGS  = -lm


# Define programs and commands
#
CC = gcc
CXX = g++


# Default target
#
all:  ccversion bin
bin:  $(TARGET)


# Create object files directory
#
$(shell mkdir -p $(OBJDIR) 2>/dev/null)
$(shell mkdir -p $(BINDIR) 2>/dev/null)


# Display compiler version information
#
ccversion: 
	@$(CC) --version


# Compile: create object files from C source files
#
$(OBJDIR)/%.obj : %.c
	@echo
	@echo Compiling C: $<
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJDIR)/%.obj : %.cpp
	@echo
	@echo Compiling C++: $<
	$(CXX) $(CFLAGS) -c $< -o $@ 

# Link: create IHX output file from object files
#
.SECONDARY: $(TARGET)
.PRECIOUS:  $(OBJECTS)
$(TARGET): $(OBJECTS)
	@echo
	@echo Linking: $@
	$(CXX) $(LDFLAGS) -o $(TARGET) $^
	#-o $@ 


# Clean project
#
clean:
	@echo Cleaning project:
	rm -rf $(OBJDIR)


# Listing of phony targets.
#
.PHONY: all ccversion bin clean
