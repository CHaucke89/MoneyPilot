# MoneyPilot Agent Configuration

## Build Commands
- **Full build**: `scons`
- **Parallel build**: `scons -j$(nproc)`
- **Clean build**: `scons -c && scons`

## Test Commands
- **All tests**: `pytest`
- **Single test**: `pytest path/to/test_file.py::TestClass::test_method`
- **Specific module**: `pytest selfdrive/test/test_module.py`
- **Skip slow tests**: `pytest -m 'not slow'`
- **C++ tests**: `scons test` (builds and runs C++ test harness)

## Lint & Format
- **Lint Python**: `ruff check .`
- **Format Python**: `ruff format .`
- **Spell check**: `codespell`
- **Type check**: `mypy`

## Architecture Overview
MoneyPilot is a fork of sunnypilot/openpilot - an open-source ADAS system. Key components:
- **selfdrive/**: Core driving logic (controls, model inference, UI)
- **common/**: Shared utilities (filters, git helpers, constants)
- **system/**: System services (logging, camera, hardware abstraction)
- **cereal/**: Messaging serialization (Cap'n Proto schemas)
- **msgq/**: ZeroMQ-based inter-process communication
- **opendbc/**: Car interface definitions and CAN protocols
- **panda/**: Hardware security module interface
- **rednose/**: Kalman filtering and sensor fusion
- **tinygrad/**: Neural network inference (submodule)

## Code Style Guidelines
- **Indentation**: 2 spaces (Python), tabs (C++)
- **Line length**: 160 characters
- **Python imports**: Use absolute imports (`openpilot.common.*`), no relative imports
- **Naming**: snake_case for functions/variables, PascalCase for classes
- **Types**: Use type hints, validated with mypy
- **Error handling**: Use exceptions, log with swaglog
- **Linting**: ruff with custom rules (E, F, W, PIE, C4, ISC, A, B, NPY, UP, TRY203, TRY400, TRY401, RUF008, RUF100, TID251, PLR1704)
- **Banned APIs**: unittest (use pytest), time.time (use time.monotonic), various Qt/text helpers
