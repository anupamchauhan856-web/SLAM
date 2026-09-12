# SLAM (Simultaneous Localization and Mapping)

A modular C++17 multi-sensor SLAM system with automated evaluation and failure analysis.

## System Specification

- **Current visualizer:** Pangolin

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