# texpand

Convert LaTeX macros to Unicode codepoints on standard input.

# Usage

```
printf %s '\\theta' | texpand
# θ

printf %s '\\mathbb{Z}' | texpand
# ℤ
```

Macros which take an argument require `{}` around the argument. Subscripts and
superscripts are not supported; see
[UnicodeIt](https://github.com/svenkreiss/unicodeit).
