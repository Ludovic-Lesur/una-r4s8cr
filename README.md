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
| [sw2.4](https://github.com/Ludovic-Lesur/una-r4s8cr/releases/tag/sw2.4) | >= [sw2.0](https://github.com/Ludovic-Lesur/r4s8cr-driver/releases/tag/sw2.0) | >= [sw2.1](https://github.com/Ludovic-Lesur/una-lib/releases/tag/sw2.1) | >= [sw7.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw7.0) |
| [sw2.3](https://github.com/Ludovic-Lesur/una-r4s8cr/releases/tag/sw2.3) | >= [sw2.0](https://github.com/Ludovic-Lesur/r4s8cr-driver/releases/tag/sw2.0) | >= [sw2.1](https://github.com/Ludovic-Lesur/una-lib/releases/tag/sw2.1) | >= [sw7.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw7.0) |
| [sw2.2](https://github.com/Ludovic-Lesur/una-r4s8cr/releases/tag/sw2.2) | >= [sw2.0](https://github.com/Ludovic-Lesur/r4s8cr-driver/releases/tag/sw2.0) | >= [sw2.1](https://github.com/Ludovic-Lesur/una-lib/releases/tag/sw2.1) | >= [sw7.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw7.0) |
| [sw2.1](https://github.com/Ludovic-Lesur/una-r4s8cr/releases/tag/sw2.1) | >= [sw2.0](https://github.com/Ludovic-Lesur/r4s8cr-driver/releases/tag/sw2.0) | >= [sw2.1](https://github.com/Ludovic-Lesur/una-lib/releases/tag/sw2.1) | >= [sw7.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw7.0) |
| [sw2.0](https://github.com/Ludovic-Lesur/una-r4s8cr/releases/tag/sw2.0) | >= [sw2.0](https://github.com/Ludovic-Lesur/r4s8cr-driver/releases/tag/sw2.0) | [sw2.0](https://github.com/Ludovic-Lesur/una-lib/releases/tag/sw2.0) | [sw6.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw6.0) to [sw6.2](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw6.2) |
| [sw1.0](https://github.com/Ludovic-Lesur/una-r4s8cr/releases/tag/sw1.0) | [sw1.0](https://github.com/Ludovic-Lesur/r4s8cr-driver/releases/tag/sw1.0) | [sw1.0](https://github.com/Ludovic-Lesur/una-lib/releases/tag/sw1.0) | [sw6.0](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw6.0) to [sw6.2](https://github.com/Ludovic-Lesur/embedded-utils/releases/tag/sw6.2) |

# Compilation flags

| **Flag name** | **Value** | **Description** |
|:---:|:---:|:---:|
| `UNA_R4S8CR_DISABLE_FLAGS_FILE` | `defined` / `undefined` | Disable the `una_r4s8cr_flags.h` header file inclusion when compilation flags are given in the project settings or by command line. |
| `UNA_R4S8CR_DISABLE` | `defined` / `undefined` | Disable the UNA R4S8CR functions. |
| `UNA_R4S8CR_NODE_ACCESS_RETRY_MAX` | `<value>` | Number of relay box access retries in case of failure. |
| `UNA_R4S8CR_USE_REGISTER_ACCESS` | `defined` / `undefined` | Enable register access definitions. |
| `UNA_R4S8CR_USE_REGISTER_ACCESS_TIMEOUT` | `defined` / `undefined` | Enable register access timeout definitions. |
| `UNA_R4S8CR_USE_REGISTER_ERROR_VALUE` | `defined` / `undefined` | Enable register error values definitions. |

# Build

A static library can be compiled by command line with `cmake`.

```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE="<toolchain_file_path>" \
      -DTOOLCHAIN_PATH="<arm-none-eabi-gcc_path>" \
      -DTYPES_PATH="<types_file_path>" \
      -DEMBEDDED_UTILS_PATH="<embedded-utils_path>" \
      -DUNA_LIB_PATH="<una-lib_path>" \
      -DR4S8CR_DRIVER_PATH="<r4s8cr-driver_path>" \
      -DR4S8CR_DRIVER_DELAY_ERROR_BASE_LAST=0 \
      -DR4S8CR_DRIVER_RS485_ERROR_BASE_LAST=0 \
      -DUNA_R4S8CR_NODE_ACCESS_RETRY_MAX=3 \
      -DUNA_R4S8CR_USE_REGISTER_ACCESS=ON \
      -DUNA_R4S8CR_USE_REGISTER_ACCESS_TIMEOUT=ON \
      -DUNA_R4S8CR_USE_REGISTER_ERROR_VALUE=ON \
      -G "Unix Makefiles" ..
make all
```
