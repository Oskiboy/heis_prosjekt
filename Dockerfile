FROM oskiboy/heis_lab:latest
LABEL Author oskar.oestby@gmail.com

COPY . .
RUN make
