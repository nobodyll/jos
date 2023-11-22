layout split
#wh asm 
focus cmd

add-symbol-file obj/user/breakpoint

#b *libmain
b *umain
c
