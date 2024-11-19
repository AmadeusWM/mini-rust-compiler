{
  description = "A Nix-flake-based Development Environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    rust-overlay.url = "github:oxalica/rust-overlay";
    flake-utils.url  = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, rust-overlay, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
    let
        overlays = [ (import rust-overlay) ];
        pkgs = import nixpkgs { inherit system overlays; };
    in
    {
      devShells.default = pkgs.mkShell rec {
        packages = with pkgs; [
            flex
            bison
            cmake
            # get ast: cargo rustc -- -Z unpretty=ast-tree
            # get hir: cargo rustc -- -Z unpretty=hir-tree
            # get typed: cargo rustc -- -Z unpretty=thir-tree
            rust-bin.nightly."2024-01-01".default
            spdlog
            clang-tools
        ];
        buildInputs = packages;
      };
    }
    );
}
