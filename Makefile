SRCS := ./src
BUILDS := ./build
OBJS := ./src/obj
CLIBS := -L/usr/local/lib -Wl,-rpath,/usr/local/lib -Wl,--enable-new-dtags -lSDL2
INCLUDES := -D_REENTRANT -I/usr/local/include/SDL2

all: $(OBJS)/$(NAME).o
	gcc -o $(BUILDS)/out $(OBJS)/$(NAME).o $(CLIBS)

$(OBJS)/$(NAME).o: $(SRCS)/$(NAME).c
	gcc -c $(SRCS)/$(NAME).c -o $(OBJS)/$(NAME).o $(INCLUDES)

run:
	$(BUILDS)/out

prep:
	mkdir -p $(BUILDS)
	mkdir -p $(OBJS)