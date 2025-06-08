# AdvancedCMakeTitanEngineExample

This repository contains an example of building a cross-platform application with the **Titan (Esenthel) Engine** using modern CMake.  It accompanies the [blog post](https://medium.com/@drew.gilpin/advanced-esenthel-titan-engine-cmake-ddb85cb3803a) and can be built on both Windows and Linux.
The project now builds two executables: a **client** sample and a **server** that hosts the ENet network (reliable UDP). It also includes unit tests using the Google Test framework, and a GitHub Actions workflow for building and testing on every push. The latest binary release is built with every push to master, which can be downloaded and ran without any installation. spdlog is included just as an additional example of using a third party library with CMake.

It is recommended to use CLion 2025.1.2+. This project was built ~80% by ChatGPT Codex.

## Preparing the engine files

The large engine assets and libraries are stored in the repository as zip archives.  If the extracted files are missing, CMake will unpack them automatically during configuration:

```
assets/Engine.zip            -> assets/Engine.pak
third_party/EE/Engine.zip               -> third_party/EE/Engine.a                (Linux library)
third_party/EE/Engine64DX11.zip         -> third_party/EE/Engine64DX11.lib        (Windows library)
third_party/EE/EngineDebug64DX11.zip    -> third_party/EE/EngineDebug64DX11.lib   (Windows debug library)
third_party/EE/EngineDebug64DX11_pdb.zip-> third_party/EE/EngineDebug64DX11.pdb   (optional debug symbols)
```

The configure step automatically unpacks these archives when the extracted
files are missing, so you normally don't need to run any manual commands.

## Building

CMake presets are provided for both platforms. Example commands:

```bash
cmake --preset linux-release   # or windows-release
cmake --build out/build/<preset>
ctest --preset linux-test      # run unit tests
```

Both a client and server executable are produced.  Their binaries will appear in:

`out/build/<preset>/apps/client/` and `out/build/<preset>/apps/server/`

The required *.pak files will appear in:

`out/build/<preset>/apps/client/Bin` and `out/build/<preset>/apps/server/Bin`

## Running

1. Launch the server executable from its directory.
2. Then run the client executable which connects to the server on `127.0.0.1:12345`.
   The client will connect both apps will display simple metrics, use the arrow keys to move the dot, which will sync from client<->server.

NB The engine headers and binaries here are subject to Esenthel / Titan Engine's license:
### License
See the [LICENSE](LICENSE) file for the full Titan Engine license text.
