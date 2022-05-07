
CC = gcc
SRC = src/**.c
CFLAGS = -std=gnu11 -g -Wall -pedantic -Wextra
# LDLIBS = -lSOMELIB
# LDFLAGS = -LINKER_FLAGS
EXE = sol
TST = src/unit_tests/runner.c
OUT = build
        
# Commands
build: $(SRC)
	@echo
	@echo 'Compiling program...'
	@$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -c
	@mv *.o $(OUT)/
	@echo 'Progam compiled! [$(OUT)/$(EXE).o]'
        
clean:
	rm -rf $(OUT)/*
        
static_lib: build
	@echo
	@echo 'Building library...'
	ar -cvq $(OUT)/lib$(EXE).a $(OUT)/*.o
	@echo '(Static) Library built! [$(OUT)/lib$(EXE).a]'
        
run: build $(OUT)/$(EXE)
	@echo
	@echo 'Running program...'
	@./$(OUT)/$(EXE)

test: $(TST)
	@echo
	@echo 'Running tests...'
	@$(CC) $(TST) $(SRC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(OUT)/unit_tests
	@./$(OUT)/unit_tests
