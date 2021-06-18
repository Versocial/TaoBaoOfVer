Server = ./bin/Server.exe 
Client = ./bin/Client.exe
SRC_S = ./server/* ./src/*.cpp 
SRC_C = ./client/* ./src/*.cpp 
INC = ./include

ALL:$(Server) $(Client)

$(Server):$(SRC_S)
	clang++ $(SRC_S) -g -lws2_32 -o $(Server) -I $(INC)

$(Client):$(SRC_C)
	clang++ $(SRC_C) -g -lws2_32 -o $(Client) -I $(INC)

.PHONY:
clean:
	del ./bin/+