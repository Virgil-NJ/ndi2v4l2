# ndi2v4l2

**A lightweight NDI® to V4L2 virtual camera bridge for Linux. No OBS required.**

`ndi2v4l2` is an open-source Linux utility intended to receive video from an NDI source and expose it as a standard V4L2 camera device that applications such as Zoom, Discord, Teams, browsers, and other Linux software can use like a normal webcam.

The primary goal is simple:

```text
NDI Source
    |
    v
ndi2v4l2
    |
    v
V4L2 Virtual Camera
    |
    v
Zoom / Teams / Discord / Browser / Other Linux Applications
```

## Project Status

**Pre-alpha / early development**

This project is currently being designed and developed.

There is not yet a production-ready release.

The first development target is to successfully:

1. Discover an NDI source on the local network.
2. Connect to that source using the NDI SDK.
3. Receive decoded video frames.
4. Send those frames to a `v4l2loopback` virtual camera.
5. Make that camera available to normal Linux applications.

The initial development and testing platform is **Omarchy Linux**, an Arch Linux-based distribution, but the project is intended to eventually support other modern Linux distributions.

## Why This Project Exists

NDI provides tools on Windows and macOS that can expose NDI video sources to applications as camera inputs.

Linux does not currently have the same simple official NDI-to-webcam workflow.

Linux users can accomplish similar things with tools such as OBS Studio, GStreamer, FFmpeg, custom scripts, and virtual video devices, but those solutions can introduce additional complexity and resource usage.

`ndi2v4l2` is intended to provide a focused alternative.

Instead of:

```text
NDI
 |
 v
OBS
 |
 v
OBS Virtual Camera
 |
 v
Zoom
```

the goal is:

```text
NDI
 |
 v
ndi2v4l2
 |
 v
V4L2
 |
 v
Zoom
```

No scene compositor.

No streaming application running in the background.

No OBS requirement.

Just an NDI receiver feeding a Linux virtual camera.

## Goals

The project aims to provide:

* NDI source discovery
* NDI video reception
* Support for NDI HX sources where supported by the installed NDI runtime
* Direct output to V4L2
* Compatibility with `v4l2loopback`
* Low CPU and memory overhead
* Low latency
* Automatic source reconnection
* Clean command-line operation
* Useful diagnostics and error messages
* Support for common resolutions and frame rates
* Support for applications that recognize standard Linux V4L2 cameras
* No OBS dependency
* No requirement to run a full multimedia production environment

## Non-Goals

At least initially, `ndi2v4l2` is **not** intended to be:

* An OBS replacement
* A video editor
* A streaming studio
* A scene compositor
* An NDI transmitter
* A complete NDI management suite
* A replacement for the NDI SDK or runtime
* A custom Linux kernel camera driver

The project should do one job and do it well:

> Receive an NDI video source and expose it as a Linux V4L2 camera.

## Planned Architecture

The initial architecture is intentionally small:

```text
        Network
           |
           v
+---------------------+
|      NDI Source     |
| Camera / Phone / PC |
+---------------------+
           |
           | NDI
           v
+---------------------+
|     ndi2v4l2        |
|                     |
| NDI Discovery       |
| NDI Receiver        |
| Frame Handling      |
| V4L2 Output         |
+---------------------+
           |
           v
+---------------------+
|    v4l2loopback     |
|   /dev/videoX       |
+---------------------+
           |
           v
+---------------------+
| Zoom / Teams / etc. |
+---------------------+
```

The project should use the NDI SDK directly wherever practical rather than passing video through OBS or another large multimedia application.

Where possible, video should remain in a format that can be passed efficiently from the NDI receiver to V4L2 without unnecessary conversions.

## Planned CLI

The final command-line interface has not been finalized, but the intended usage is approximately:

### List available NDI sources

```bash
ndi2v4l2 --list
```

Example:

```text
Available NDI sources:

1. IPHONE 4D38 (HX Camera)
2. Studio Camera
3. Laptop NDI Output
```

### Connect an NDI source to a virtual camera

```bash
ndi2v4l2 --source "IPHONE 4D38 (HX Camera)"
```

Or specify the V4L2 device:

```bash
ndi2v4l2 \
  --source "IPHONE 4D38 (HX Camera)" \
  --device /dev/video10
```

Future options may include:

```bash
ndi2v4l2 \
  --source "IPHONE 4D38 (HX Camera)" \
  --device /dev/video10 \
  --resolution 1920x1080 \
  --fps 30
```

These commands describe the intended interface and are not yet guaranteed to work.

## Dependencies

The project is expected to require:

* Linux
* NDI SDK/runtime
* Video4Linux2
* `v4l2loopback`
* A C++ compiler
* CMake

Additional dependencies should be kept to a minimum.

One of the goals of this project is to avoid requiring OBS, FFmpeg, or GStreamer merely to move already-decoded video frames between NDI and V4L2 when they are not technically necessary.

Dependencies may change as development progresses.

## NDI Runtime

`ndi2v4l2` does not implement the NDI protocol itself.

The application is intended to use the official NDI SDK/runtime for:

