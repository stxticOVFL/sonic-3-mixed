rwc = $(foreach d, $(wildcard $1*), $(call rwc,$d/,$2) $(filter $(subst *,%,$2),$d))

TARGET   = /Users/Justin/Dropbox/binj/client/makeheaders
STARTDIR = /Users/Justin/Sonic3Mixed/ImpostorEngine2/source
OBJS     = main.o

SRC_C   = $(call rwc, source/, *.c)
SRC_CPP = $(call rwc, source/, *.cpp)
SRC_WAV = $(call rwc, source/, *.wav)

OBJ_DIRS := $(sort \
			$(addprefix out/osx/, $(dir $(SRC_C:source/%.c=%.o))) \
			$(addprefix out/osx/, $(dir $(SRC_CPP:source/%.cpp=%.o))) )

OBJS     := $(addprefix out/osx/, $(SRC_C:source/%.c=%.o)) \
			$(addprefix out/osx/, $(SRC_CPP:source/%.cpp=%.o))

INCLUDES  =	-Wall -Wno-deprecated \
			-F/Library/Frameworks/ \
			-F/System/Library/Frameworks/ \
			-F/usr/local/include \
			-F/usr/local/lib \
			-Iinclude

LIBS	  =	-lz

LINKER	  =

DEFINES   =	-DMACOSX

all:
	@mkdir -p $(OBJ_DIRS)
	@make build
	@cp "$(TARGET)" /Users/Justin/Sonic3Mixed/ImpostorEngine2/tools/makeheaders
	@cp "$(TARGET)" /Users/Justin/Dropbox/STREAM/makeheaders
	# @cp "$(TARGET)" "/Users/Justin/Dropbox/StreamFrog Stream Pad/makeheaders"
	@"$(TARGET)" $(STARTDIR)

debug:
	@mkdir -p $(OBJ_DIRS)
	@make build
	cp "$(TARGET)" /Users/Justin/Sonic3Mixed/ImpostorEngine2/tools/makeheaders
	cp "$(TARGET)" /Users/Justin/Dropbox/STREAM/makeheaders
	# @cp "$(TARGET)" "/Users/Justin/Dropbox/StreamFrog Stream Pad/makeheaders"
	@lldb -f "$(TARGET)" $(STARTDIR)

clean:
	@@rm -r $(OBJS)
	@make build
	cp "$(TARGET)" /Users/Justin/Sonic3Mixed/ImpostorEngine2/tools/makeheaders
	cp "$(TARGET)" /Users/Justin/Dropbox/STREAM/makeheaders
	# @cp "$(TARGET)" "/Users/Justin/Dropbox/StreamFrog Stream Pad/makeheaders"
	@"$(TARGET)" $(STARTDIR)

build: $(OBJS)
	@g++ $^ $(INCLUDES) $(LIBS) $(LINKER) -o $(TARGET)

$(OBJ_DIRS):
	mkdir -p $@

out/osx/%.o: source/%.cpp
	@g++ -c -g $(INCLUDES) $(DEFINES) -o "$@" "$<" -std=c++11 -O3

out/osx/%.o: source/%.c
	@gcc -c -g $(INCLUDES) $(DEFINES) -o "$@" "$<" -O3
