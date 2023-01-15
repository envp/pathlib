#!/usr/bin/python3
import pathlib
import argparse

from typing import List


_SCRIPT_CWD = pathlib.Path.cwd().absolute()
_EXAMPLES_DIR = (
    pathlib.Path(__file__)
    .parent.joinpath("../examples")
    .relative_to(_SCRIPT_CWD)
    .resolve()
)


def create_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="create-example",
        description="Set up the scaffolding for a new pathlib example.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "--examples-dir",
        type=pathlib.Path,
        help="Path to examples directory",
        default=_EXAMPLES_DIR,
    )
    parser.add_argument(
        "example_name", metavar="EXAMPLE_NAME", help="Name of the example"
    )
    return parser


def create_example(examples_root: pathlib.Path, name: str):
    """Set up the directory structure and bare minimum files.
    ```
        examples/
        + <name>/
        + + CMakeLists.txt
        + + main.cpp
    ```
    It will also add the subdirectory to `examples/CMakeLists.txt`,
    however it will not deduplicate these additions.
    """
    example_dir = examples_root / name
    example_dir.mkdir(exist_ok=True, parents=True)
    example_cml = example_dir / "CMakeLists.txt"
    example_main = example_dir / "main.cpp"
    with example_main.open(mode="w", encoding="utf-8") as handle:
        handle.write("int main() { return 0; }")

    with example_cml.open(mode="w", encoding="utf-8") as handle:
        handle.writelines(
            [
                f"add_executable({name})\n",
                f"target_sources({name} main.cpp)\n"
                f"target_link_libraries({name} PRIVATE pathlib)\n",
            ]
        )

    root_cml = examples_root / "CMakeLists.txt"
    with root_cml.open(mode="a", encoding="utf-8") as handle:
        handle.write(f"\nadd_subdirectory({name})")


def main():
    """Entrypoint to the utility script."""
    parser = create_parser()
    args = parser.parse_args()
    create_example(args.examples_dir, args.example_name)


if __name__ == "__main__":
    main()
