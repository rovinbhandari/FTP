CC = gcc
CFLAGS = -g -I./
SRCCLIENT = .
SRCSERVER = .
BIN = .
OBJCLIENT = obj
OBJSERVER = obj
OBJECTSCLIENT = ${OBJ}/commons_functions.o ${OBJ}/client_ftp.o
OBJECTSSERVER = ${OBJ}/commons_functions.o ${OBJ}/server_ftp_functions.o ${OBJ}/server_ftp.o
EXECUTABLECLIENT = ${BIN}/client_ftp.out
EXECUTABLESERVER = ${BIN}/server_ftp.out

all:	client server

client:	${OBJECTSCLIENT}
	${CC} ${CFLAGS} $^ -o ${EXECUTABLECLIENT}

server:	${OBJECTSSERVER}
	${CC} ${CFLAGS} $^ -o ${EXECUTABLESERVER}

${OBJ}/%.o:	${SRC}/%.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${OBJCLIENT}/*.o
	rm -f ${OBJSERVER}/*.o
	rm -f ${BIN}/*.out
