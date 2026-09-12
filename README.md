# SLAM (Simultaneous Localization and Mapping)

Modular Visual, Visual-Inertial and Stereo SLAM framework in C++.

## System Specification

- **Current visualizer:** Pangolin

## High-Level Architecture
### Sensor Calibration
                    ┌──────────────────────┐
                    │    SensorManager     │
                    │      TOP OWNER       │
                    └──────────┬───────────┘
                               │
                ┌──────────────┴──────────────┐
                │                             │
              owns                          owns
                │                             │
                ▼                             ▼
       ┌─────────────────┐          ┌─────────────────┐
       │ SensorContext   │          │CalibrationManager│
       │   per sensor    │          └─────────────────┘
       └───────┬─────────┘
               │
          ┌────┴────┐
          │         │
        owns      owns
          │         │
          ▼         ▼
    ┌──────────┐ ┌──────────────┐
    │  Driver  │ │ICalibration  │
    └──────────┘ └──────────────┘

                         ┌─────────────────────────┐
                         │     SENSOR CONFIG       │
                         │       YAML / JSON       │
                         └────────────┬────────────┘
                                      │
                                      ▼
                         ┌─────────────────────────┐
                         │     SensorManager       │
                         │                         │
                         │  • loadConfig()         │
                         │  • sensor registration  │
                         │  • calibration setup    │
                         │  • owns SensorContexts  │
                         │  • owns CalibrationMgr  │
                         └───────────┬─────────────┘
                                     │
                   ┌─────────────────┴─────────────────┐
                   │                                   │
                   │ owns                              │ owns
                   ▼                                   ▼
        ┌─────────────────────────┐        ┌─────────────────────────┐
        │     SensorContext       │        │   CalibrationManager    │
        │       (per sensor)      │        │                         │
        │                         │        │ • validates config      │
        │ • sensor identity       │        │ • selects provider      │
        │ • owns SensorDriver     │        │ • coordinates loading   │
        │ • owns ICalibration     │        │ • coordinates algorithm │
        └────────────┬────────────┘        └────────────┬────────────┘
                     │                                  │
                     │ owns                             │
                     ▼                                  │
        ┌─────────────────────────┐                     │
        │      SensorDriver       │                     │
        │                         │                     │
        │ • init()                │                     │
        │ • start()               │                     │
        │ • stop()                │                     │
        │ • lifecycle/state       │                     │
        └────────────┬────────────┘                     │
                     │                                  │
                     │                                  │
                     │                    CalibrationConfig
                     │                                  │
                     │                                  ▼
                     │                    ┌─────────────────────────┐
                     │                    │     Provider Selection  │
                     │                    └────────────┬────────────┘
                     │                                 │
                     │                    ┌────────────┴────────────┐
                     │                    │                         │
                     │                    ▼                         ▼
                     │          ┌────────────────────┐   ┌────────────────────────┐
                     │          │ ICalibrationLoader │   │ ICalibrationAlgorithm  │
                     │          │                    │   │                        │
                     │          │ Load existing      │   │ Compute calibration     │
                     │          │ calibration data   │   │ from observations/data │
                     │          └──────────┬─────────┘   └───────────┬────────────┘
                     │                     │                         │
                     │                     ▼                         ▼
                     │          ┌────────────────────┐   ┌────────────────────────┐
                     │          │ EurocCalibration   │   │ Zhang / Stereo /       │
                     │          │ Loader             │   │ Future Algorithms      │
                     │          └──────────┬─────────┘   └───────────┬────────────┘
                     │                     │                         │
                     │                     └────────────┬────────────┘
                     │                                  │
                     │                                  ▼
                     │                    ┌─────────────────────────┐
                     │                    │      ICalibration       │
                     │                    │                         │
                     │                    │ Common calibration      │
                     │                    │ interface               │
                     │                    └────────────┬────────────┘
                     │                                 │
                     │                    ownership transferred to
                     │                                 │
                     └─────────────────────────────────┘
                                                       │
                                                       ▼
                                      ┌─────────────────────────┐
                                      │     SensorContext       │
                                      │                         │
                                      │ owns resulting          │
                                      │ ICalibration             │
                                      └─────────────────────────┘

                                        ┌──────────────────────┐
                                        │   Sensor YAML Config │
                                        └──────────┬───────────┘
                                                    │
                                                    ▼
                                        ┌──────────────────────┐
                                        │    SensorManager     │
                                        │                      │
                                        │ Creates              │
                                        │ CalibrationConfig    │
                                        └──────────┬───────────┘
                                                    │
                                                    ▼
                                        ┌──────────────────────┐
                                        │ CalibrationManager   │
                                        └──────────┬───────────┘
                                                    │
                                            provider type
                                                    │
                                            ┌────┴─────┐
                                            ▼          ▼
                                        ┌──────────┐ ┌───────────────┐
                                        │  Loader  │ │   Algorithm   │
                                        └────┬─────┘ └───────┬───────┘
                                            │               │
                                            └───────┬───────┘
                                                    ▼
                                            ┌────────────────┐
                                            │ ICalibration   │
                                            └───────┬────────┘
                                                    │
                                            std::unique_ptr
                                                    │
                                                    ▼
                                            ┌────────────────┐
                                            │SensorContext   │
                                            │                │
                                            │ owns           │
                                            │ calibration   │
                                            └────────────────┘

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
