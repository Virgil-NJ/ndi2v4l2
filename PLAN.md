# ndi2v4l2 development plan

Do not skip milestones.

A later milestone may begin only after the previous milestone's acceptance criteria have been demonstrated or the user explicitly changes the plan.

## Milestone 0: C++ Project Scaffold

Goal: Create the smallest possible C++/CMake application.

Acceptance criteria:

* CMake project exists.
* Application compiles.
* Running it prints the project name/version and exits successfully.
* No NDI integration.
* No V4L2 integration.
* No new system dependencies unless explicitly approved.

## Milestone 1: NDI Source Discovery

Goal: Initialize the NDI runtime and enumerate available NDI sources.

Acceptance criteria:

* Application can initialize the installed NDI runtime.
* Available NDI sources can be listed.
* The development iPhone source should appear when broadcasting.
* No video decoding yet.
* No V4L2 integration yet.

## Milestone 2: NDI Video Reception

Goal: Connect to one selected NDI source and receive real video frames.

Acceptance criteria:

* Connect to the selected source.
* Receive at least one valid video frame.
* Print resolution.
* Print frame rate.
* Print pixel format.
* Cleanly release the frame and connection.

Do not proceed to V4L2 until this works.

## Milestone 3: Independent V4L2 Output

Goal: Prove V4L2 output independently of NDI.

Acceptance criteria:

* Detect or use an explicitly provided `v4l2loopback` device.
* Send a synthetic test image or generated video frame to `/dev/videoX`.
* Verify another Linux application can read the virtual camera.

No NDI connection is required for this milestone.

## Milestone 4: NDI to V4L2 Bridge

Goal: Connect the already-working NDI receiver to the already-working V4L2 output.

Acceptance criteria:

* Receive live NDI video.
* Feed frames directly into the virtual V4L2 device.
* Maintain stable video.
* Avoid unnecessary frame conversion where possible.

## Milestone 5: Application Compatibility

Goal: Verify the virtual camera works in normal Linux applications.

Initial target: Zoom.

Later testing may include:

* Chromium/Chrome
* Firefox
* Discord
* Microsoft Teams
* other V4L2-compatible applications

## Milestone 6: Reliability

Add:

* reconnect after source loss
* graceful shutdown
* useful error messages
* source selection
* resolution changes
* frame-rate handling
* proper cleanup
* logging

## Milestone 7: Packaging

Initial target:

* Arch Linux
* Omarchy Linux
* AUR packaging

Later:

* Debian/Ubuntu
* Fedora

## Milestone 8: Community Release

Prepare:

* documentation
* GitHub Issues
* contribution instructions
* automated build/test workflow where practical
* versioned release
* v0.1.0
