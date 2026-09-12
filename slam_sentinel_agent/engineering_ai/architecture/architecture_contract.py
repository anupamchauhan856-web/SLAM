ARCHITECTURE_CONTRACT = {
    "SensorManager": {
        "owns": [
            "SensorContext",
            "BufferManager",
            "CalibrationManager"
        ],
        "interface": False
    },

    "SensorContext": {
        "owns": [
            "SensorDriver",
            "ICalibration"
        ],
        "interface": False
    },

    "SensorDriver": {
        "responsibility": [
            "lifecycle",
            "start",
            "stop",
            "state"
        ],
        "interface": True
    },

    "IDataSource": {
        "responsibility": [
            "measurement acquisition"
        ],
        "interface": True
    },

    "DatasetPlayer": {
        "responsibility": [
            "dataset playback",
            "push measurements to BufferManager"
        ],
        "interface": False
    },

    "BufferManager": {
        "responsibility": [
            "multi-sensor buffering",
            "timestamp ordering",
            "bounded buffering"
        ],
        "interface": False
    },

    "CalibrationManager": {
        "responsibility": [
            "calibration orchestration"
        ],
        "interface": False
    },

    "ICalibrationLoader": {
        "responsibility": [
            "load calibration"
        ],
        "interface": True
    }
}