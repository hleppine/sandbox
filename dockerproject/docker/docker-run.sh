#!/bin/bash

set -euo pipefail

CURRENT_DIR="$(realpath .)"
BASE_DIR="$(realpath "$(dirname "$0")/..")"
WORK_DIR="$(realpath --relative-to "$BASE_DIR" "$CURRENT_DIR")"

mkdir -p "$BASE_DIR/docker/home"

# TODO Select which docker image to run.

# TODO graphical apps e.g. chromium browser

docker run \
    --rm \
    --init \
    --net host \
    --tty \
    --interactive \
    --user "$(id -u):$(id -g)" \
    --volume "${CURRENT_DIR}/home:/home/dockeruser" \
    --volume "$BASE_DIR:/src" \
    --workdir "/src/$(realpath --relative-to "${BASE_DIR}" "$(realpath .)")" \
    dockerproject \
    "$@"
