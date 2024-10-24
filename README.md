# Kernel Hello World Module with Sysfs Attributes

## Overview

This project implements a simple Linux kernel module (KMM) named `kmt`, which demonstrates the use of sysfs attributes for interacting with kernel modules. The module provides several attributes that can be read from and written to via the sysfs filesystem, allowing users to interact with the kernel module directly.

## Features

- **Sysfs Attributes**: The module exposes four attributes:
  - `status`: Indicates the current status of the module (active/inactive).
  - `message`: A customizable message that can be set by the user.
  - `version`: Displays the version of the module.
  - `mode`: Allows setting and retrieving the operational mode of the module.

- **Dynamic Message Handling**: Users can dynamically change the message displayed by the module through the sysfs interface.

- **Easy Integration**: The module can be built and integrated easily into a Linux kernel environment.

## Requirements

- Linux kernel headers matching your running kernel version.
- Build tools such as `make` and `gcc`.

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/kernel-module-sysfs.git
   cd kernel-module-sysfs
   ```

2. **Build the module**:
   ```bash
   make
   ```

3. **Load the module**:
   ```bash
   sudo insmod kmt.ko
   ```

4. **Verify the module is loaded**:
   ```bash
   dmesg | tail -n 10
   ```

5. **Interact with sysfs attributes**:
   - Check the status:
     ```bash
     cat /sys/class/driver/hello_world_driver/status
     ```
   - Set a message:
     ```bash
     echo "Hello, World!" > /sys/class/driver/hello_world_driver/message
     ```
   - Check the message:
     ```bash
     cat /sys/class/driver/hello_world_driver/message
     ```
   - Check the version:
     ```bash
     cat /sys/class/driver/hello_world_driver/version
     ```
   - Set the mode:
     ```bash
     echo "custom_mode" > /sys/class/driver/hello_world_driver/mode
     ```
   - Check the mode:
     ```bash
     cat /sys/class/driver/hello_world_driver/mode
     ```

6. **Remove the module**:
   ```bash
   sudo rmmod kmt
   ```

## Cleanup

To remove the compiled module and associated files, run:
```bash
make clean
```

## Usage

This kernel module can be used for educational purposes to demonstrate the interaction between user space and kernel space through sysfs. It can also be extended to include more complex behaviors and additional attributes.


## License

This project is licensed under the GNU General Public License v2.0 - see the [LICENSE](LICENSE) file for details.


