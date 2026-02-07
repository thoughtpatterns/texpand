# texpand

Convert LaTeX macros to Unicode codepoints on standard input. Whitespace is
trimmed from inputs.

## Installation

Requires `gperf`.

```bash
make -C ./src install
```

# Usage

```bash
printf %s '\\theta' | texpand
# θ

printf %s ' \\theta ' | texpand
# θ

printf %s '\\mathbb{Z}' | texpand
# ℤ
```

Macros which take an argument require `{}` around the argument. Subscripts and
superscripts are not supported; if this is unacceptable, see
[UnicodeIt](https://github.com/svenkreiss/unicodeit).
