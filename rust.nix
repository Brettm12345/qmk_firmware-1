let
  pkgs = import <nixpkgs> { };
  sources = import ./nix/sources.nix;
  naersk = pkgs.callPackage sources.naersk { };
  pkg = naersk.buildPackage {
    root = ./rust;
    userAttrs = {
      CFLAGS =
        "-isystem /nix/store/6i5ngd8035kzh3pdhpr0rflfvk425aqk-avr-libc-2.0.0/avr/include -B/nix/store/6i5ngd8035kzh3pdhpr0rflfvk425aqk-avr-libc-2.0.0/avr/lib/avr5 -L/nix/store/6i5ngd8035kzh3pdhpr0rflfvk425aqk-avr-libc-2.0.0/avr/lib/avr5 -B/nix/store/6i5ngd8035kzh3pdhpr0rflfvk425aqk-avr-libc-2.0.0/avr/lib/avr35 -L/nix/store/6i5ngd8035kzh3pdhpr0rflfvk425aqk-avr-libc-2.0.0/avr/lib/avr35 -B/nix/store/6i5ngd8035kzh3pdhpr0rflfvk425aqk-avr-libc-2.0.0/avr/lib/avr51 -L/nix/store/6i5ngd8035kzh3pdhpr0rflfvk425aqk-avr-libc-2.0.0/avr/lib/avr51";
    };
  };

in { inherit pkg; }
