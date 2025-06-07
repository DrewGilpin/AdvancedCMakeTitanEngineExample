# BasicAppCmake

This repository contains a minimal example of building a small application with the **Titan (Esenthel) Engine** using modern CMake.  It accompanies the [blog post](https://medium.com/@drew.gilpin/esenthel-titan-engine-visual-studio-cmake-wsl-project-75da74e3d5b6) and can be built on both Windows and Linux.
The project now builds two executables: a **client** sample and a **server** that hosts the ENet network.

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

CMake presets are provided for both platforms.  **The Linux presets use Clang,**
as the third-party Titan Engine headers rely on MSVC extensions not supported
by GCC.  Example commands:

```bash
cmake --preset linux-release   # or windows-release
cmake --build out/build/<preset>
ctest --preset linux-test      # run unit tests
```

Both a client and server executable are produced.  Their binaries and the required *.pak files will appear in
`out/build/<preset>/apps/client/Bin` and `out/build/<preset>/apps/server/Bin`.

## Running

1. Launch the server executable from its `Bin` directory.
2. Then run the client executable which connects to the server on `127.0.0.1:12345`.
   The client will send a single test packet and both apps will display simple metrics.

NB The engine headers and binaries here are subject to Esenthel / Titan Engine's license:
### License
See the [LICENSE](LICENSE) file for the full Titan Engine license text.
