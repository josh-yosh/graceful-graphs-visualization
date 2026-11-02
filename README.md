# graceful-graphs-visualization

The C++ implementation lives in `cpp/`, including its source files, CMake
presets, and vcpkg manifest. A Rust implementation can be added alongside it
in `rust/`.

Run CMake commands from `cpp/`. For example, on Apple Silicon with `VCPKG_ROOT`
set:

```sh
cd cpp
cmake --preset macos-arm
cmake --build --preset macos-arm-debug
```

Build output is generated in `cpp/build/`. Any existing root-level `build/`
and `vcpkg_installed/` directories are artifacts from the previous layout.
