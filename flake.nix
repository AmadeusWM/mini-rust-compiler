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
            gdb
            flex
            bison
            cmake
            # get ast: cargo rustc -- -Z unpretty=ast-tree
            # get hir: cargo rustc -- -Z unpretty=hir-tree
            # get typed: cargo rustc -- -Z unpretty=thir-tree
            rust-bin.nightly."2024-10-01".default
            spdlog
            clang-tools
        ];
        buildInputs = packages;
      };

      packages = rec {
      default = mini-rust;
      mini-rust = pkgs.stdenv.mkDerivation {
        pname = "mini-rust";
        version = "0.1.0";
        src = ./.;
        nativeBuildInputs = [
            pkgs.cmake
            pkgs.flex
            pkgs.bison
            pkgs.spdlog
        ];
        buildPhase = ''
            cmake .
            make -j$(nproc)
        '';
        installPhase = ''
            mkdir -p $out/bin
            cp mini-rust $out/bin/
        '';
        meta = with pkgs.lib; {
            description = "A mini Rust compiler written in C++";
            license = licenses.mit;
            maintainers = [ maintainers.your-github-username ];
            platforms = platforms.linux;
        };
      };
    };
  });
}
