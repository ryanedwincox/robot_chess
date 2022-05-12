FROM matimoreyra/opencv

COPY src src
COPY CMakeLists.txt .
WORKDIR /build
RUN cmake ..
RUN make

ENTRYPOINT [ "/build/./perception" ]