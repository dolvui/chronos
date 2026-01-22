{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.cmake
    pkgs.flex
    pkgs.bison
  ];

  shellHook = ''
    echo "Chronos dev environment ready"
  '';
}
