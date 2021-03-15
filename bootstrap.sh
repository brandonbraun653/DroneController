#!/bin/bash

#------------------------------------------------------------------------------
# Drone Controller Shell Bootstrap
#   This is expected to be executed before running commands that interact with
#   the project's build system or other tooling. There are a few aspects of the
#   system (code generators) that benefit from having environment variables to
#   determine paths OR need a virtual environment activated.
#
# VS Code Integration:
#   "terminal.integrated.shellArgs.linux": [ "--init-file", "bootstrap.sh" ]
#------------------------------------------------------------------------------
echo "Bootstrapping into DroneController environment"

# Pull the system level shell config
source ~/.bashrc

# Activate the python virtual environment for the project. Must have already
# created it from the Conda submodule.
conda activate quadcopter

# Root directory of the project
export PROJECT_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# NanoPB Directories
export NANOPB_ROOT_DIR="$PROJECT_ROOT_DIR/lib/nanopb"
export NANOPB_GEN_DIR="$NANOPB_ROOT_DIR/generator"
export NANOPB_PROTO_DIR="$NANOPB_GEN_DIR/proto"