# RES=C:\raylib\raylib\src\raylib.rc.data
MINGW_INCLUDE=C:\raylib\w64devkit\x86_64-w64-mingw32\include
MINGW_LIB=C:\raylib\w64devkit\x86_64-w64-mingw32\lib
GLFW_INCLUDE=C:\ProgramData\chocolatey\lib\glfw3\tools\glfw-3.0.4.bin.WIN64\include
GLFW_LIB=C:\ProgramData\chocolatey\lib\glfw3\tools\glfw-3.0.4.bin.WIN64\lib-mingw
RAYLIB_SRC=C:\raylib\raylib\src
FLAGS=-std=c99 -Wall 
# LIBS=-lraylib -lgdi32 -lwinmm -lopengl32
GLEW_INCLUDE=c:\raylib\glew-2.1.0-win32\glew-2.1.0\include
GLEW_LIB=C:\raylib\glew-2.1.0-win32\glew-2.1.0\lib\Release\x64
LIBS=-lraylib -lglew32s -lglfw3 -lwinmm -lgdi32 -lopengl32

main: compile
	.\main.exe

compile: main.c
	gcc -o main.exe main.c $(RES) \
	-I.  \
	-I$(RAYLIB_SRC)  \
	-I$(MINGW_INCLUDE)  \
	-I$(GLFW_INCLUDE)  \
	-I$(GLEW_INCLUDE)  \
	-L$(GLEW_LIB)  \
	-L$(GLFW_LIB)  \
	-L$(RAYLIB_SRC) $(FLAGS) $(LIBS) 

clean:
	rm main.exe
