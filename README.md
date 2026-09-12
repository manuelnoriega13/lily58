flashing_guide_content = """# Lily58 Firmware Flashing & Configuration Guide

A comprehensive, step-by-step guide for flashing firmware and setting up keymaps on the **Lily58** split mechanical keyboard using **VIA** and **VIAL**.

---

## Table of Contents
1. [Crucial Safety Warning (TRRS Cable)](#1-crucial-safety-warning-trrs-cable)
2. [Prerequisites & Software Requirements](#2-prerequisites--software-requirements)
3. [Repository Files Overview](#3-repository-files-overview)
4. [How to Enter Bootloader Mode](#4-how-to-enter-bootloader-mode)
5. [Step-by-Step: Flashing with QMK Toolbox](#5-step-by-step-flashing-with-qmk-toolbox)
   - [Flashing the Master Half](#flashing-the-master-half)
   - [Flashing the Slave Half](#flashing-the-slave-half)
6. [Step-by-Step: Configuring via VIA](#6-step-by-step-configuring-via-via)
   - [Connecting to VIA](#connecting-to-via)
   - [Loading the Definition JSON File](#loading-the-definition-json-file)
   - [Remapping Keys and Layers](#remapping-keys-and-layers)
7. [Step-by-Step: Configuring via VIAL](#7-step-by-step-configuring-via-vial)
   - [Connecting to VIAL](#connecting-to-vial)
   - [Security Unlock Prompt](#security-unlock-prompt)
   - [Using Advanced Features (Tap Dance, Combos, Layers)](#using-advanced-features-tap-dance-combos-layers)
8. [Troubleshooting & FAQ](#8-troubleshooting--faq)

---

## 1. Crucial Safety Warning (TRRS Cable)

> **DANGER:** **NEVER plug or unplug the TRRS (3.5mm) cable while the keyboard is connected to USB power.**  
> Doing so can cause a temporary short circuit across the VCC, GND, and data pins, permanently damaging the microcontroller (Pro Micro / Elite-C) or OLED display modules.
>
> **Safe Procedure:**
> 1. Unplug the USB cable from your computer.
> 2. Connect the TRRS cable securely between the left and right halves.
> 3. Plug the USB cable back into the primary (master) half.

---

## 2. Prerequisites & Software Requirements

Before you begin, ensure you have downloaded and installed:

1. **QMK Toolbox:**
   - Download the latest release from [QMK Toolbox GitHub](https://github.com/qmk/qmk_toolbox/releases).
   - *Windows Users:* Make sure to install the drivers when prompted, or run `Tools > Install Drivers` inside QMK Toolbox.
2. **Web Browser (Chromium-based):**
   - Google Chrome, Brave, Chromium, or Microsoft Edge are required for WebHID support when using web configurators.
3. **Hardware Requirements:**
   - Lily58 keyboard fully assembled.
   - TRRS cable connecting both halves.
   - USB cable (USB-C or Micro-USB depending on your controller).

---

## 3. Repository Files Overview

```text
.
├── README.md
├── FLASHING_GUIDE.md
├── via/
│   ├── layout/
│   │   └── lily58_r2g.layout-via.json  # VIA layout definition file (for manual import)
│   └── lily58_via.hex                  # Firmware compiled with VIA support
└── vial/
    ├── layout/                         # Directory for custom exported Vial layouts
    └── lily58_rev1_vial.hex            # Firmware compiled with on-board VIAL support