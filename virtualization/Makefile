# -*- MakeFile -*-

cpu: cpu.c common.h
	gcc -o cpu cpu.c -Wall
	@strip --strip-unneeded cpu

cpu.run:
	./cpu "A" & ./cpu " B" & ./cpu "  C" &

cpu.stop:
	killall ./cpu

clean:
	rm cpu
