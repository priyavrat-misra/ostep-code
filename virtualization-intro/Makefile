# -*- MakeFile -*-

mem: mem.c common.h
	gcc -o mem mem.c -Wall
	@strip --strip-unneeded mem

mem.run:
	@echo 0 | sudo tee /proc/sys/kernel/randomize_va_space  # disable ASLR
	./mem & ./mem & ./mem &

mem.stop:
	killall ./mem
	@echo 2 | sudo tee /proc/sys/kernel/randomize_va_space  # enable ASLR

cpu: cpu.c common.h
	gcc -o cpu cpu.c -Wall
	@strip --strip-unneeded cpu

cpu.run:
	./cpu "A" & ./cpu " B" & ./cpu "  C" &

cpu.stop:
	killall ./cpu

clean:
	rm cpu mem
