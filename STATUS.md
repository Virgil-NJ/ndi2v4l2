# Persistent session handoff

Project: ndi2v4l2
Repository: `/home/loudmonkey/_git/ndi2v4l2`

## Current milestone

Milestone 0 - C++ Project Scaffold complete.
Milestone 1 - NDI Source Discovery blocked during prerequisite inspection; implementation has not started.
Milestone 2 has NOT started.

## Previous prerequisite inspection

* Read AGENTS.md, PLAN.md, STATUS.md and inspected the Milestone 0 scaffold.
* Confirmed repository identity, branch `main`, and initially clean working tree.
* HEAD and cached origin/main both identify `466c2d0f9c1958149ccd2bbdc31bafdb4bcae0f3` (zero divergence).
* Inspected standard include/library locations, /opt, the user's home directory, linker cache, and installed-package metadata for NDI development components.
* No Processing.NDI headers or libndi libraries were found in the inspected locations. No matching installed-package metadata was found.
* Dynamic loader could not resolve libndi.so, libndi.so.6, or libndi.so.5. NDI runtime directory variables and LD_LIBRARY_PATH are unset.
* Installed NDI SDK/runtime version and usable library path could not be determined because the components were not found.
* Stopped before implementation, installation, or system configuration changes.

## Files changed

* AGENTS.md: clarified autonomous actions, explicit approvals, dependencies, and automatic Git checkpoints.
* STATUS.md: preserved the dependency blocker and recorded this workflow-only update.

## Tests performed

* `git status --short --branch`
* `git remote -v`
* `git rev-list --left-right --count HEAD...origin/main`
* `git rev-parse HEAD origin/main`
* `git ls-remote origin refs/heads/main`
* `ldconfig -p | rg -i 'libndi'`
* `find /usr/include /usr/lib /usr/local /opt /home/loudmonkey -name 'Processing.NDI*' -o -name 'libndi*' -o -iname '*ndi*sdk*' 2>/dev/null`
* `rg -i '^ndi|libndi|ndi-sdk' /var/lib/pacman/local/*/desc`
* Python ctypes.CDLL resolution checks for libndi.so, libndi.so.6, and libndi.so.5, plus runtime environment variable inspection.
* Final checks: `git diff --check`; `git status --short --branch`.

## Tests passed

* Initial working tree clean; branch main; cached origin/main matches HEAD.
* Milestone 0 scaffold remains unchanged: C++17, version 0.1.0, compilation database export, out-of-source build workflow.

## Tests failed / not run

* Runtime resolution checks failed: libraries not found.
* Live remote verification failed: SSH reported bad owner or permissions on `/etc/ssh/ssh_config.d/20-omarchy-keepalive.conf`. No SSH settings were changed.
* Configure/build and discovery tests not run because required NDI development components are missing.
* Milestone 1 acceptance criteria have NOT passed.

## Known blockers

* Official NDI SDK for Linux is needed: C/C++ API headers for compilation and the prebuilt shared runtime for initialization and discovery.
* Obtain the Linux SDK from https://ndi.video/for-developers/ndi-sdk/download/ when Milestone 1 is assigned again, following the home-directory dependency policy in AGENTS.md. Proposed installer invocation, after obtaining/extracting the official v6 installer in a user-owned directory: `bash ./Install_NDI_SDK_v6_Linux.sh`. Verify the supplied installer filename and review its license before execution; do not auto-accept the license.
* Source: official NDI SDK, not an Arch repository or AUR package. No third-party source compilation is proposed.
* SDK/runtime remain subject to NDI's own license, not this project's MIT license. Review the supplied agreement and redistribution/attribution requirements before distribution; do not commit proprietary SDK/runtime files.
* Live origin/main synchronization remains unverified because of the SSH configuration error above.

## System changes

None.

## Packages installed

None.

## Next recommended task

Run `/status`, then await a separate assignment to resume Milestone 1. Under the updated policy, required SDK downloads and preparation entirely within the home directory may proceed autonomously during that approved milestone; system changes still require approval. Do not begin Milestone 2.

## Current workflow task

* Updated execution policy only; no Milestone 1 implementation, SDK preparation, or system changes performed.
* Preserved the prior incomplete Milestone 1 inspection as an explicit blocker checkpoint in this policy commit.
* Validation: documentation diff review and `git diff --check`; no application tests needed for this documentation-only change.
* Delivery: commit and push this policy update to origin/main, then verify a clean, synchronized working tree. Final delivery results are reported in the task response.
