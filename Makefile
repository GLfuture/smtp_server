CC=g++
SRC=test.cc ./Base64/base64.cc
TARGET=smtp_server
$(TARGET):$(SRC)
	$(CC) $(SRC) -o $(TARGET)
clean:
	rm smtp_server