# SLAM (Simultaneous Localization and Mapping)

A modular C++17 multi-sensor SLAM system with automated evaluation and failure analysis.

## System Specification

- **Visualizer:** Pangolin

## High-Level Architecture

### Sensors: Calibration, Drivers, Dataset Player, Data Source

```text
                         Config YAML
                              │
                              ▼
                       SensorManager
                              │
        ┌─────────────────────┼─────────────────────┐
        │                     │                     │
        ▼                     ▼                     ▼
 SensorContext(s)       BufferManager       CalibrationManager
        │                     ▲                     │
        ▼                     │                     ▼
  SensorDriver         DatasetPlayer       ICalibrationLoader
        │                     ▲                     │
        ▼                     │                     ▼
EurocDatasetDriver      IDataSource       EurocCalibrationLoader
                              │
                        ┌─────┴─────┐
                        ▼           ▼
                EurocCameraSource  EurocImuSource
                        │           │
                        └─────┬─────┘
                              ▼
                        BufferManager
                              │
                              ▼
                          SLAM Core
```

## Status

- ⚪ Not Started
- 🟡 In Progress
- 🟢 Completed

## Architecture Layers
- 🟢 **Configuration** — YAML-based system and sensor configuration
- 🟢 **Sensor Management** — Sensor registration and lifecycle coordination
- 🟢 **Sensor Context** — Per-sensor driver and calibration ownership
- 🟢 **Calibration** — Calibration management and loading
- 🟢 **Sensor Drivers** — Sensor lifecycle abstraction
- 🟢 **Data Sources** — EuRoC camera and IMU data acquisition
- 🟢 **Dataset Player** — Dataset playback and measurement delivery
- 🟢 **Buffer Management** — Bounded, timestamp-aware multi-sensor buffering
- 🟡 **Visual Frontend** — Monocular visual processing
- ⚪ **IMU Frontend** — IMU processing and preintegration
- ⚪ **LiDAR Frontend**
- ⚪ **SLAM Backend** — Mapping and optimization
- ⚪ **Trajectory Evaluation** — ATE, RPE and trajectory analysis
- 🟡 **SLAM Sentinel** — Automated architecture and engineering validation

## Target Systems

- 🟡 Monocular SLAM
- ⚪ Visual-Inertial SLAM
- ⚪ Stereo SLAM

## Visual Frontend

- ⚪ Feature detection using ORB
- ⚪ Feature matching
- ⚪ Descriptor filtering
- ⚪ Lowe Ratio Test
- ⚪ RANSAC
- ⚪ Essential matrix
- ⚪ Fundamental matrix
- ⚪ PnP
- ⚪ Pose recovery
- ⚪ Motion gating
- ⚪ Triangulation
- ⚪ Parallax check
- ⚪ Reprojection error check
- ⚪ Pose refinement