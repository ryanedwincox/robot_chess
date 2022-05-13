#!/bin/bash

export DOCKER_BUILDKIT=1

export XAUTH=/tmp/.docker.xauth
xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -

docker-compose build
docker-compose up