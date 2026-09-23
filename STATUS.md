# Persistent session handoff

Project: ndi2v4l2
Repository: `/home/loudmonkey/_git/ndi2v4l2`

## Current milestone

Milestone 1 - NDI Source Discovery complete
Milestone 0 remains complete. Milestone 2 has NOT started.

## Work completed

* Re-read AGENTS.md, PLAN.md, STATUS.md. Initial branch main tracked origin/main; only STATUS.md had the prior blocker notes modified.
* User explicitly reviewed and accepted the SDK license and authorized answering y.
* Ran the inspected official installer in `/home/loudmonkey/SDKs`; no system installation.
* SDK layout includes include, lib, bin, documentation, examples, and licenses, all outside the repository.
* Verified runtime version through NDIlib_version: `NDI SDK LINUX 12:51:52 Apr 13 2026 6.3.2.0`.
* Added CMake NDI_SDK_ROOT setting (also initialized from the environment), header/library lookup, and direct shared-library linking. No runtime dynamic-loading architecture was added.
* Preserved C++17, project version 0.1.0, compilation database export, and out-of-source build.
* Implemented --list: runtime initialization, finder creation, approximately three seconds of discovery, source-name enumeration, finder destruction, runtime shutdown. No sources is a successful result.
* Normal invocation continues to print `ndi2v4l2 0.1.0`.
* No video reception, decoding, audio, V4L2, or Milestone 2 work.

## External SDK

* Root: `/home/loudmonkey/SDKs/NDI SDK for Linux`
* Headers: `include/Processing.NDI.Lib.h` and its included headers, including `Processing.NDI.Find.h`.
* Runtime: `lib/x86_64-linux-gnu/libndi.so.6.3.2`.
* Both `libndi.so` and `libndi.so.6` symlink to `libndi.so.6.3.2` in that directory.
* SDK/runtime remain separately licensed external dependencies. No SDK materials were copied into the repository.

## Files changed

* CMakeLists.txt
* src/main.cpp
* STATUS.md

## Tests performed

* `cmake -S . -B build -DNDI_SDK_ROOT='/home/loudmonkey/SDKs/NDI SDK for Linux'`
* `cmake --build build`
* `./build/ndi2v4l2`
* `./build/ndi2v4l2 --list` (outside the network sandbox)
* Runtime version queried with Python ctypes and NDIlib_version.
* `git diff --check`
* `git status --short --branch`
* Python subprocess byte-for-byte version-output assertion and JSON compilation database C++17 check.
* `git ls-files`; `git ls-files --others --exclude-standard`
* `git check-ignore build/ndi2v4l2 build/compile_commands.json`
* `ldd build/ndi2v4l2`

## Tests passed

* CMake configuration and final build succeeded.
* Normal invocation printed `ndi2v4l2 0.1.0` and exited 0.
* --list initialized NDI, created the finder, completed discovery and cleanup, printed `No NDI sources found.`, and exited 0.

* After the user confirmed broadcasting, --list printed `Available NDI sources:` and `IPHONE 4D38 (HX Camera)` and exited 0.
* Exact normal output and C++17 compilation database checks passed.
* Runtime resolves from the external SDK directory; tracked/untracked file inventory contains no SDK materials. Build artifacts are ignored.
* Milestone 1 acceptance criteria passed; discovery command validated.

## Tests failed

* Initial build failed because SDK headers require NULL to be defined before inclusion. Fixed by including standard `<cstddef>` first; rebuild passed without changing SDK files.
* No outstanding test failures.

## Known blockers

None. The live iPhone source was discovered after the user started broadcasting. No network troubleshooting was needed.

## System changes

None. Official SDK extracted only under `/home/loudmonkey/SDKs`.

## Packages installed

None.

## Next recommended task

Milestone 2 - NDI Video Reception, only after a separate user assignment. Milestone 2 has NOT started.

Completed Milestone 1 is ready for its authorized commit and push. The final task response records the commit hash, push result, and clean/synchronized repository verification.
