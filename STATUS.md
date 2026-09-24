# Persistent session handoff

Project: ndi2v4l2
Repository: `/home/loudmonkey/_git/ndi2v4l2`

## Current milestone

Milestone 2 - NDI Video Reception complete for NDI High Bandwidth.
Receiver functionality was validated with one real decoded frame from a local NDI High Bandwidth test source.
Milestones 0 and 1 remain complete. Milestone 3 has NOT started.
NDI HX reception is NOT working and remains an external/runtime blocker.

## Implementation

* Added `--probe "<source name>"` to the existing C++ application.
* Preserved exact normal output `ndi2v4l2 0.1.0` and `--list` discovery.
* Discovers sources for approximately three seconds and selects by exact NDI name.
* Creates a receiver with `NDIlib_recv_create_v3` and `NDIlib_recv_color_format_fastest`.
* Uses `NDIlib_recv_capture_v3` with null audio/metadata buffers to request video only.
* Receive wait is bounded by a 10-second steady-clock deadline, individual timeouts capped at 250 ms, and a 100-call limit.
* Checks frame data, positive dimensions and frame-rate values, reports metadata and the actual FourCC, then stops after the first video frame.
* Frees the frame with `NDIlib_recv_free_video_v2`, destroys the receiver and finder, and shuts down NDI before returning success.
* Failure paths also clean up and return nonzero. No V4L2, continuous receiver streaming, audio, conversion, or sender functionality was added to the application.

## External SDK

* Root: `/home/loudmonkey/SDKs/NDI SDK for Linux`
* Runtime: `lib/x86_64-linux-gnu/libndi.so.6.3.2`.
* Runtime version: `NDI SDK LINUX 12:51:52 Apr 13 2026 6.3.2.0`.
* Existing CMake configuration links directly to this external SDK. SDK files were not modified or copied into the repository.

## Successful High Bandwidth validation (2026-09-24)

* Inspected official `examples/C++/NDIlib_Send_Video/NDIlib_Send_Video.cpp` as the reference for the synchronous video send API.
* Temporary sender source, executable, and validation harness lived only under `/tmp/ndi2v4l2-ndi-test-sender`.
* Built with the existing C++ compiler and external SDK; no new dependencies.
* Sender submitted a synthetic 640x360 BGRX progressive image at 30/1 fps through `NDIlib_send_send_video_v2`, allowing the SDK to encode ordinary High Bandwidth NDI. No audio.
* Sender had a 30-second lifetime limit and was stopped by the harness immediately after validation. Sender destruction and NDI shutdown completed; exit 0.
* Actual discovered source: `OMARCHY-DELL (ndi2v4l2 Test Source)`.
* Exact probe: `./build/ndi2v4l2 --probe "OMARCHY-DELL (ndi2v4l2 Test Source)"`.
* `NDIlib_recv_capture_v3` returned one valid video frame:
  * Width: 640
  * Height: 360
  * Frame-rate numerator: 30
  * Frame-rate denominator: 1
  * Calculated frame rate: 30 fps
  * FourCC: UYVY (`0x59565955`)
  * Line stride: 1280 bytes
* Dimensions and frame rate match the sender. UYVY stride is consistent with two bytes per pixel.
* Confirmed frame release, receiver destruction, finder destruction, NDI shutdown, and probe exit 0.
* Receiver implementation validated independently of the unresolved iPhone HX decoding issue.

## Tests performed and passed

* CMake configure with `-DNDI_SDK_ROOT='/home/loudmonkey/SDKs/NDI SDK for Linux'` and `cmake --build build` passed during Milestone 2 implementation.
* Byte-for-byte normal output check passed: `ndi2v4l2 0.1.0\n`, no stderr, exit 0.
* `--list` discovered the iPhone during earlier testing and the temporary High Bandwidth source during final validation; exit 0.
* Bounded one-frame High Bandwidth probe passed with the metadata and cleanup above.
* Temporary sender compiled successfully and exited cleanly.
* Project diff and file inventory reviewed; only `src/main.cpp` and `STATUS.md` changed for Milestone 2. No temporary sender or SDK files are included. Generated project build artifacts remain ignored.
* `git diff --check` passed.

## Tests failed / external NDI HX blocker

NDI HX reception from iPhone is currently blocked on Linux because NDI 6.3.2 attempts to load libndihx.so and that component is not present in the distributed Linux SDK or system. Official clarification from NDI is required.

* iPhone source: `IPHONE 4D38 (HX Camera)`.
* Both HEVC and subsequently H.264 broadcasts produced an active connection but no decoded video frame within the bounded 10-second test; exit 1 after cleanup.
* `ldd` found no unresolved directly linked dependencies.
* A separate bounded `LD_DEBUG=libs,files` test showed a failed `libndihx.so` lookup. It showed no attempts to load FFmpeg libraries. This identifies a missing runtime component, but its necessity for this specific source still requires official confirmation.
* Runtime strings reference `libavcodec.so.61`, `libavutil.so.59`, and their `-ndi` variants. System FFmpeg 2:9.0.1-4 supplies libavcodec.so.63 and libavutil.so.61. This ABI mismatch is a potential additional issue, not a confirmed cause from the loader trace.
* Read-only searches found no libndihx.so in the SDK, original installer payload, home directory, or normal system library locations.
* Official standard SDK material advertises HX reception, while specific H.264 documentation directs Linux users to NDI SDK support. No public official Linux libndihx.so download was identified.
* No HX fix attempted. HX is not implemented or validated as working.

## Files changed for Milestone 2

* src/main.cpp
* STATUS.md

## System changes

None. Temporary test infrastructure exists only under `/tmp`; the sender is stopped. No SDK changes, library changes, system configuration changes, or compatibility symlinks.

## Packages installed

None. No FFmpeg or other multimedia framework downloads/builds.

## Next recommended task

Milestone 3 - Independent V4L2 Output

Milestone 3 has NOT started. Begin only under a separate user assignment.
The final task response records the Milestone 2 commit hash, push result, and clean/synchronized repository verification.
