# FreeBuild (Geode mod)

FreeBuild is an experimental Geometry Dash editor utility mod scaffold.

## Current implementation
- Scans all editor objects or objects within a rectangular selection region.
- Records object ID, position, rotation, and X/Y scale in JSON.
- Writes the latest scan to the mod's save directory as `last-scan.json`.
- Includes a GitHub Actions workflow for Geode builds on supported platforms.

## Build
The GitHub Actions workflow builds this repository using the Geode SDK build action. Open the **Actions** tab to inspect the run and download its artifacts if the build succeeds.

## Notes
This is an early scaffold. Editor UI/API compatibility and platform builds still need validation against the current Geode SDK. Tech/Null/Hell style profiles and decoration-template placement are not implemented yet.
