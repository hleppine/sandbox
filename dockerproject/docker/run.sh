#!/bin/bash

set -euo pipefail

CURRENT_DIR="$(realpath .)"
BASE_DIR="$(realpath "$(dirname "$0")/..")"
WORK_DIR="$(realpath --relative-to "$BASE_DIR" "$CURRENT_DIR")"

mkdir -p "$BASE_DIR/docker/home"

# TODO fix workdir below

docker run \
    --rm \
    --init \
    --net host \
    --tty \
    --interactive \
    --user "$(id -u):$(id -g)" \
    --volume "${CURRENT_DIR}/home:/home/user" \
    --volume "$BASE_DIR:/src" \
    --workdir "/src/$(realpath --relative-to "${BASE_DIR}" "$(realpath .)")" \
    --ipc host \
    --env DISPLAY \
    --volume /tmp/.X11-unix:/tmp/.X11-unix \
    --volume ~/.Xauthority:/home/user/.Xauthority \
    dockerproject-image \
    "$@"
