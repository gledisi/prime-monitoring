FROM gcc:latest
RUN apt-get update && apt-get -y install build-essential iproute2

COPY . /prime/

WORKDIR /prime/src
RUN make prime

WORKDIR /prime/bin

CMD ./prime -i $SERVER_NUM -d $MICROSECONDS $STEP -a $PP_TYPE $DELAY
