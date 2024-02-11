# script for quickly running all presets and cleaning up after

all:
	g++ -D Penta_decathlon './src/main.cpp'; gnome-terminal --full-screen --zoom=2 --wait -- ./a.out || true
	g++ -D Gosper_glider_gun './src/main.cpp'; gnome-terminal --full-screen --zoom=0.40 --wait -- ./a.out || true
	g++ -D Puffer_type_breeder './src/main.cpp'; gnome-terminal --full-screen --zoom=0 --wait -- ./a.out || true
	rm ./a.out