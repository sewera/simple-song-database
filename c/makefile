all: clean projekt

clean-build: clean-all projekt

functions.o:
	@echo "[I] Build started (functions.c)"
	gcc -c functions.c -o functions.o
	@echo "[S] Build succeeded -> functions.o"

projekt: functions.o
	@echo "[I] Build started (projekt.c)"
	gcc projekt.c functions.o -o projekt
	@echo "[S] Build succeeded -> projekt"

clean:
	@rm -f projekt
	@echo "[I] <projekt> executable removed."

clean-all:
	@rm -f projekt functions.o
	@echo "[I] All executables removed."
