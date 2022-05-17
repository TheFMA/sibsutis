CPPFLAGS = -MP -MMD

INCLUDE = -I src/interface -I src/memory -I src/keyboard -I src/hdd -I src/cpu -I src/loading
LIBS_INCLUDE = -L $(LIBS_PATH) -l memory -l interface -l keyboard -l hdd -l cpu -l loading

BIN_PATH = bin
LIBS_PATH = obj/libs

OBJ_PATH = obj/src
OBJ_MEMORY_PATH = $(OBJ_PATH)/memory
OBJ_INTERFACE_PATH = $(OBJ_PATH)/interface
OBJ_KEYBOARD_PATH = $(OBJ_PATH)/keyboard
OBJ_HDD_PATH = $(OBJ_PATH)/hdd
OBJ_CPU_PATH = $(OBJ_PATH)/cpu
OBJ_LOADING_PATH = $(OBJ_PATH)/loading

SRC_PATH = src
MEMORY_PATH = $(SRC_PATH)/memory
INTERFACE_PATH = $(SRC_PATH)/interface
KEYBOARD_PATH = $(SRC_PATH)/keyboard
HDD_PATH = $(SRC_PATH)/hdd
CPU_PATH = $(SRC_PATH)/cpu
LOADING_PATH = $(SRC_PATH)/loading

bin/main.exe: $(OBJ_PATH)/main.o
	g++ -o $(BIN_PATH)/main.exe $(OBJ_PATH)/main.o $(LIBS_INCLUDE)

obj/src/main.o: $(SRC_PATH)/main.cpp $(LIBS_PATH)/libmemory.a $(LIBS_PATH)/libinterface.a $(LIBS_PATH)/libkeyboard.a $(LIBS_PATH)/libhdd.a $(LIBS_PATH)/libcpu.a $(LIBS_PATH)/libloading.a
	g++ $(CPPFLAGS) -c -o $(OBJ_PATH)/main.o $(SRC_PATH)/main.cpp $(INCLUDE) $(LIBS_INCLUDE)

obj/src/memory/memory.o: $(MEMORY_PATH)/memory.cpp
	g++ -c -o $(OBJ_MEMORY_PATH)/memory.o $(MEMORY_PATH)/memory.cpp $(INCLUDE)

obj/libs/libmemory.a: $(OBJ_MEMORY_PATH)/memory.o
	ar rcs $(LIBS_PATH)/libmemory.a $(OBJ_MEMORY_PATH)/memory.o

obj/src/interface/structs.o: $(INTERFACE_PATH)/structs.cpp
	g++ $(CPPFLAGS) -c -o $(OBJ_INTERFACE_PATH)/structs.o $(INTERFACE_PATH)/structs.cpp $(INCLUDE)

obj/src/interface/console.o: $(INTERFACE_PATH)/console.cpp
	g++ $(CPPFLAGS) -c -o $(OBJ_INTERFACE_PATH)/console.o $(INTERFACE_PATH)/console.cpp $(INCLUDE)

obj/src/interface/interface.o: $(INTERFACE_PATH)/interface.cpp
	g++ $(CPPFLAGS) -c -o $(OBJ_INTERFACE_PATH)/interface.o $(INTERFACE_PATH)/interface.cpp $(INCLUDE)

obj/libs/libinterface.a: $(OBJ_INTERFACE_PATH)/structs.o $(OBJ_INTERFACE_PATH)/interface.o $(OBJ_INTERFACE_PATH)/console.o
	ar rcs $(LIBS_PATH)/libinterface.a $(OBJ_INTERFACE_PATH)/console.o $(OBJ_INTERFACE_PATH)/structs.o $(OBJ_INTERFACE_PATH)/interface.o

obj/src/keyboard/keyboard.o: $(KEYBOARD_PATH)/keyboard.cpp
	g++ -c -o $(OBJ_KEYBOARD_PATH)/keyboard.o $(KEYBOARD_PATH)/keyboard.cpp $(INCLUDE)

obj/libs/libkeyboard.a: $(OBJ_KEYBOARD_PATH)/keyboard.o
	ar rcs $(LIBS_PATH)/libkeyboard.a $(OBJ_KEYBOARD_PATH)/keyboard.o

obj/src/hdd/hdd.o: $(HDD_PATH)/hdd.cpp
	g++ -c -o $(OBJ_HDD_PATH)/hdd.o $(HDD_PATH)/hdd.cpp $(INCLUDE)

obj/libs/libhdd.a: $(OBJ_HDD_PATH)/hdd.o
	ar rcs $(LIBS_PATH)/libhdd.a $(OBJ_HDD_PATH)/hdd.o

obj/src/cpu/cpu.o: $(CPU_PATH)/cpu.cpp
	g++ -c -o $(OBJ_CPU_PATH)/cpu.o $(CPU_PATH)/cpu.cpp $(INCLUDE)

obj/libs/libcpu.a: $(OBJ_CPU_PATH)/cpu.o
	ar rcs $(LIBS_PATH)/libcpu.a $(OBJ_CPU_PATH)/cpu.o


obj/src/loading/loading.o: $(LOADING_PATH)/loading.cpp
	g++ -c -o $(OBJ_LOADING_PATH)/loading.o $(LOADING_PATH)/loading.cpp $(INCLUDE)

obj/libs/libloading.a: $(OBJ_LOADING_PATH)/loading.o
	ar rcs $(LIBS_PATH)/libloading.a $(OBJ_LOADING_PATH)/loading.o

clean:
	rm -f obj/src/*.o obj/src/*.d obj/src/**/*.o obj/src/**/*.d obj/libs/*.a bin/main.exe

run:
	cd bin && ./main.exe -noload
