PROJNAME=Speed Compute
CC=gcc
CFLGS=-shared -o
SHAREDOBJ=speed_compute.so
PRGNAME=speed_compute.c

all: info setup cleanup build
	@printf "\033[32mBuild process is complete!\033[0m\n"

info:
	@printf "\033[36mProject: $(PROJNAME)\n"
	@printf "C Compiler: $(CC)\n"
	@printf "C Flags: $(CFLGS)\n"
	@printf "Shared Object: $(SHAREDOBJ)\n"
	@printf "Program Name: $(PRGNAME)\033[0m\n"
	@$(CC) --verbose


cleanup:
	@printf "\033[36mStarting, the clean-up process...\033[0m\n"
	@find . -type f -name $(SHAREDOBJ) -delete
	@printf "\033[32mClean-Up is done!\033[0m\n"

setup:
	@printf "Setting up, the $(PROJNAME) project...\033[0m\n"
	@./setup.sh
	@printf "\033[32mDone!\033[0m\n"

build:
	@echo "Building, project..."
	@gcc -fPIC -shared -o $(SHAREDOBJ) $(PRGNAME) -I$(shell python3 -c "import sysconfig;print(sysconfig.get_paths()['include'])")
