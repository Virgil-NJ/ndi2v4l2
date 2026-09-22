# ndi2v4l2 — permanent Codex instructions

Read `AGENTS.md`, `PLAN.md`, and `STATUS.md` at the beginning of every future project session.

## Project

* This project is `ndi2v4l2`.
* The goal is a lightweight Linux application that receives an NDI video source and exposes it as a standard V4L2 virtual webcam.
* OBS must not be required.
* The initial development platform is Omarchy Linux / Arch Linux.
* The application will initially be written in C++ using CMake.
* Keep dependencies to the minimum technically necessary.
* Prefer direct use of the NDI SDK and Linux V4L2 interfaces.

## Authorization and scope

* Never install or remove system packages without explicit user authorization.
* Never modify system configuration without explicit user authorization.
* Never compile large third-party projects such as FFmpeg, GStreamer, or kernel components from source without explicit permission.
* Never change architecture because something fails without stopping and explaining the problem first.
* Never attempt several unrelated alternative solutions within one task.
* If the same approach fails twice for substantially the same reason, stop.
* Do not use subagents unless explicitly authorized.
* Do not perform more than 15 significant shell/tool operations during one implementation task without stopping and reporting status.
* Keep every task limited to the explicitly assigned milestone.
* Do not automatically continue into the next milestone.
* Run only the tests necessary to validate the current milestone.

## Git and checkpoints

* Keep the Git repository recoverable.
* Never rewrite Git history.
* Never force-push.
* Never commit secrets, private keys, SDK credentials, proprietary binaries, or generated build directories.
* Update `STATUS.md` before finishing every development task.
* At every completed checkpoint tell the user:

  `Checkpoint reached. Run /status before starting the next milestone.`
