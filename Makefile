src_files := $(wildcard ./Simulation/src/*.c)

run: $(src_files)
	gcc -g -o scc-16.run $(src_files) -lm

clean:
	rm -f $(wildcard ./Simulation/obj/*.o) scc-16.run
