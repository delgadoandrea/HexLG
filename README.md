## G4 simulation for Hexagonal light-guide

### Currently on the package:

- Optical Physics class including most optical photon processes.
- PMT SD/Hit class which can be expanded to include hit position, time, energy....
- Optical photon particle gun with random polarization/momentum direction.
- Very basic format to save ROOT histograms with number of photons hitting PMT or absorbed.
- Tracking classes to manually record hits.
- Messenger classes for particle gun/event settings/tracking actions.

- Python script for mac file creation.

# To run the code (Assuming G4 already installed):
1. Clone repository locally.
2. Create "Build directory".
3. Create cmake files in build directory.
  ```bash
   cd <path to build directory>
   cmake <path-to-cloned-repository>
   ```
4. Compile.
```bash
make -j<number of processors>
  ```
5.Run.
```bash
./HexLG photon.mac
  ```
