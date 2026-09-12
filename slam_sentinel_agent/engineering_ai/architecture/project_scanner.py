from pathlib import Path


class ProjectScanner:
    def __init__(self, project_root):
        self.project_root = Path(project_root)

    def scan(self):
        return {
            "project_root": str(self.project_root),
            "directories": self._scan_directories(),
            "cpp_files": self._scan_files(["*.cpp"]),
            "header_files": self._scan_files(["*.h", "*.hpp"]),
            "config_files": self._scan_files(["*.yaml", "*.yml"]),
            "python_files": self._scan_files(["*.py"]),
        }

    def _scan_directories(self):
        directories = []

        for path in self.project_root.rglob("*"):
            if path.is_dir() and not self._should_ignore(path):
                directories.append(
                    str(path.relative_to(self.project_root))
                )

        return sorted(directories)

    def _scan_files(self, patterns):
        files = []

        for pattern in patterns:
            for path in self.project_root.rglob(pattern):
                if path.is_file() and not self._should_ignore(path):
                    files.append(
                        str(path.relative_to(self.project_root))
                    )

        return sorted(set(files))

    def _should_ignore(self, path):
        ignored = {
            ".git",
            "build",
            ".vscode",
            "__pycache__",
            ".cache",
        }

        return any(part in ignored for part in path.parts)