# DMA-WarThunder-SDK

This repository contains an SDK for interacting with War Thunder using Direct Memory Access (DMA).

## Features and Functionality

*   **ImGui Integration:** [Dear ImGui](https://github.com/ocornut/imgui) for creating overlays and user interfaces.
*   **DMA Support:** Leverages the `vmm.dll`, `FTD3XX.dll`, and `leechcore.dll` libraries for direct memory access.

## Technology Stack

*   **C++:** Primary programming language.
*   **[Dear ImGui](https://github.com/ocornut/imgui):** GUI framework.
*   **VMMDLL, FTD3XX, LeechCore:** DMA libraries.

## Prerequisites

*   A development environment capable of compiling C++ code.
*   `vmm.dll`, `FTD3XX.dll`, and `leechcore.dll` libraries.

## Installation Instructions

1.  Clone the repository:
    ```
    git clone https://github.com/MHSPlay/DMA-WarThunder-SDK
    ```
2.  Ensure all required DLLs ([`vmm.dll`](https://github.com/ufrisk/MemProcFS), [`FTD3XX.dll`](https://ftdichip.com/drivers/d3xx-drivers/), [`leechcore.dll`](https://github.com/ufrisk/LeechCore)) are present in the execution directory.
3.  Compile the project using your preferred C++ compiler. The project uses standard Windows API and DirectX 11, so any compatible compiler should work (e.g., Visual Studio).
4.  Run the compiled executable.

## Contributing Guidelines

1.  Fork the repository.
2.  Create a new branch for your feature or bug fix.
3.  Implement your changes.
4.  Test your changes thoroughly.
5.  Submit a pull request with a clear description of your changes.

## License Information

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact/Support Information

For questions, support, or contributions, please contact MHSPlay through the GitHub repository.
