# Benchmarker

A cross-platform embedded benchmarking application for ARM Cortex-M microcontrollers. This project provides performance testing capabilities across multiple development boards including STM32, Nordic nRF, and Renesas RA series microcontrollers.

## Supported Boards

- **STM32F411 Nucleo** (`nucleo-f411`)
- **STM32F3 Discovery** (`stm32f3discovery`) 
- **STM32U575 Nucleo** (`nucleo-u575`)
- **EK-RA6M5** (`ek-ra6m5`)
- **nRF52840 DK** (`nrf52840-dk`)
- **nRF54L15 DK** (`nrf54l15-dk`)

## Build Requirements

- Docker with dev container support
- CLion (recommended)
  or 
  Visual Studio Code with Dev Containers extension 
  or
  Terminal

## Build Instructions

### Using CLion (Recommended)

1. **Open the project in CLion:**
   ```bash
   # Clone the repository
   git clone <repository-url>
   cd Benchmarker
   
   # Open in CLion
   clion .
   ```

2. **Configure dev container integration:**
   - Go to `Settings` → `Build, Execution, Deployment` → `Docker`
   - Ensure Docker is configured and running
   - CLion will automatically detect the dev container configuration

3. **Select CMake preset:**
   - Open `Settings` → `Build, Execution, Deployment` → `CMake`
   - Click the `+` button to add a new profile
   - Choose `Load CMake Presets` and select your target board preset (e.g., `RelWithDebInfo-F411`)
   - CLion will automatically configure the toolchain and build settings

4. **Build the project:**
   - Select your target configuration from the run/debug configuration dropdown
   - Click `Build` → `Build Project` or use `Ctrl+F9`
   - Alternatively, use the build button in the toolbar

5. **Alternative manual configuration:**
   If presets don't work automatically, configure manually:
   - Go to `Settings` → `Build, Execution, Deployment` → `CMake`
   - Set `Build type` to `RelWithDebInfo`
   - Add to `CMake options`: `-DCMAKE_TOOLCHAIN_FILE=gcc-arm-none-eabi.cmake`
   - Set `Environment variables`: `TARGET_BOARD=nucleo-f411` (or your target board)

### Using in VSCode Dev Container

1. **Open the project in a dev container:**
   ```bash
   # Clone the repository
   git clone <repository-url>
   cd Benchmarker
   
   # Open in VS Code
   code .
   ```
   
2. **When prompted, reopen in container or use Command Palette:**
   - `Ctrl+Shift+P` → "Dev Containers: Reopen in Container"

3. **Build the project:**
   ```bash
   # Configure for your target board (example: STM32F411)
   cmake -S . --preset RelWithDebInfo-F411
   
   # Build the project
   cmake --build --target Benchmarker --preset RelWithDebInfo-F411
   ```

### Available Build Presets

The project uses CMake presets for different board configurations. Available presets can be found in `CMakePresets.json`:

| Board | Debug Preset | Release Preset |
|-------|-------------|----------------|
| STM32F411 Nucleo | `Debug-F411` | `RelWithDebInfo-F411` |
| STM32F3 Discovery | `Debug-Discovery` | `RelWithDebInfo-Discovery` |
| STM32U575 Nucleo | - | `RelWithDebInfo-U575` |
| EK-RA6M5 | - | `RelWithDebInfo-RA6M5` |
| nRF52840 DK | - | `RelWithDebInfo-nRF52840` |
| nRF54L15 DK | - | `RelWithDebInfo-nRF54L15` |

### Build Examples

```bash
# For STM32F3 Discovery (Debug)
cmake -S . --preset Debug-Discovery
cmake --build --target Benchmarker --preset Debug-Discovery

# For STM32U575 Nucleo (Release with Debug Info)
cmake -S . --preset RelWithDebInfo-U575
cmake --build --target Benchmarker --preset RelWithDebInfo-U575

# For Nordic nRF52840
cmake -S . --preset RelWithDebInfo-nRF52840
cmake --build --target Benchmarker --preset RelWithDebInfo-nRF52840
```

## Build Artifacts

Build artifacts are generated in the following directory structure:
```
build/<board_name>-<preset_name>/
```

Examples:
- `build/nucleo-f411-RelWithDebInfo-F411/`
- `build/stm32f3discovery-Debug-Discovery/`
- `build/nrf52840-dk-RelWithDebInfo-nRF52840/`

## Project Structure

- **`src/`** - Source code including board-specific implementations
- **`src/boards/`** - Board support packages for each target platform
- **`.devcontainer/`** - Dev container configuration
- **`docker/`** - Docker build files
- **`CMakePresets.json`** - CMake configuration presets
- **`gcc-arm-none-eabi.cmake`** - ARM GCC toolchain configuration

## Notes

- The build process is designed to work within the provided dev container environment
- While building from the host OS may be possible, it is not officially supported
- Each board has its own specific compiler flags and linker scripts configured in the respective `CMakeLists.txt` files in `src/boards/` subdirectories