BUILD_DIR = build
TOOLCHAIN = -DCMAKE_SYSTEM_NAME=Windows \
            -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
            -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++

all:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. $(TOOLCHAIN) && cmake --build .

run:
	wine /media/sf_linux/game_engine_dev/GED2D/bin/GameEngineDev.exe

clean:
	rm -rf $(BUILD_DIR)
