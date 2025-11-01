# keyrate
Small utility for setting the keyrate to higher speeds than is normally allowed by the Windows keyboard control panel

inspired by https://github.com/EricTetz/keyrate

additions :
- registry entries for persistence of common value
- icon in system tray

## Project Structure

- **main.cpp**: Minimal entry point with application initialization
- **config.hpp/cpp**: Registry-based configuration management
- **keyrate.hpp/cpp**: Windows FilterKeys API for keyboard rate control
- **tray_icon.hpp/cpp**: System tray icon and context menu
- **dialog.hpp/cpp**: Configuration dialog UI
- **window.hpp/cpp**: Main window procedure and event handling
