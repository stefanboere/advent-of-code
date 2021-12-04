{
  description = "J development shell";

  inputs = {
    nixpkgs.url = "nixpkgs/nixpkgs-unstable";

    moz_overlay = {
      url = "github:mozilla/nixpkgs-mozilla";
      flake = false;
    };
  };

  outputs = { self, nixpkgs, moz_overlay }:
    let
      overlay = final: prev: {
        haskellPackages = prev.haskellPackages.override {
          overrides = with prev.haskell.lib;
            self: super: {
              advent-of-code =
                self.callCabal2nix "advent-of-code" ./haskell { };
            };
        };
      };

      pkgs = import nixpkgs {
        system = "x86_64-linux";
        config.permittedInsecurePackages = [ "libgit2-0.27.10" ];
        overlays = [ overlay (import moz_overlay) ];
      };
    in {
      devShell."x86_64-linux" = pkgs.haskellPackages.shellFor {
        packages = ps: [ ps.advent-of-code ];
        nativeBuildInputs = with pkgs; [
          cabal-install
          haskell-language-server
          ((rustChannelOf {
            channel = "nightly";
            sha256 = "B3T/bVER66CE2z7Ocvk7Gn6hXwDZnW+5n/3C0H+HSOk=";
          }).rust.override { targets = [ "wasm32-unknown-unknown" ]; })
          cargo
          rustfmt
          j
          cmake
          swiProlog
          julia_16-bin
          sbcl
          python3
        ];
        RUST_BACKTRACE = 1;
      };
    };
}
