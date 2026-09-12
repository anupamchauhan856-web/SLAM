from engineering_ai.architecture.project_scanner import ProjectScanner
from engineering_ai.architecture.architecture_validator import (
    ArchitectureValidator
)


def main():
    project_root = "/home/anupam/slam_core"

    scanner = ProjectScanner(project_root)
    scan_result = scanner.scan()

    validator = ArchitectureValidator(scan_result)

    validator.validate()
    validator.print_report()


if __name__ == "__main__":
    main()