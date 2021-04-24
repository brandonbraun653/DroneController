#!/bin/bash
#------------------------------------------------------------------------------
# Protobuf Binding Generation
#   A quick and dirty script to get up and running with generated protobuf
#   bindings for C/Python. Expects to be using quadcopter Conda environment
#   from lib/Conda.
#------------------------------------------------------------------------------

# Root directory of the project
export PROJECT_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# NanoPB Directories
export NANOPB_ROOT_DIR="$PROJECT_ROOT_DIR/lib/nanopb"
export NANOPB_GEN_DIR="$NANOPB_ROOT_DIR/generator"
export NANOPB_PROTO_DIR="$NANOPB_GEN_DIR/proto"

# Proto files directory
#export PROTO_DIR="$PROJECT_ROOT_DIR/lib/VirtualDrone/src/VDrone/nanopb"

# Generate the C/H files. Must explicitly list relative proto path for some reason
echo "Generating C bindings"
#python "$NANOPB_GEN_DIR"/nanopb_generator.py lib/VirtualDrone/src/VDrone/nanopb/ahrs.proto

# Generate the python bindings
echo "Generating python bindings"
#protoc --proto_path="$NANOPB_GEN_DIR" --proto_path="$NANOPB_PROTO_DIR" --proto_path="$PROTO_DIR" --python_out="$PROTO_DIR" "$PROTO_DIR/ahrs.proto"

# Add the generated protobuf_pb2.py directory to the python environment
conda develop lib/nanopb/generator/proto