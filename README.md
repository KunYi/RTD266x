# RTD266x LCD Driver Board Development Resources

This repository is a curated collection of development resources for Realtek's RTD266x series LCD driver boards. These boards are commonly used in low-cost HDMI/VGA/LCD controller applications.

## 📁 Project Structure

```bash
.
├── docs
│   ├── datasheet       # Official datasheets for RTD266x series
│   ├── ref. design     # Reference designs and schematics
│   └── spec            # Specifications
├── programmer
│   ├── *.c / *.h       # A minimal I2C-based programmer for RTD266x
│   └── CMakeLists.txt  # Build script for the programmer
├── sources
│   └── *.zip / *.7z    # Archived source codes
└── tools
    └── RTD2660 OSD Tool.7z  # OSD (On-Screen Display) configuration tool
```

## 🛠 Programmer

The programmer directory contains a simple I2C-based tool written in C for communicating with RTD266x series chips. It includes:

- CRC checksum utilities
- GFF (possibly graphics firmware format) support
- Basic NOR flash definitions
- Low-level I2C communication routines (need implement)
    - another programmer project [OpenDisplayController](https://github.com/Mcsiv/OpenDisplayController)

## 📚 Documentation

The docs/ folder includes:

- Datasheets: Official hardware and chip specifications
- Reference designs: Schematic examples for hardware integration
- Specifications: Technical details of the RTD266x platform

## 📦 Source Archives

The sources/ folder includes various firmware archives

## Disclaimer

All materials are provided for educational and research purposes. Please respect local laws and copyright regulations when using firmware or tools from third-party sources.
