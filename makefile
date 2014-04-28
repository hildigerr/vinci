OBJS = vinci_global.o vinci_set.o \
       vinci_screen.o vinci_file.o vinci_memory.o \
       vinci_computation.o vinci_volume.o vinci_lass.o
OPT  = -O3 -Wall -ansi -pedantic
CC   = gcc
      

vinci : $(OBJS) vinci.o
	$(CC) vinci.o $(OBJS) -lm $(OPT) -o vinci

vinci.o : vinci.h vinci.c
	$(CC) vinci.c -c $(OPT)
	  
vinci_global.o : vinci.h vinci_global.c
	$(CC) vinci_global.c -c $(OPT)

vinci_set.o : vinci.h vinci_set.c
	$(CC) vinci_set.c -c $(OPT)

vinci_screen.o : vinci.h vinci_screen.c
	$(CC) vinci_screen.c -c $(OPT)

vinci_file.o : vinci.h vinci_file.c
	$(CC) vinci_file.c -c $(OPT)
	
vinci_memory.o : vinci.h vinci_memory.c
	$(CC) vinci_memory.c -c $(OPT)

vinci_computation.o : vinci.h vinci_computation.c
	$(CC) vinci_computation.c -c $(OPT)

vinci_volume.o : vinci.h vinci_volume.c
	$(CC) vinci_volume.c -c $(OPT)

vinci_lass.o : vinci.h vinci_lass.c
	$(CC) vinci_lass.c -c $(OPT)
	
clean :
	rm *.o


#with_matlab:
#	mex v_vol.c vinci_global.c vinci_memory.c vinci_set.c vinci_lass.c vinci_file.c