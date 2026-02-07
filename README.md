# texpand

Convert LaTeX macros to Unicode codepoints on standard input. Whitespace is
trimmed from inputs.

## Installation

Requires `gperf`.

```bash
make -C ./src install
```

## Usage

```bash
printf %s '\\theta' | texpand
# θ

printf '\n %s \n' '\\theta' | texpand
# θ

printf %s '\\mathbb{Z}' | texpand
# ℤ
```

Macros which take an argument require `{}` around the argument. Subscripts and
superscripts are not supported; if this is unacceptable, see
[UnicodeIt](https://github.com/svenkreiss/unicodeit).

Text editors which can pipe to `sh` can use `texpand` on a keybind to expand
LaTeX macros. For Kakoune, the snippet

```bash
define-command -hidden texpand-word %{
	evaluate-commands -draft -save-regs 'e|' -no-hooks %{
		try %{ execute-keys '<a-i><a-w>' } catch %{ execute-keys '<a-b>' }

		set-register e 'nop'
		set-register | %{
			root="$(mktemp -d)" ; stdin="$root/stdin" ; stdout="$root/stdout"
			tee "$stdin" | texpand > "$stdout"

			if [ "$?" -eq 0 ]
			then cat "$stdout"
			else printf 'set-register e fail "%s"\n' "failed to expand macro" > "$kak_command_fifo" ; cat "$stdin"
			fi

			rm -rf "$root"
		}

		execute-keys '|<ret>'
		%reg{e}
	}
}

map global insert <c-t> '<a-;>: texpand-word<ret>'
```

will bind `<c-t>` in insert mode to a command which,
1. tries to select the current word; if no word is selected, tries to select
   the previous word;
2. then passes the selection to `texpand`, and replaces the selected word with
   the procured Unicode codepoint if successful; else, does nothing, and prints
   an error message to `*debug*`.

Then, let `|` represent the cursor, so that our buffer is
```
\mu|
```
then `<c-t>` in insert mode will result in
```
μ|
```
but if the expansion were to fail (i.e., if the macro were invalid), the buffer
would instead be unchanged; e.g., for
```
\abcde|
```
`<c-t>` gives
```
\abcde|
```
and prints the message `"failed to expand macro"` on the status line.
