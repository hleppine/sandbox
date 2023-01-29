#!/bin/bash

set -euxo pipefail

docker build --tag dockerproject .
