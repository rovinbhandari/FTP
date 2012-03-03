CC = gcc
CFLAGS = -g -I./
SRCCLIENT = .
SRCSERVER = .
BIN = .
OBJCLIENT = obj
OBJSERVER = obj
OBJECTSCLIENT = ${OBJCLIENT}/commons.o ${OBJCLIENT}/client_ftp.o
OBJECTSSERVER = ${OBJSERVER}/commons.o ${OBJSERVER}/server_ftp_functions.o ${OBJSERVER}/server_ftp.o
EXECUTABLECLIENT = ${BIN}/client_ftp.out
EXECUTABLESERVER = ${BIN}/server_ftp.out

all:	client server

client:	${OBJECTSCLIENT}
	${CC} ${CFLAGS} $^ -o ${EXECUTABLECLIENT}

server:	${OBJECTSSERVER}
	${CC} ${CFLAGS} $^ -o ${EXECUTABLESERVER}

${OBJCLIENT}/%.o:	${SRCCLIENT}/%.c
	${CC} ${CFLAGS} -c $< -o $@

${OBJSERVER}/%.o:	${SRCSERVER}/%.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${OBJCLIENT}/*.o
	rm -f ${OBJSERVER}/*.o
	rm -f ${BIN}/*.out
