!ifdef __UNIX__
dosobj = src/dos/main.obj src/dos/gfx.obj src/dos/timer.obj src/dos/watdpmi.obj &
		 src/dos/vbe.obj src/dos/vga.obj src/dos/keyb.obj src/dos/mouse.obj &
		 src/dos/logger.obj
gameobj = src/game.obj src/util.obj
incpath = -Isrc -Isrc/dos -Ilibs/imago/src
libpath = libpath libs/imago
RM = rm -f
!else
dosobj = src\dos\main.obj src\dos\gfx.obj src\dos\timer.obj src\dos\watdpmi.obj &
		 src\dos\vbe.obj src\dos\vga.obj src\dos\keyb.obj src\dos\mouse.obj &
		 src\dos\logger.obj
gameobj = src\game.obj src\util.obj
incpath = -Isrc -Isrc\dos -Ilibs\imago\src
libpath = libpath libs\imago
RM = del
!endif

obj = $(dosobj) $(gameobj)
bin = game.exe

CC = wcc386
LD = wlink
CFLAGS = -d3 -5 -fp5 -otebmileran -s -zq -bt=dos $(incpath)
LDFLAGS = option map $(libpath)
# library { $(libs) }

$(bin): $(obj)
	%write objects.lnk $(obj)
	$(LD) debug all name $@ system dos4g file { @objects } $(LDFLAGS)

.c: src;src/dos
.asm: src;src/dos

.c.obj: .autodepend
	$(CC) -fo=$@ $(CFLAGS) $[*

.asm.obj:
	nasm -f obj -o $@ $[*.asm

clean: .symbolic
	$(RM) src\*.obj
	$(RM) src\dos\*.obj
	$(RM) objects.lnk
	$(RM) $(bin)
