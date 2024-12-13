# Description

This repository contains the **Unified Node Access (UNA)** implementation of the **R4S8CR** driver.

# Dependencies

The driver relies on:

* An external `types.h` header file defining the **standard C types** of the targeted MCU.
* The **R4S8CR driver** provided in the [r4s8cr-driver](https://github.com/Ludovic-Lesur/r4s8cr-driver) repository.
* The **UNA library** provided in the [una-lib](https://github.com/Ludovic-Lesur/una-lib) repository.
* The **embedded utility functions** defined in the [embedded-utils](https://github.com/Ludovic-Lesur/embedded-utils) repository.

Here is the versions compatibility table:

| **una-r4s8cr** | **r4s8cr-driver** | **una-lib** | **embedded-utils** |
|:---:|:---:|:---:|:---:|
| [sw1.0](https://github.com/Ludovic-Lesur/una-r4s8cr/releases/tag/sw1.0) | >= [sw1.0](https://github.com/Ludovic-Lesur/r4s8cr-driver/releases/tag/sw1.0) | >= [sw1.0](https://github.com/Ludovic-Lesur/una-lib/releases/tag/sw1.0) | >= [sw6.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw6.0) |

# Compilation flags

| **Flag name** | **Value** | **Description** |
|:---:|:---:|:---:|
| `UNA_R4S8CR_DISABLE` | `defined` / `undefined` | Disable the UNA R4S8CR functions. |
