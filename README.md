# Araxys

An external game modification tool for **Assault Cube**, built as a learning project to explore the fundamentals of reverse engineering, memory manipulation, and overlay rendering on Windows.

---

## Disclaimer

> **This project is strictly for educational purposes only.**
>
> I do not encourage, condone, or support cheating in any video game. Using cheats in online/multiplayer games violates terms of service, ruins the experience for other players, and can result in permanent bans.
>
> This project was created solely to:
> - Learn the basics of **reverse engineering**
> - Understand how **external cheats** work at a technical level
> - Experiment with **Windows memory APIs** and **overlay rendering**
>
> **Assault Cube** was chosen because it is a well-known, open-source game frequently used in the game hacking community as a safe learning environment. The techniques explored here are purely academic.

---

## Features

| Feature | Description | Hotkey |
|---------|-------------|--------|
| **God Mode** | Sets health to maximum value | `A` |
| **Armor** | Sets armor to maximum value | `S` |
| **Infinite Ammo** | Unlimited ammunition | `D` |
| **Rapid Fire** | Removes shooting delay | `F` |
| **No Recoil** | Eliminates weapon recoil | `G` |
| **ESP** | Tracks player positions | `H` |

---

## Technical Stack

- **Language:** C++20
- **Build System:** Visual Studio 2022 (MSVC v143)
- **Graphics:** Direct3D 11
- **UI Framework:** [Dear ImGui](https://github.com/ocornut/imgui)
- **Platform:** Windows 10+

---

## Project Structure

```
AraxysAC/
├── araxys.sln              # Visual Studio solution
├── build/                  # Compiled output
│   └── araxys.exe
└── araxys/
    ├── extern/
    │   └── imgui/          # ImGui library
    └── src/
        ├── main.cpp        # Entry point
        ├── cheat/          # Cheat modules
        │   ├── esp.cpp
        │   ├── health.cpp
        │   ├── armor.cpp
        │   ├── bullet.cpp
        │   ├── fastShoot.cpp
        │   ├── noRecoil.cpp
        │   └── runCheat.cpp
        ├── utils/
        │   ├── memory.cpp  # Memory read/write operations
        │   └── offsets.h   # Game memory offsets
        ├── window/
        │   └── window.cpp  # D3D11 overlay window
        └── print/
            └── print.cpp   # Console output
```

---

## How It Works

### Memory Manipulation
Uses Windows APIs (`ReadProcessMemory`, `WriteProcessMemory`) to read and modify the game's memory space externally, without injecting code into the target process.

### Overlay Rendering
Creates a transparent, click-through window using Direct3D 11 and Dear ImGui that renders on top of the game, displaying ESP information and UI elements.

### Code Patching
The no-recoil feature demonstrates basic code patching by modifying assembly instructions in memory to bypass recoil calculations.

---

## Building

### Requirements
- Visual Studio 2022
- Windows SDK 10.0+
- DirectX 11 SDK

### Steps
1. Open `araxys.sln` in Visual Studio
2. Select configuration (Debug/Release) and platform (x86/x64)
3. Build solution (`Ctrl+Shift+B`)
4. Output will be in `build/araxys.exe`

---

## Learning Resources

If you're interested in learning more about the topics covered in this project:

- [Game Hacking Academy](https://gamehacking.academy/) - Free tutorials on game hacking
- [Guided Hacking](https://guidedhacking.com/) - Community and tutorials
- [Cheat Engine](https://www.cheatengine.org/) - Memory scanning tool
- [x64dbg](https://x64dbg.com/) - Open-source debugger
- [Dear ImGui](https://github.com/ocornut/imgui) - UI library documentation

---

## License

This project is provided as-is for educational purposes. Use at your own risk and responsibility.

---

**Remember: Use your knowledge ethically. Understanding how systems work is valuable, but exploiting them to harm others is not.**
