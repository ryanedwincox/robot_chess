#!/bin/bash

rm -rf perception/test_output
mkdir -p perception/test_output

export PROJECT_DIR=$PWD
export DOCKER_BUILDKIT=1

docker-compose -f docker-compose-tests.yml build
docker-compose -f docker-compose-tests.yml up