FROM gcc:latest

COPY . /prime/

WORKDIR /prime/src
RUN make

WORKDIR /prime/bin
RUN ./gen_keys

CMD ./prime -i $SERVER_NUM
