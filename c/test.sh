#!/bin/bash

set -euxo pipefail

SCRIPT_DIR=(dirname "$0")
make -C "${SCRIPT_DIR}" all
