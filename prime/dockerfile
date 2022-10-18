FROM gcc:latest

COPY . /prime/

WORKDIR /prime/src
RUN make prime

WORKDIR /prime/bin

CMD ./prime -i $SERVER_NUM
