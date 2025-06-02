# BasicAppCmake

This repository contains a minimal example of building a small application with the **Titan (Esenthel) Engine** using modern CMake.  It accompanies the [blog post](https://medium.com/@drew.gilpin/esenthel-titan-engine-visual-studio-cmake-wsl-project-75da74e3d5b6) and can be built on both Windows and Linux.

## Preparing the engine files

The large engine assets and libraries are stored in the repository as zip archives.  Extract them **in place** before configuring the build:

```
assets/Engine.zip            -> assets/Engine.pak
third_party/EE/Engine.zip               -> third_party/EE/Engine.a                (Linux library)
third_party/EE/Engine64DX11.zip         -> third_party/EE/Engine64DX11.lib        (Windows library)
third_party/EE/EngineDebug64DX11.zip    -> third_party/EE/EngineDebug64DX11.lib   (Windows debug library)
third_party/EE/EngineDebug64DX11_pdb.zip-> third_party/EE/EngineDebug64DX11.pdb   (optional debug symbols)
```

## Building

CMake presets are provided for both platforms.  Example commands:

```bash
cmake --preset linux-release   # or windows-release
cmake --build out/build/<preset>
ctest --preset linux-test      # run unit tests
```

The built applications and required *.pak files will appear in
`out/build/<preset>/Bin`.  Two executables are produced:

- `client` – the interactive sample which draws a window and sends a test
  message using ENet
- `server` – a small console program which accepts the client's connection and
  prints any received packets.

NB The engine headers and binaries here are subject to Esenthel / Titan Engine's license:
### License
See the [LICENSE](LICENSE) file for the full Titan Engine license text.