* NDI source discovery
* NDI connection management
* Video reception
* NDI codec handling

The open-source project should not unnecessarily redistribute proprietary NDI runtime components.

The preferred architecture is to dynamically load the appropriate NDI runtime installed on the user's system.

## V4L2 Virtual Camera

Linux applications generally access webcams through Video4Linux2.

`v4l2loopback` provides virtual V4L2 video devices. Applications can read those virtual devices in the same general way they read physical webcams.

A typical device may appear as:

```text
/dev/video10
```

`ndi2v4l2` will act as the video producer for that device.

Applications such as Zoom should then be able to select the virtual device as a camera.

## Development Milestones

### Milestone 1: NDI Receiver

* [ ] Initialize the NDI runtime
* [ ] Discover NDI sources
* [ ] Display discovered source names
* [ ] Connect to a selected source
* [ ] Receive one valid decoded video frame
* [ ] Report frame resolution
* [ ] Report frame rate
* [ ] Report pixel format
* [ ] Cleanly disconnect and shut down

**Nothing else should be considered important until this milestone works reliably.**

### Milestone 2: V4L2 Output

* [ ] Detect an available `v4l2loopback` device
* [ ] Open the V4L2 output device
* [ ] Negotiate a compatible video format
* [ ] Send received NDI frames to V4L2
* [ ] Maintain the incoming frame rate
* [ ] Verify the stream with standard V4L2 utilities

### Milestone 3: Application Compatibility

* [ ] Zoom
* [ ] Chromium/Chrome
* [ ] Firefox
* [ ] Discord
* [ ] Microsoft Teams
* [ ] Other V4L2-compatible applications

### Milestone 4: Reliability

* [ ] Handle NDI source disconnects
* [ ] Automatically reconnect
* [ ] Handle resolution changes
* [ ] Handle frame-rate changes
* [ ] Handle malformed or unsupported frames
* [ ] Graceful shutdown
* [ ] Useful logging
* [ ] Useful exit codes

### Milestone 5: Distribution

* [ ] Arch Linux / Omarchy
* [ ] AUR package
* [ ] Debian / Ubuntu
* [ ] Fedora
* [ ] Other distributions based on community interest

### Future Ideas

Once the core bridge is stable:

* [ ] Optional GUI
* [ ] System tray control
* [ ] Automatic virtual camera creation
* [ ] Multiple NDI sources
* [ ] Multiple virtual cameras
* [ ] Audio support
* [ ] Configuration file
* [ ] systemd user service
* [ ] Hardware acceleration where appropriate
* [ ] Flatpak investigation

These features should not delay development of the core NDI-to-V4L2 bridge.

## Development Philosophy

Keep it small.

Before adding a large dependency, ask whether the dependency is actually necessary.

Before adding a GUI, make the command-line application reliable.

Before supporting every Linux distribution, make the core application work correctly.

Before optimizing performance, verify correctness.

Before building additional features, make this pipeline work:

```text
NDI Source
    |
    v
Decoded Video Frame
    |
    v
V4L2 Virtual Camera
    |
    v
Application
```

## Testing

The original development use case is an iPhone running an NDI HX camera application and a Linux workstation running Zoom.

However, the project should not contain iPhone-specific assumptions.

Any standards-compatible NDI source should eventually be usable.

Testing should include:

* NDI HX sources
* Standard NDI sources
* Different resolutions
* Different frame rates
* Source disconnect/reconnect
* Multiple Linux distributions
* Different Linux kernels
* Different V4L2 consumers

## Contributing

Contributions are welcome once the initial project structure is established.

Useful contributions may include:

* Code
* Testing
* Bug reports
* Documentation
* Packaging
* Distribution compatibility
* Performance improvements
* V4L2 compatibility fixes
* NDI source compatibility testing

When reporting a problem, please include:

```text
Linux distribution:
Kernel:
ndi2v4l2 version:
NDI runtime version:
NDI source:
Source resolution:
Source frame rate:
v4l2loopback version:
Application using the camera:
Relevant logs:
```

## License

The original `ndi2v4l2` source code is intended to be released under the MIT License.

Third-party components remain subject to their respective licenses.

The NDI SDK/runtime is not licensed under the MIT License merely because this project uses it. Users and distributors are responsible for complying with the applicable NDI SDK and runtime licensing terms.

See the `LICENSE` file for the license covering the original code in this repository.

## Trademark Notice

NDI® is a registered trademark of Vizrt NDI AB.

`ndi2v4l2` is an independent open-source project and is not an official NDI product.

The project is not intended to imply endorsement, certification, sponsorship, or affiliation with Vizrt NDI AB.

The NDI name is used to describe compatibility with and use of the NDI technology.

## Name Notice

The current project name is **ndi2v4l2**.

Because the project name contains the NDI name, the project's naming and branding should be reviewed against the current NDI brand and licensing guidelines before a formal public release.

## Disclaimer

This project is experimental software.

It is currently under development and should not yet be relied upon for production use.

Use it at your own risk.

---

**Current objective:**

> Receive one real NDI video frame on Linux and prove it can be delivered to a V4L2 virtual camera.

Everything else comes after that.
