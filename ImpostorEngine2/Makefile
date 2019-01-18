rwc = $(foreach d, $(wildcard $1*), $(call rwc,$d/,$2) $(filter $(subst *,%,$2),$d))

TARGET   = builds/osx/$(notdir $(CURDIR))
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
			-F/usr/local/include/ \
			-F/usr/local/lib \
			-I/Library/Frameworks/SDL2.framework/Headers/ \
			-I/Library/Frameworks/SDL2_image.framework/Headers/ \
			-I/Library/Frameworks/SDL2_mixer.framework/Headers/ \
			-I/Library/Frameworks/SDL2_ttf.framework/Headers/ \
			-I/System/Library/Frameworks/OpenGL.framework/Headers/ \
			-I/usr/local/include/ \
			-Igen \
			-Isource

LIBS	  =	-logg -lvorbis -lvorbisfile -lz -lminizip -ldiscord-rpc

LINKER	  =	-framework SDL2 \
			-framework SDL2_mixer \
			-framework OpenGL \
			-framework CoreFoundation \
			-framework CoreServices \
			-framework Foundation
			# \
			-framework Cocoa \
			#


DEFINES   =	-Ofast -DMACOSX -DUSING_FRAMEWORK -DOGG_MUSIC

all:
	@mkdir -p $(OBJ_DIRS)
	@./tools/makeheaders source
	@make build
	@./"$(TARGET)"

nogen:
	@mkdir -p $(OBJ_DIRS)
	@make build
	@./"$(TARGET)"

debug:
	@mkdir -p $(OBJ_DIRS)
	@./tools/makeheaders source
	@make build
	@lldb -o r -f "$(TARGET)"

clean:
	@@rm -r $(OBJS)
	@make all

cleannogen:
	@@rm -r $(OBJS)
	@make build
	@./"$(TARGET)"

commit:
	@mkdir -p $(OBJ_DIRS)
	@./tools/makeheaders source
	@make build
	@./"$(TARGET)"
	@git add ../ImpostorEngine2
	@git commit -m "$(message)"
	git push

build: $(OBJS)
	@g++ $^ $(INCLUDES) $(LIBS) $(LINKER) -o $(TARGET) -std=c++11

$(OBJ_DIRS):
	@mkdir -p $@

out/osx/%.o: source/%.cpp
	@g++ -c -g $(INCLUDES) $(DEFINES) -o "$@" "$<" -std=c++11

out/osx/%.o: source/%.c
	@gcc -c -g $(INCLUDES) $(DEFINES) -o "$@" "$<" -std=c11
