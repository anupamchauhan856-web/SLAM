from engineering_ai.architecture.architecture_contract import (
    ARCHITECTURE_CONTRACT
)


class ArchitectureValidator:
    def __init__(self, scan_result):
        self.scan_result = scan_result
        self.results = []

    def validate(self):
        self.results.clear()

        header_files = self.scan_result.get("header_files", [])
        cpp_files = self.scan_result.get("cpp_files", [])

        self._check_component("SensorManager", header_files, cpp_files)
        self._check_component("SensorContext", header_files, cpp_files)
        self._check_component("SensorDriver", header_files, cpp_files)
        self._check_component("IDataSource", header_files, cpp_files)
        self._check_component("DatasetPlayer", header_files, cpp_files)
        self._check_component("BufferManager", header_files, cpp_files)
        self._check_component("CalibrationManager", header_files, cpp_files)
        self._check_component("ICalibrationLoader", header_files, cpp_files)

        return self.results

    def _check_component(self, component, header_files, cpp_files):
        header_found = self._find_component(
            component,
            header_files
        )

        cpp_found = self._find_component(
            component,
            cpp_files
        )

        contract = ARCHITECTURE_CONTRACT.get(component, {})
        is_interface = contract.get("interface", False)

        if is_interface:
            if header_found:
                status = "PASS"
                message = "Interface header found."
            else:
                status = "FAIL"
                message = "Interface header not found."

        else:
            if header_found and cpp_found:
                status = "PASS"
                message = "Header and implementation found."

            elif header_found:
                status = "WARNING"
                message = "Header found, implementation not found."

            elif cpp_found:
                status = "WARNING"
                message = "Implementation found, header not found."

            else:
                status = "FAIL"
                message = "Component not found."

        self.results.append({
            "component": component,
            "status": status,
            "message": message
        })

    @staticmethod
    def _find_component(component, files):
        for file in files:
            filename = file.split("/")[-1]

            if filename == component + ".h":
                return True

            if filename == component + ".hpp":
                return True

            if filename == component + ".cpp":
                return True

        return False

    def print_report(self):
        print("\n========================================")
        print("SLAM SENTINEL - ARCHITECTURE VALIDATION")
        print("========================================\n")

        for result in self.results:
            print(
                f"{result['component']:<25}"
                f"{result['status']:<10}"
                f"{result['message']}"
            )

        failures = sum(
            1
            for result in self.results
            if result["status"] == "FAIL"
        )

        warnings = sum(
            1
            for result in self.results
            if result["status"] == "WARNING"
        )

        print("\n----------------------------------------")
        print(f"Failures : {failures}")
        print(f"Warnings : {warnings}")
        print("----------------------------------------")