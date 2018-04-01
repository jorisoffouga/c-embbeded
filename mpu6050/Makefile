NAME=mpu6050
CFLAGS=-I /src
OBJ=${NAME}.o
LIB=periphery.a
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mpu6050: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIB)

.PHONY: clean 

clean:
	rm -f MPU6050 $(OBJ)
