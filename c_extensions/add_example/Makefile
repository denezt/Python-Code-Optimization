CC=gcc
CFLGS=-shared -o

all: setup build

info:
	@printf "\033[35m$(CC) compiler info:\033[0m\n"
	@$(CC) --verbose

setup:
	@./setup.sh

build:
	@echo "Building, project..."
	@gcc -fPIC -shared -o add.so add.c -I$(shell python3 -c "import sysconfig;print(sysconfig.get_paths()['include'])")
