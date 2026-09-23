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

## Autonomous actions allowed

Codex may perform normal development work without asking permission when the action stays within the user's home directory or project repository and the current approved task scope. This includes:

* Creating and editing project files.
* Creating normal development directories under `/home/loudmonkey`, including `/home/loudmonkey/SDKs`.
* Downloading official development SDKs or source archives into the user's home directory and extracting them there.
* Configuring and building the project and running necessary tests.
* Deleting generated project build artifacts.
* Using `git status`, `git diff`, and `git log`.
* Staging project files with `git add` and creating normal project commits.
* Pushing completed, validated milestone commits to `origin/main`.

A successfully completed milestone should normally be committed and pushed automatically unless the user explicitly says not to. Use clear, descriptive milestone commit messages.

## Explicit approval required

STOP and ask the user before:

* Using `sudo`.
* Installing, upgrading, or removing system packages with `pacman`, `yay`, or similar tools.
* Modifying files under `/etc` or `/usr`, or otherwise changing system configuration.
* Changing boot configuration.
* Loading, unloading, installing, or configuring kernel modules.
* Changing permissions or ownership of system files.
* Enabling or disabling system services.
* Compiling large third-party frameworks, multimedia stacks such as FFmpeg or GStreamer, or kernel components from source.
* Changing the approved architecture or implementation strategy. Explain the problem before proposing a change, including when the current approach fails.
* Performing destructive Git operations, force pushes, or rewriting Git history.

These approval requirements apply even when a command is launched from the user's home directory or project repository.

## Dependency policy

A dependency downloaded and kept entirely within the user's home directory may be downloaded and prepared autonomously when it is clearly required by the current approved milestone. If installation requires root privileges or changes to the operating system, stop and request approval. The explicit approval requirements above, including those for large third-party builds, still apply.

## Scope and execution safeguards

* Never attempt several unrelated alternative solutions within one task.
* If the same approach fails twice for substantially the same reason, stop.
* Do not use subagents unless explicitly authorized.
* Do not perform more than 15 significant shell/tool operations during one implementation task without stopping and reporting status.
* Keep every task limited to the explicitly assigned milestone or workflow task.
* Do not automatically continue into the next milestone.
* Run only the tests necessary to validate the current milestone or workflow task.

## Git checkpoint policy

* Keep the Git repository recoverable.
* Never commit secrets, private keys, SDK credentials, proprietary binaries, or generated build directories.
* Update `STATUS.md` before finishing every development task.
* Do not commit a failed or incomplete milestone unless preserving an explicit blocker/checkpoint is useful. Such a commit must clearly describe the incomplete state.

After a milestone passes all acceptance criteria, unless the user explicitly says not to commit or push:

1. Update `STATUS.md`.
2. Run the required validation.
3. Run `git diff --check`.
4. Review `git status`.
5. Stage the milestone files.
6. Commit them with a descriptive milestone commit message.
7. Push the commit to `origin/main`.
8. Verify the working tree is clean and synchronized with `origin/main`.
9. Stop.

At every completed checkpoint tell the user:

`Checkpoint reached. Run /status before starting the next milestone.`
