#!/bin/bash

set -euxo pipefail

SCRIPT_DIR="$(realpath "$(dirname "$0")")"
REPO_DIR="${SCRIPT_DIR}/../"
DEPS_DIR="${SCRIPT_DIR}/deps"

CPPCHECK_VERSION="2.10"

cd "${SCRIPT_DIR}"

mkdir -p "${DEPS_DIR}"

# Download dependencies if not present.
pushd "${DEPS_DIR}"
wget -nc -O "./cppcheck-${CPPCHECK_VERSION}.tar.gz" "https://github.com/danmar/cppcheck/archive/${CPPCHECK_VERSION}.tar.gz"
popd

# Build the docker image.
DOCKER_BUILDKIT=1 docker build --tag dockerproject-image .
