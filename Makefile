CC       = gcc
WINDRES  = windres
OBJ      = main.o zpmer.o
LINKOBJ  = main.o zpmer.o
BIN      = ZPMer.exe
LIBS     = -L"libs/win/IUP/lib" -static-libgcc -mwindows -liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -g3 -mwindows
INCS     = -I"libs/win/IUP/include"
CFLAGS   = $(INCS) -Wall -g3 -mwindows -fexec-charset=gbk

.PHONY: all build-test test build clean

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)
zpmer.o: zpmer.c
	$(CC) -c zpmer.c -o zpmer.o $(CFLAGS)

build: clean $(BIN)

run: build
	$(BIN)


clean:
	-@rm "ZPMer.exe" "main.o" "zpmer.o"